#pragma once
#include <string>
#include <map>
#include <vector>
#include <SharedCppLib2/bytearray.hpp>

namespace unidb {

class typesystem {

    struct typeinfo {
        std::string name;
        size_t size;
    };

    bool registerType(const typeinfo& ti);
    bool registerType();

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

private:
    ::unidb::typesystem m_typesystem;
};


} // namespace unidb
