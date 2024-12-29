// File: database.cpp
#include "DataBase.hpp"
#include <iostream>
#include "FileManager.hpp"
DataBase::DataBase(const std::string& name) : dbname(name) {}

bool DataBase::createDatabase() {
    if (fs::create_directory(dbname)) {
        std::cout << "c " << dbname << std::endl;
        return true;
    }
    std::cerr << "Failed to create database: " << dbname << std::endl;
    return false;
}

bool DataBase::tableExists(const std::string& tableName) {
    // Define the directory where tables are stored

    // Construct the full path to the table
    std::filesystem::path tablePath = std::filesystem::path(dbname) / (tableName+".HAD");

    // Check if the table exists as a file or directory
    return std::filesystem::exists(tablePath);
}

bool DataBase::createTable(const std::string& tableName, const std::map<std::string, std::string>& schema) {
    if (tableExists(tableName)) {
        std::cerr << "Table already exists: " << tableName << std::endl;
        return false;
    }
    uint32_t size;
    serializeSchema(schema,dbname,tableName,size);
    Table* table= new Table(tableName);
    table->schema = schema;
    table->size = size;
    std::cout << "Table created: " << tableName << std::endl;
    return true;
}

bool DataBase::deleteTable(const std::string& tableName) {
    // Define the directory where tables are stored
    const std::string dbDirectory = "dbname";

    // Construct the full path to the table directory
    std::filesystem::path tablePath = std::filesystem::path(dbDirectory) / tableName;

    // Check if the directory exists
    if (!std::filesystem::exists(tablePath)) {
        std::cerr << "Table does not exist: " << tableName << std::endl;
        return false;
    }

    // Try to delete the directory (only if it's empty)
    try {
        if (std::filesystem::is_directory(tablePath) && std::filesystem::remove(tablePath)) {
            std::cout << "Table directory deleted: " << tableName << std::endl;
            return true;
        } else {
            std::cerr << "Failed to delete table directory. Ensure it is empty: " << tableName << std::endl;
            return false;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error deleting table directory: " << e.what() << std::endl;
        return false;
    }
}

Table* DataBase::getTable(const std::string tableName ) {
    if (tableExists(tableName)) {
        Table* my = new Table(tableName);
        std::map<std::string, std::string> schema;
        uint32_t size;
        bool ok = deserializeSchema(schema,dbname,tableName,size);
        my->size= size;
        std::cout <<"offset size "<< my->size<<std::endl;
        my->schema = schema;
          for (const auto& [key, value] : schema) {
        std::cout << key << ": " << value << std::endl;
    }
        return my;
    }
    std::cerr << "Table not found: " << tableName << std::endl;
    return nullptr;
}


bool DataBase::serializeSchema(const std::map<std::string, std::string>& schema, const std::string& dbName, const std::string& fileName,uint32_t& size) {
    try {
        // Construct the full file path
        std::string filePath = dbName + "/" + fileName + ".HAD";

        // Open the file in binary write mode
        std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);
        if (!outFile.is_open()) {
            throw std::ios_base::failure("Error: Could not open file for writing: " + filePath);
        }

        // Write the size of the schema
        uint32_t size = schema.size();
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

        // Write each key-value pair
        for (const auto& [key, value] : schema) {
            uint32_t keySize = key.size();
            uint32_t valueSize = value.size();

            // Write key size and value size
            outFile.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
            outFile.write(reinterpret_cast<const char*>(&valueSize), sizeof(valueSize));

            // Write key and value
            outFile.write(key.data(), keySize);
            outFile.write(value.data(), valueSize);
        }

        // Close the file
        outFile.close();
        std::cout << "Schema serialized successfully to " << filePath << std::endl;
        return true;
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error serializing schema: " << e.what() << std::endl;
        return false;
    }
}

// Deserialize the schema from a .HAD file using FileHandler
bool DataBase::deserializeSchema(std::map<std::string, std::string>& schema, const std::string& dbName, const std::string& fileName,uint32_t& size) {
    try {
        // Construct the full file path
        std::string filePath = dbName + "/" + fileName + ".HAD";

        // Open the file in binary read mode
        std::ifstream inFile(filePath, std::ios::binary);
        if (!inFile.is_open()) {
            throw std::ios_base::failure("Error: Could not open file for reading: " + filePath);
        }

        // Read the size of the schema
        uint32_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        if (inFile.fail()) {
            throw std::ios_base::failure("Error: Failed to read schema size.");
        }

        // Clear the schema map
        schema.clear();

        // Read each key-value pair
        for (uint32_t i = 0; i < size; ++i) {
            uint32_t keySize, valueSize;

            // Read key size and value size
            inFile.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));
            inFile.read(reinterpret_cast<char*>(&valueSize), sizeof(valueSize));
            if (inFile.fail()) {
                throw std::ios_base::failure("Error: Failed to read key/value sizes.");
            }

            // Read the key
            std::string key(keySize, '\0');
            inFile.read(&key[0], keySize);
            if (inFile.fail()) {
                throw std::ios_base::failure("Error: Failed to read key.");
            }

            // Read the value
            std::string value(valueSize, '\0');
            inFile.read(&value[0], valueSize);
            if (inFile.fail()) {
                throw std::ios_base::failure("Error: Failed to read value.");
            }

            // Add the key-value pair to the schema
            schema[key] = value;
        }

        // Close the file
        inFile.close();
        std::cout << "Schema deserialized successfully from " << filePath << std::endl;
        return true;
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error deserializing schema: " << e.what() << std::endl;
        return false;
    }
}


