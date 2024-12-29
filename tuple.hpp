#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <vector>
#include <string>
#include <utility>
#include <map>

class Tuple {
public:
    // Attributes
    std::vector<std::pair<std::string, std::pair<int, std::string>>> attributes;  // Vector of attributes (key, type-value pair)

    // Methods
    void add_attribute(const std::string& key, const std::string& value);  // Add an attribute to the tuple
    std::string get_attribute(const std::string& key);  // Get an attribute's value by key
    void update_attribute(const std::vector<std::pair<std::string, std::string>>& attributes);  // Update multiple attributes
    void Serialize();  // Serialize the tuple data
    void Deserialize();  // Deserialize the tuple data

private:
    // Additional private members can be added if needed for serialization
};

#endif // TUPLE_HPP
