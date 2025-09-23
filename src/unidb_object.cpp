#include "unidb.hpp"

namespace unidb {

object::object(object* parent)
: m_parent(parent)
{
    if(parent != nullptr) parent->__p_registerAsChild(this);
}

object::~object()
{

}

void object::__p_registerAsChild(object* child) {
    m_childrens.push_back(child);
}

void object::__p_unregisterChild(object *child)
{
    std::vector<object*>::iterator it = m_childrens.begin();
    for(; it != m_childrens.end(); it++) {
        if((*it) == child) {
            it = m_childrens.erase(it);
            break;
        }
    }
}

} // namespace unidb