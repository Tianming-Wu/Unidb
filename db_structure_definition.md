# File Structure Definition

## Database File
extension: .unidb
### [header] size = 128
-> p = 0
 - [marker] size = 1, content = static_byte: 0x65
 - [signature] size = 5, content = static_string: "unidb"
 - [version] size = 16, content = {
    - [MajorVersion] size = 4, content = integer: $MajorVersion
    - [MinorVersion] size = 4, content = integer: $MinorVersion
    - [Version] size = 4, content = integer: $Version
    - [Version] size = 4, content = integer: $Version
 }
 - [guid] size = 16, content = guid
 - [encryption] size = 32, reserved
 - [root_offset] size = 8, content = size_type: $rootoffset
 - [max_id] size = 8, content = size_type:
 - [reserved] size = 42, reserved

### [type system] size = *
-> p = 128
 - [count] size = 8, content = long_integer: $count
 

### [root object] size = *
-> p = $rootoffset
 - [children_size] size = 8, content = size_t: $childrenSize
 - [children] size = {$childrenSize * sizeof(uint64_t)}, content = (children_uid): $Data

### [content] size = *
-> p
 - [size] size = 8, content = size_t: #sizeof(this_section)
 - [uid] size = 8, content = uint64_t: $uid
 - [name_size] size = 8, content = size_t: $NameSize
 - [name] size = $NameSize, content = (string): $Data
 - [parent_uid] size = 8, content = uint64_t: $parentuid
 - [children_size] size = 8, content = size_t: $childrenSize
 - [children] size = {$childrenSize * sizeof(uint64_t)}, content = (children_uid): $Data
 - [type_id] size = 4, content = integer: $type_id
 - [data_size] size = 8, content = size_t: $dataSize
 - [data] size = $dataSize, content = (bytearray): $data

## Builtin Storage Structures Standard
### String / ByteArray
-> offset = 0
- [size] size = 8, content = size_t: $Size
- [content] size = $Size, content = (string): $Data