#include "tuple.hpp"
#include <iostream>

void Tuple::add_attribute(const std::string& key, const std::string& value) {
    attributes.emplace_back(key, std::make_pair(value.size(), value));
    std::cout << "Attribute added: " << key << " = " << value << std::endl;
}

std::string Tuple::get_attribute(const std::string& key) {
    for (const auto& attr : attributes) {
        if (attr.first == key) {
            return attr.second.second;
        }
    }
    std::cerr << "Attribute not found: " << key << std::endl;
    return "";
}

void Tuple::update_attribute(const std::vector<std::pair<std::string, std::string>>& attributes) {
    for (const auto& update : attributes) {
        for (auto& attr : this->attributes) {
            if (attr.first == update.first) {
                attr.second.second = update.second;
                attr.second.first = update.second.size();
                std::cout << "Attribute updated: " << update.first << " = " << update.second << std::endl;
                break;
            }
        }
    }
}

void Tuple::Serialize() {
    // Placeholder for serialization logic
    std::cout << "Tuple serialized." << std::endl;
}

void Tuple::Deserialize() {
    // Placeholder for deserialization logic
    std::cout << "Tuple deserialized." << std::endl;
}
