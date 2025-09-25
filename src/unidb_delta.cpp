#include "unidb_private.hpp"

#include <random>

namespace unidb {

dbVersion dbVersion::current() {
    return dbVersion {PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, PROJECT_VERSION_TWEAK};
}


bool dbHeader::isValid() const {
    if(marker != 0x65) return false;
    if(std::string(signature, 5) != "unidb") return false;
    if(version.major != 0) return false; // only major version 0 is supported
    return true;
}

guid_t generateGUID() {
    guid_t guid = {0};

    // This is a placeholder implementation. In a real-world scenario, you would use a proper GUID generation library or API.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis32(0, 0xFFFFFFFF);
    std::uniform_int_distribution<uint16_t> dis16(0, 0xFFFF);
    std::uniform_int_distribution<uint8_t> dis8(0, 0xFF);

    guid.data1 = dis32(gen);
    guid.data2 = dis16(gen);
    guid.data3 = dis16(gen);
    for(int i = 0; i < 8; i++) {
        guid.data4[i] = dis8(gen);
    }

    return guid;
};


} // namespace unidb