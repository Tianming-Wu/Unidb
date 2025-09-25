#include "unidb_private.hpp"
#include "unidb.hpp"

namespace unidb {

object::object()
{
}

object::~object()
{
}

std::bytearray object::pack() const
{
    std::bytearray ba;
    
    // Own uid
    ba.append(m_uid);

    // Name info
    ba.append(m_name.size());
    ba.append(m_name.data());

    // Write the parent uid
    ba.append(m_parentuid);

    // Write the childrens
    ba.append(m_childrens.size());
    for(auto child_uid : m_childrens) {
        ba.append(child_uid);
    }

    // Type id
    ba.append(m_typeid);

    // Data size (reserved for dynamic types)
    ba.append(static_cast<uint64_t>(0));

    // Data content
    ba.append(m_data);

    return ba;
}

bool object::unpack(const std::bytearray &data)
{
    size_t p = 0;

    // uid
    m_uid = data.subarr(p, sizeof(uint64_t)).convert_to<uint64_t>(); p += 1;

    // name
    size_t name_size = data.subarr(p, sizeof(size_t)).convert_to<size_t>(); p += sizeof(size_t);
    m_name = data.subarr(p, name_size).tostdstring(); p += name_size;

    // parent uid
    m_parentuid = data.subarr(p, sizeof(uint64_t)).convert_to<uint64_t>(); p += sizeof(uint64_t);

    //childrens
    size_t children_size = data.subarr(p, sizeof(size_t)).convert_to<size_t>(); p += sizeof(size_t);
    for(size_t i = 0; i < children_size; i++) {
        uint64_t child_uid = data.subarr(p, sizeof(uint64_t)).convert_to<uint64_t>();
        p += sizeof(uint64_t);
    }

    // type id
    m_typeid = data.subarr(p, sizeof(int)).convert_to<int>(); p += sizeof(int);

    // Data size
    size_t data_size = data.subarr(p, sizeof(size_t)).convert_to<size_t>(); p += sizeof(size_t);

    // data
    m_data = data.subarr(p, data_size);

    return true;
}

void object::__p_setParent(uint64_t parent_uid)
{
    m_parentuid = parent_uid;
}

void object::__p_addChild(uint64_t child_uid)
{
    m_childrens.push_back(child_uid);
}

void object::__p_removeChild(uint64_t child_uid)
{
     std::vector<uint64_t>::iterator it = m_childrens.begin();
    for(; it != m_childrens.end(); it++) {
        if((*it) == child_uid) {
            it = m_childrens.erase(it);
            return;
        }
    }
    throw unidb_internal_reference_exception("Cannot find child by id " + std::to_string(child_uid));
}

uint64_t object::__p_getUid() const { return m_uid; }

void object::__p_setUid(uint64_t id)
{
    m_uid = id;
}

} // namespace unidb