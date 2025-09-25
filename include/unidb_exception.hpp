#pragma once

#include <stdexcept>
#include <string>

namespace unidb {

class unidb_exception : public std::runtime_error {
public:
    explicit unidb_exception(const std::string& message)
        : std::runtime_error(message) {}

    explicit unidb_exception(const char* message)
        : std::runtime_error(message) {}


};

#define UNIDB_DEFINE_EXCEPTION(name) \
class name : public unidb_exception { \
public: \
    explicit name(const std::string& message) \
        : unidb_exception(message) {} \
    explicit name(const char* message) \
        : unidb_exception(message) {} \
};

UNIDB_DEFINE_EXCEPTION(unidb_file_exception)
UNIDB_DEFINE_EXCEPTION(unidb_invalid_db_exception)

} // namespace unidb