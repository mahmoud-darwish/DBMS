#ifndef FILE_HANDLER_TPP
#define FILE_HANDLER_TPP

#include "FileManager.hpp"

// Template method to write data to the file
template <typename T>
void FileHandler::writeData(const T& data) {
    if (!fileStream.is_open()) {
        throw std::ios_base::failure("Error: File is not open for writing");
    }
    fileStream << data;
    if (fileStream.fail()) {
        throw std::ios_base::failure("Error: Writing to file failed");
    }
}

// Template method to read data from the file
template <typename T>
void FileHandler::readData(T& data) {
    if (!fileStream.is_open()) {
        throw std::ios_base::failure("Error: File is not open for reading");
    }
    fileStream >> data;
    if (fileStream.fail()) {
        throw std::ios_base::failure("Error: Reading from file failed");
    }
}

#endif // FILE_HANDLER_TPP
