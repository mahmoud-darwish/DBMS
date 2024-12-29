#include "FileManager.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

// Initialize the static members
std::unique_ptr<FileHandler> FileHandler::instance = nullptr;
std::mutex FileHandler::mtx;

// Private Constructor
FileHandler::FileHandler(const std::string& dbName, const std::string& fileName, std::ios::openmode mode, const std::string& extension ) {
    fs::create_directories(dbName);
    filePath = dbName + "/" + fileName + ".HAD";
    openFile(mode);
}


// Private method to open the file with the desired mode
void FileHandler::openFile(std::ios::openmode mode) {
    if (fileStream.is_open()) {
        fileStream.close();
    }
    fileStream.open(filePath, std::ios::in |std::ios::out | std::ios::binary);
    std::cout << "Attempting to open file at: " << filePath << std::endl;
    if (!fileStream.is_open()) {
        throw std::ios_base::failure("Error: Could not open file " + filePath);
    }
    currentMode = mode;
}

// Static method to get the singleton instance
FileHandler& FileHandler::getInstance(const std::string& dbName, const std::string& fileName, std::ios::openmode mode) {
    std::lock_guard<std::mutex> lock(mtx);  // Thread-safe initialization
    if (!instance) {
        instance.reset(new FileHandler(dbName, fileName, mode));
    } else if (instance->currentMode != mode) {
        instance->reopen(mode);
    }
    return *instance;
}

// Method to reopen the file in a different mode
void FileHandler::reopen(std::ios::openmode mode) {
    if (currentMode != mode) {
        openFile(mode);
        currentMode = mode;
    }
}

// Destructor
FileHandler::~FileHandler() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

// Method to read a line from the file
bool FileHandler::readLine(std::string& line) {
    if (!fileStream.is_open()) {
        throw std::ios_base::failure("Error: File is not open for reading");
    }

    if (std::getline(fileStream, line)) {
        return true;
    } else {
        return false;
    }
}

// Method to flush the output buffer to the file
void FileHandler::flush() {
    fileStream.flush();
}

// Method to check if the file is open
bool FileHandler::isFileOpen() const {
    return fileStream.is_open();
}

// Get the file path
std::string FileHandler::getFilePath() const {
    return filePath;
}

void FileHandler::write(const std::string& data) {
    if (!fileStream.is_open() || !(fileStream.flags() & std::ios::out)) {
        throw std::ios_base::failure("Error: File is not open for writing");
    }
    fileStream << data;
}

void FileHandler::writeBinary(const char* data, std::size_t size) {
    if (!fileStream.is_open() || !(fileStream.flags() & std::ios::out)) {
        throw std::ios_base::failure("Error: File is not open for writing binary data");
    }
    fileStream.write(data, size);
}

void FileHandler::readBinary(char* data, std::size_t size) {
    if (!fileStream.is_open() || !(fileStream.flags() & std::ios::in)) {
        throw std::ios_base::failure("Error: File is not open for reading binary data");
    }
    fileStream.read(data, size);
}

void FileHandler::deleteFile() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
    std::filesystem::remove(filePath);
}
