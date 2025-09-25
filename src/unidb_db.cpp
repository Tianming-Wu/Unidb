#include "unidb_private.hpp"
#include "unidb.hpp"

namespace unidb {

db::db()
    : m_root(nullptr)
{
    m_objectlist.insert(std::make_pair(0, &m_root));
}

db::~db()
{
}

bool db::writeFile()
{
    return false;
}

bool db::readFile()
{
    std::ifstream ifs(m_filepath, std::ios::binary);
    if(ifs.is_open()) {
        dbHeader header;
        ifs.read((char*)&header, sizeof(header));

        if(!header.isValid()) {
            ifs.close();
            throw unidb_invalid_db_exception("Invalid database file, header mismatch.");
        }


        ifs.close();
        return true;
    }
    ifs.close();
    throw unidb_file_exception("Cannot open database file.");
}

bool db::createDB(const fs::path &filepath)
{
    if(fs::exists(filepath)) {
        throw unidb_file_exception("Database file already exists.");
    }

    std::ofstream ofs(m_filepath, std::ios::binary);
    if(ofs.is_open()) {
        dbHeader header = {
            .marker = 0x65,
            .signature = {0},
            .version = dbVersion::current(),
            .guid = ::unidb::generateGUID(),
            .encryptionInfo = {0},
            .rootOffset = 0,
            .objectCount = 0,
            .reserved = {0}
        };
        std::memcpy(header.signature, "unidb", 5);

        ofs.write((char*)&header, sizeof(header));
        ofs.close();
        return true;
    }
    ofs.close();
    throw unidb_file_exception("Cannot create database file.");
}
bool db::setFilename(const fs::path &filepath)
{
    if(fs::exists(filepath)) {
        if(!fs::is_regular_file(filepath)) {
            return false;
        }
    }

    ///TODO: check write permission

    m_filepath = filepath;
    return true;
}

::unidb::object *db::getObjectById(uint64_t uid)
{
    if(m_objectlist.find(uid) == m_objectlist.end())
        throw unidb_internal_reference_exception("Cannot find object by id " + std::to_string(uid));
    return m_objectlist[uid];
}

::unidb::object *db::makeObject(uint64_t parent_uid)
{
    ::unidb::object* nobj = new object(getObjectById(parent_uid));
    return nobj;
}

void db::defrag()
{
    // TODO: remove any unused code from the system.
}

} // namespace unidb