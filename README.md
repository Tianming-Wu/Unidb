# Uni DB

English | [中文](README.zh_CN.md)

This project implements a simple, light-weighted database system, which is completely portable.

Warning: To properly use this library, you must deal with those exceptions well.

## Features
- Portable: No files are storaged in the local file system.
- Custom type: supports register custon types.
- Encryption Support (Not present).



## Warnings
- These useful features are not yet supported, and is not planned for development in the near future:
  - Atomic operation
  - Read/Write Protection
  - Multiple access point
  - Real-time sync

So if you want to use it on a portable device, you need to ensure that any application using the database should be closed or saved to disk in advance.