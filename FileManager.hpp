#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <fstream>
#include <string>
#include <memory>
#include <mutex>

class FileHandler {
private:
    std::fstream fileStream;
    std::string filePath;
    std::ios::openmode currentMode;  // Track the current mode (read/write)

    // Private Constructor
    FileHandler(const std::string& dbName, const std::string& fileName, std::ios::openmode mode, const std::string& extension = ".HAD") ;

    // Disable copy constructor and assignment operator
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    // Singleton instance
    static std::unique_ptr<FileHandler> instance;
    static std::mutex mtx;

    // Private method to open the file with the desired mode
    void openFile(std::ios::openmode mode);

public:
    // Static method to get the singleton instance
    static FileHandler& getInstance(const std::string& dbName, const std::string& fileName, std::ios::openmode mode);

    // Method to write data to the file
    template <typename T>
    void writeData(const T& data);

    // Method to read data from the file
    template <typename T>
    void readData(T& data);

    // Method to read a line from the file
    bool readLine(std::string& line);

    // Destructor
    ~FileHandler();

    // Method to flush the output buffer to the file
    void flush();

    // Method to check if the file is open
    bool isFileOpen() const;

    // Get the file path (for verification or logging)
    std::string getFilePath() const;

    // Method to reopen file in a different mode
    void reopen(std::ios::openmode mode);
    void write(const std::string& data);

    void writeBinary(const char* data, std::size_t size) ;

void readBinary(char* data, std::size_t size);
void deleteFile() ;
};
// Include templates implementation
#include "FileManager.tpp"

#endif // FILE_HANDLER_HPP
