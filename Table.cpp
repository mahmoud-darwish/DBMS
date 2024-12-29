#include "Table.hpp"
#include "page.hpp"
#include<iostream>
void Table::Create_page() {
    std::map<int, std::pair<int, int>> page_meta = {{directory.size(), {0, 0}}};
    directory.push_back(page_meta);
    std::cout << "Page created with ID: " << directory.size() - 1 << std::endl;
}

Page* Table::Get_page(int page_id) {
    if (page_id >= 0 && page_id < static_cast<int>(directory.size())) {
        return new Page(); // Assuming Page retrieval logic is more complex in a real scenario.
    }
    std::cerr << "Invalid page ID: " << page_id << std::endl;
    return nullptr;
}

void Table::Update_page(int page_id, Page* page) {
    if (page_id >= 0 && page_id < static_cast<int>(directory.size())) {
        // Update logic for the page (Placeholder)
        std::cout << "Page updated: " << page_id << std::endl;
    } else {
        std::cerr << "Invalid page ID: " << page_id << std::endl;
    }
}

void Table::Delete_page(int page_id) {
    if (page_id >= 0 && page_id < static_cast<int>(directory.size())) {
        directory.erase(directory.begin() + page_id);
        std::cout << "Page deleted: " << page_id << std::endl;
    } else {
        std::cerr << "Invalid page ID: " << page_id << std::endl;
    }
}

bool Table::serializeDirectory(const std::string& dbName, const std::string& fileName) {
    try {
        // Construct the full file path
        std::string filePath = dbName + "/" + fileName + ".HAD";

        // Open the file in binary mode
        std::fstream outFile(filePath, std::ios::in | std::ios::out | std::ios::binary);
        if (!outFile.is_open()) {
            throw std::ios_base::failure("Error: Could not open file for writing: " + filePath);
        }

        // Seek to the specified offset
        outFile.seekp(offset);
        if (outFile.fail()) {
            throw std::ios_base::failure("Error: Could not seek to the specified offset.");
        }

        // Write the directory size
        uint32_t directorySize = directory.size();
        outFile.write(reinterpret_cast<const char*>(&directorySize), sizeof(directorySize));

        // Serialize the directory
        for (const auto& page : directory) {
            // Write the number of entries in the current page map
            uint32_t pageEntries = page.size();
            outFile.write(reinterpret_cast<const char*>(&pageEntries), sizeof(pageEntries));

            // Write each entry (pageID, pair of integers)
            for (const auto& [pageID, offsets] : page) {
                outFile.write(reinterpret_cast<const char*>(&pageID), sizeof(pageID));
                outFile.write(reinterpret_cast<const char*>(&offsets.first), sizeof(offsets.first));
                outFile.write(reinterpret_cast<const char*>(&offsets.second), sizeof(offsets.second));
            }
        }

        // Close the file
        outFile.close();
        std::cout << "Table directory serialized successfully at offset " << offset << " in " << filePath << std::endl;
        return true;
    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error serializing table directory: " << e.what() << std::endl;
        return false;
    }
}
