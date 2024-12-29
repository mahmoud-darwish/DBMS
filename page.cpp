#include "page.hpp"
#include <iostream>

bool Page::insert_tuple(const std::vector<std::pair<std::string, std::pair<int, std::string>>>& attributes) {
    if (Page_MetaData + sizeof(attributes) > PAGE_SIZE) {
        std::cerr << "Not enough space to insert tuple." << std::endl;
        return false;
    }
    
    tuples.emplace_back(Tuple{attributes});
    Page_MetaData += sizeof(attributes);
    std::cout << "Tuple inserted successfully." << std::endl;
    return true;
}

Tuple* Page::get_tuple(const std::pair<std::string, std::string>& attribute) {
    for (auto& tuple : tuples) {
        if (tuple.get_attribute(attribute.first) == attribute.second) {
            return &tuple;
        }
    }
    std::cerr << "Tuple not found." << std::endl;
    return nullptr;
}

bool Page::update_tuple(const std::vector<std::pair<std::string, std::string>>& attributes) {
    for (auto& tuple : tuples) {
        tuple.update_attribute(attributes);
    }
    std::cout << "Tuple updated successfully." << std::endl;
    return true;
}

bool Page::del_tuple(const std::pair<std::string, std::string>& attribute) {
    for (auto it = tuples.begin(); it != tuples.end(); ++it) {
        if (it->get_attribute(attribute.first) == attribute.second) {
            tuples.erase(it);
            std::cout << "Tuple deleted successfully." << std::endl;
            return true;
        }
    }
    std::cerr << "Tuple not found to delete." << std::endl;
    return false;
}
