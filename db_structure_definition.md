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
 - [objectid_count] size = 8, content = size_type:
 - [reserved] size = 42, reserved

### [type system] size = *
-> p = 128
 - [entrysize] size = 8, content = long_integer: $[]

### [root object] size = *
-> p = $rootoffset
 - [] size = 8


### [content] size = *


## Builtin Storage Structures Standard
### String / ByteArray
-> offset = 0
- [size] size = 4, content: $Size
- [content] size = $Size, content: $Data