#include "unidb_private.hpp"

namespace unidb {

db::db()
{
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
    return false;
}

bool db::createDB(const fs::path &filepath)
{
    if(!setFilename(filepath)) return false;

    std::ofstream ofs(m_filepath, std::ios::binary);
    if(ofs.is_open()) {
        dbHeader header = {
            .marker = 0x65,
            .signature = {0},
            .version = dbVersion::current(),
            .guid = ::unidb::generateGUID(),
            .encryptionInfo = {0},
            .rootOffset = 0,
            .reserved = {0}
        };
        std::memcpy(header.signature, "unidb", 5);

        ofs.write((char*)&header, sizeof(header));
        ofs.close();
        return true;
    }
    ofs.close();
    return false;
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

} // namespace unidb