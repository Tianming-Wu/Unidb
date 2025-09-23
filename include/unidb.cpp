#include "unidb.hpp"

namespace unidb {
    
bool typesystem::registerType(const typeinfo& ti)
{
    if(m_typeinfos.find(ti.name) != m_typeinfos.end()) {
        return false;
    }

    m_typeinfos.insert(std::make_pair(ti.name, ti));
    return true;
}




} // namespace unidb