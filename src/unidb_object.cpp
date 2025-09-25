#include "unidb_private.hpp"
#include "unidb.hpp"

namespace unidb {

object::object(object* parent)
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
    


    return true;
}

void object::__p_registerAsChild(uint64_t child_uid)
{
    m_childrens.push_back(child_uid);
}

void object::__p_unregisterChild(uint64_t child_uid)
{
     std::vector<uint64_t>::iterator it = m_childrens.begin();
    for(; it != m_childrens.end(); it++) {
        if((*it) == child_uid) {
            it = m_childrens.erase(it);
            return;
        }
    }
    throw unidb_
}

uint64_t object::__p_getUid() const { return m_uid; }

} // namespace unidb