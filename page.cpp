#include "page.hpp"
#include <fstream>
#include <iostream>
#include <utility>
#include <cstring> 
#include <arpa/inet.h>
#include <memory>
Page::Page()
        : freespace(0),
          ids_Range({0, 0}),
          tuples() {
        // Initialize PageData to all zeros
        std::memset(PageData, 0, PAGE_SIZE);
    }
    #pragma pack(push, 1)

// bool Page::serialize(int page_id, const std::string& dbName, const std::string& tableName) {
//         // Construct file path
//         std::string filePath = dbName + "/" + tableName + ".HAD";
        
//         // Open the file in binary read/write mode
//         std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
//         if (!file.is_open()) {
//             // If the file doesn't exist, create it
//             file.open(filePath, std::ios::out | std::ios::binary);
//             if (!file.is_open()) {
//                 std::cerr << "Error: Could not open or create file: " << filePath << std::endl;
//                 return false;
//             }
//             file.close();
//             file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
//             if (!file.is_open()) {
//                 std::cerr << "Error: Could not open file after creation: " << filePath << std::endl;
//                 return false;
//             }
//         }
        
//         // Calculate offset
//         size_t offset = static_cast<size_t>(page_id) * PAGE_SIZE;
//         file.seekp(offset);
//         if (file.fail()) {
//             std::cerr << "Error: Could not seek to offset " << offset << " in file: " << filePath << std::endl;
//             return false;
//         }
        
//         // Convert integers to network byte order
//         int freespace_network = htonl(freespace);
//         freespace_network = 1;
//         std::cout << freespace_network << std::endl;
//         int id_first_network = htonl(ids_Range.first);
//         int id_second_network = htonl(ids_Range.second);
        
//         // Write freespace
//         file.write(reinterpret_cast<const char*>(&freespace_network), sizeof(int));
//         if (file.fail()) {
//             std::cerr << "Error: Could not write freespace to file: " << filePath << std::endl;
//             return false;
//         }
        
//         // Write ids_Range.first
//         file.write(reinterpret_cast<const char*>(&id_first_network), sizeof(int));
//         if (file.fail()) {
//             std::cerr << "Error: Could not write ids_Range.first to file: " << filePath << std::endl;
//             return false;
//         }
        
//         // Write ids_Range.second
//         file.write(reinterpret_cast<const char*>(&id_second_network), sizeof(int));
//         if (file.fail()) {
//             std::cerr << "Error: Could not write ids_Range.second to file: " << filePath << std::endl;
//             return false;
//         }
        
//         // Write tuples
//         for (const auto& tuple : tuples) {
//             file.write(reinterpret_cast<const char*>(&tuple), sizeof(Tuple));
//             if (file.fail()) {
//                 std::cerr << "Error: Could not write tuple to file: " << filePath << std::endl;
//                 return false;
//             }
//         }
        
//         // Close the file
//         file.close();
//         return true;
//     }

//  Page* Page::deserialize(int page_id, const std::string& dbName, const std::string& tableName) {
//         // Construct file path
//         std::string filePath = dbName + "/" + tableName + ".HAD";
        
//         // Open the file in binary read mode
//         std::ifstream file(filePath, std::ios::binary);
//         if (!file.is_open()) {
//             std::cerr << "Error: Could not open file: " << filePath << std::endl;
//             return nullptr;
//         }
        
//         // Calculate offset
//         size_t offset = static_cast<size_t>(page_id) * PAGE_SIZE;
//         file.seekg(offset);
//         if (file.fail()) {
//             std::cerr << "Error: Could not seek to offset " << offset << " in file: " << filePath << std::endl;
//             file.close();
//             return nullptr;
//         }
        
//         // Read freespace
//         int freespace_network;
//         file.read(reinterpret_cast<char*>(&freespace_network), sizeof(int));
//         if (file.fail()) {
//             std::cerr << "Error: Could not read freespace from file: " << filePath << std::endl;
//             file.close();
//             return nullptr;
//         }
//         int freespace = ntohl(freespace_network);
        
//         // Read ids_Range.first
//         int id_first_network;
//         file.read(reinterpret_cast<char*>(&id_first_network), sizeof(int));
//         if (file.fail()) {
//             std::cerr << "Error: Could not read ids_Range.first from file: " << filePath << std::endl;
//             file.close();
//             return nullptr;
//         }
//         int id_first = ntohl(id_first_network);
        
//         // Read ids_Range.second
//         int id_second_network;
//         file.read(reinterpret_cast<char*>(&id_second_network), sizeof(int));
//         if (file.fail()) {
//             std::cerr << "Error: Could not read ids_Range.second from file: " << filePath << std::endl;
//             file.close();
//             return nullptr;
//         }
//         int id_second = ntohl(id_second_network);
        
//         // Calculate used space for tuples
//         const size_t used_space = PAGE_SIZE - freespace;
//         const size_t tuples_size = used_space - 3 * sizeof(int); // Subtract metadata size
//         const size_t num_tuples = tuples_size / sizeof(Tuple);
        
//         // Read tuples
//         std::vector<Tuple> tuples;
//         tuples.resize(num_tuples);
//         for (size_t i = 0; i < num_tuples; ++i) {
//             file.read(reinterpret_cast<char*>(&tuples[i]), sizeof(Tuple));
//             if (file.fail()) {
//                 std::cerr << "Error: Could not read tuple " << i << " from file: " << filePath << std::endl;
//                 file.close();
//                 return nullptr;
//             }
//             // If Tuple has a deserialize method, call it here
//             // tuples[i].deserialize();
//         }
        
//         // Create a new Page object and initialize it
//         Page* newPage = new Page();
//         if (!newPage) {
//             std::cerr << "Error: Memory allocation failed for new Page object." << std::endl;
//             file.close();
//             return nullptr;
//         }
//         newPage->freespace = freespace;
//         newPage->ids_Range = std::make_pair(id_first, id_second);
//         newPage->tuples = tuples;
        
//         // Close the file
//         file.close();
//         return newPage;
//     }


bool Page::serialize(int page_id, const std::string& dbName, const std::string& tableName) {
    std::string filePath = dbName + "/" + tableName + ".HAD";
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return false;
    }

    size_t offset = static_cast<size_t>(page_id) * PAGE_SIZE;
    file.seekp(offset);

    // Determine the current file size
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    std::cout << file_size<<"ddd"<<std::endl;
    file.seekp(offset);

    // Extend the file with zeros if necessary
    // if (offset + PAGE_SIZE > file_size) {
    //     size_t bytes_to_write = offset + PAGE_SIZE - file_size;
    //     char padding[bytes_to_write];
    //     memset(padding, 0, bytes_to_write);
    //     file.write(padding, bytes_to_write);
    // }

    // Serialize metadata and tuples here
    int fs_network = htonl(freespace);
    //fs_network = 10;
    file.write(reinterpret_cast<const char*>(&fs_network), sizeof(int));
    if (file.fail()) {
        std::cerr << "Error: Could not write freespace to file: " << filePath << std::endl;
        file.close();
        return false;
    }

    int id_first_network = htonl(ids_Range.first);
    file.write(reinterpret_cast<const char*>(&id_first_network), sizeof(int));
    if (file.fail()) {
        std::cerr << "Error: Could not write ids_Range.first to file: " << filePath << std::endl;
        file.close();
        return false;
    }

    int id_second_network = htonl(ids_Range.second);
    file.write(reinterpret_cast<const char*>(&id_second_network), sizeof(int));
    if (file.fail()) {
        std::cerr << "Error: Could not write ids_Range.second to file: " << filePath << std::endl;
        file.close();
        return false;
    }

    // Serialize tuples
    // for (const auto& tuple : tuples) {
    //     file.write(reinterpret_cast<const char*>(&tuple), sizeof(Tuple));
    //     if (file.fail()) {
    //         std::cerr << "Error: Could not write tuple to file: " << filePath << std::endl;
    //         file.close();
    //         return false;
    //     }
    // }

    // Calculate the data written and add padding if necessary
    // size_t data_written = 3 * sizeof(int) ;
    // if (data_written < PAGE_SIZE) {
    //     char padding[PAGE_SIZE - data_written];
    //     memset(padding, 0, PAGE_SIZE - data_written);
    //     file.write(padding, PAGE_SIZE - data_written);
    // }

    file.close();
    return true;
}  

Page* Page::deserialize(int page_id, const std::string& dbName, const std::string& tableName) {
        std::string filePath = dbName + "/" + tableName + ".HAD";
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for reading: " << filePath << std::endl;
            return nullptr;
        }

        size_t offset = static_cast<size_t>(page_id) * PAGE_SIZE;
        file.seekg(offset);
        if (file.fail()) {
            std::cerr << "Error: Could not seek to offset " << offset << " in file: " << filePath << std::endl;
            file.close();
            return nullptr;
        }

        size_t file_size = 0;
        file.seekg(0, std::ios::end);
        file_size = file.tellg();
        file.seekg(offset);

        if (file_size < offset + PAGE_SIZE) {
            std::cerr << "File is smaller than expected for page " << page_id << std::endl;
            file.close();
            return nullptr;
        }

        int freespace_network;
        if (!file.read(reinterpret_cast<char*>(&freespace_network), sizeof(int))) {
            std::cerr << "Error: Could not read freespace from file: " << filePath << std::endl;
            file.close();
            return nullptr;
        }
        int freespace = ntohl(freespace_network);

        int id_first_network;
        if (!file.read(reinterpret_cast<char*>(&id_first_network), sizeof(int))) {
            std::cerr << "Error: Could not read ids_Range.first from file: " << filePath << std::endl;
            file.close();
            return nullptr;
        }
        int id_first = ntohl(id_first_network);

        int id_second_network;
        if (!file.read(reinterpret_cast<char*>(&id_second_network), sizeof(int))) {
            std::cerr << "Error: Could not read ids_Range.second from file: " << filePath << std::endl;
            file.close();
            return nullptr;
        }
        int id_second = ntohl(id_second_network);

        const size_t used_space = PAGE_SIZE - freespace;
        const size_t tuples_size = used_space - 3 * sizeof(int);

        // if (used_space < 0 || tuples_size < 0 || tuples_size % sizeof(Tuple) != 0) {
        //     std::cerr << "Invalid space calculations." << std::endl;
        //     file.close();
        //     return nullptr;
        // }

        // const size_t num_tuples = tuples_size / sizeof(Tuple);

        // std::vector<Tuple> tuples;
        // tuples.reserve(num_tuples);

        // for (size_t i = 0; i < num_tuples; ++i) {
        //     Tuple tuple;
        //     if (!file.read(reinterpret_cast<char*>(&tuple), sizeof(Tuple))) {
        //         std::cerr << "Error: Could not read tuple " << i << " from file: " << filePath << std::endl;
        //         file.close();
        //         return nullptr;
        //     }
        //     tuples.push_back(tuple);
        // }

        Page* newPage = new Page();
        if (!newPage) {
            std::cerr << "Error: Memory allocation failed for new Page object." << std::endl;
            file.close();
            return nullptr;
        }
        newPage->freespace = freespace;
        std::cout<<freespace<<"from desir"<<std::endl;
        newPage->ids_Range = std::make_pair(id_first, id_second);
        //newPage->tuples = tuples;

        file.close();
        return newPage;
    }
// #include "page.hpp"
// #include <iostream>

// bool Page::insert_tuple(const std::vector<std::pair<std::string, std::pair<int, std::string>>>& attributes) {
//     if (Page_MetaData + sizeof(attributes) > PAGE_SIZE) {
//         std::cerr << "Not enough space to insert tuple." << std::endl;
//         return false;
//     }
    
//     tuples.emplace_back(Tuple{attributes});
//     Page_MetaData += sizeof(attributes);
//     std::cout << "Tuple inserted successfully." << std::endl;
//     return true;
// }

// Tuple* Page::get_tuple(const std::pair<std::string, std::string>& attribute) {
//     for (auto& tuple : tuples) {
//         if (tuple.get_attribute(attribute.first) == attribute.second) {
//             return &tuple;
//         }
//     }
//     std::cerr << "Tuple not found." << std::endl;
//     return nullptr;
// }

// bool Page::update_tuple(const std::vector<std::pair<std::string, std::string>>& attributes) {
//     for (auto& tuple : tuples) {
//         tuple.update_attribute(attributes);
//     }
//     std::cout << "Tuple updated successfully." << std::endl;
//     return true;
// }

// bool Page::del_tuple(const std::pair<std::string, std::string>& attribute) {
//     for (auto it = tuples.begin(); it != tuples.end(); ++it) {
//         if (it->get_attribute(attribute.first) == attribute.second) {
//             tuples.erase(it);
//             std::cout << "Tuple deleted successfully." << std::endl;
//             return true;
//         }
//     }
//     std::cerr << "Tuple not found to delete." << std::endl;
//     return false;
// }
