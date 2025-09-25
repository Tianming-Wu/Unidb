#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>
#include <SharedCppLib2/bytearray.hpp>

#include "version.hpp"
#include "unidb_exception.hpp"

namespace fs = std::filesystem;

namespace unidb {

class typesystem {

    struct typeinfo {
        std::string name;
        size_t size;
    };

    bool registerType(const typeinfo& ti);
    // bool registerType();

private:

    std::map<std::string, typeinfo> m_typeinfos;
    int __m_unique_typeid_distribution = 0;
};

class object {
public:
    object();
    ~object();

    std::bytearray pack() const;
    bool unpack(const std::bytearray& data);

protected:
    void __p_setParent(uint64_t parent_uid);

    void __p_addChild(uint64_t child_uid);
    void __p_removeChild(uint64_t child_uid);

    uint64_t __p_getUid() const;
    void __p_setUid(uint64_t id);

private:
    uint64_t m_uid, m_parentuid;
    std::vector<uint64_t> m_childrens;
    std::string m_name;
    int m_typeid = -1;
    std::bytearray m_data;

    friend class ::unidb::db;
};

class db {
public:
    db();
    ~db();

    inline typesystem& typesystem() { return m_typesystem; }

    bool writeFile();

    /**
     * @return `true` if read successfully, `false` if file not exists or error occurs
     * @throw `unidb_invalid_db_exception` if file is not a valid unidb database file
     */
    bool readFile();

    bool createDB(const fs::path &filepath);
    inline fs::path filepath() const { return m_filepath; }

    bool setFilename(const fs::path &filepath);

    ::unidb::object* getObjectById(uint64_t uid);
    ::unidb::object* makeObject();

    void defrag();

private:
    ::unidb::typesystem m_typesystem;
    object m_root;
    fs::path m_filepath;

    std::map<uint64_t, ::unidb::object*> m_objectlist;

    int __m_unique_typeid_distribution = 1;
};


} // namespace unidb
