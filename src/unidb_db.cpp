#include "unidb_private.hpp"
#include "unidb.hpp"

namespace unidb {

db::db()
    : m_root()
{
    m_objectlist.insert(std::make_pair(0, &m_root));
    m_root.__p_setUid(1);
    m_root.__p_setParent(0);
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
        std::bytearray data_tp;

        ifs.read((char*)&header, sizeof(header));

        if(!header.isValid()) {
            ifs.close();
            throw unidb_invalid_db_exception("Invalid database file, header mismatch.");
        }

        size_t p = sizeof(dbHeader);

        // read typesystem


        p = header.rootOffset;
        // read root object
        
        size_t children_size;
        ifs >> children_size;

        data_tp.readFromStream(ifs, children_size * sizeof(uint64_t));

        p += sizeof(size_t);
        for(size_t i = 0; i < children_size; i++) {
            uint64_t child_uid = data_tp.subarr(p, sizeof(uint64_t)).convert_to<uint64_t>();
            p += sizeof(uint64_t);
        }
    

        // read object
        for(size_t c = 1; c <= header.max_id; c++) {
            std::bytearray objdata;
            size_t curobject_size;

            ::unidb::object* nobj = makeObject();

            ifs.read((char*)&curobject_size, sizeof(size_t));

            objdata.readFromStream(ifs, curobject_size);
            nobj->unpack(objdata);

            p += curobject_size + sizeof(size_t); // the object size in total
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
            .max_id = 1, // root
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

::unidb::object *db::makeObject()
{
    ::unidb::object* nobj = new object();
    // nobj->__p_setUid(++__m_unique_typeid_distribution);
    return nobj;
}

void db::defrag()
{
    // TODO: remove any unused code from the system.
}

} // namespace unidb