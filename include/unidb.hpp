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
    int __m_unique_id_distribution = 0;
};

class object {
public:
    object(object* parent = nullptr);
    ~object();

    inline object* parent() { return m_parent; };

protected:
    void __p_registerAsChild(object* child);
    void __p_unregisterChild(object* child);

private:
    object *m_parent;
    std::vector<object*> m_childrens;
    std::bytearray m_data;
    int m_typeid = -1;
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

private:
    ::unidb::typesystem m_typesystem;
    object m_root;
    fs::path m_filepath;
};


} // namespace unidb
