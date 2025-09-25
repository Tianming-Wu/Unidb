#include "unidb.hpp"
#include <iostream>


int main() {
    unidb::db database;
    database.setFilename("testdb.unidb");

    std::string line;
    while(getline(std::cin, line)) {
        if(line == "exit" || line == "quit") {
            break;
        } else if (line == "create") {
            try {
                if(database.createDB("testdb.unidb")) {
                    std::cout << "Database created." << std::endl;
                } else {
                    std::cout << "Failed to create database." << std::endl;
                }
            } catch(const unidb::unidb_exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
                return 1;
            }
        } else if (line == "defrag") {
            database.defrag();
            std::cout << "Defrag completed." << std::endl;
        } else if (line == "write") {
            if(database.writeFile()) {
                std::cout << "Write success." << std::endl;
            } else {
                std::cout << "Write failed." << std::endl;
            }
        } else if(line == "read") {
            try {
                if(!database.readFile()) {
                    std::cout << "Failed to read database file." << std::endl;
                    return 1;
                }
            } catch(const unidb::unidb_exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
                return 1;
            }
            std::cout << "Read success" << std::endl;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }




    return 0;



}