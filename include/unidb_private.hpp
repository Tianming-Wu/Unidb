#pragma once
#include "unidb.hpp"

namespace unidb {

// Compatibility: same major version
struct dbVersion {
    uint32_t major, minor, patch, build;

    static dbVersion current();
};

struct guid_t {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
};

struct dbHeader {
    uint8_t marker; // should be 0x65
    char signature[5]; // should be "unidb"
    dbVersion version;
    guid_t guid;
    uint8_t encryptionInfo[32]; // reserved for future use
    uint64_t rootOffset;
    uint64_t objectCount;
    uint8_t reserved[42];

    bool isValid() const;
};

guid_t generateGUID();

} // namespace unidb