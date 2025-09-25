#pragma once

#include <stdexcept>
#include <string>

namespace unidb {

class unidb_exception : public std::runtime_error {
public:
    inline explicit unidb_exception(const std::string& message)
        : std::runtime_error(message) {}

    inline explicit unidb_exception(const char* message)
        : std::runtime_error(message) {}

    inline const char* what() const noexcept override {
        return std::runtime_error::what();
    }

};

#define UNIDB_DEFINE_EXCEPTION(name) \
class name : public unidb_exception { \
public: \
    inline explicit name(const std::string& message) \
        : unidb_exception(message) {} \
    inline explicit name(const char* message) \
        : unidb_exception(message) {} \
};

UNIDB_DEFINE_EXCEPTION(unidb_file_exception)
UNIDB_DEFINE_EXCEPTION(unidb_invalid_db_exception)
UNIDB_DEFINE_EXCEPTION(unidb_internal_reference_exception)


} // namespace unidb