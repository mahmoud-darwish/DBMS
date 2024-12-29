#ifndef PAGE_HPP
#define PAGE_HPP

#include <vector>
#include <string>
#include <map>
#include <utility>
#define PAGE_SIZE 4096
// Forward declaration of the Tuple class
#include "tuple.hpp"
class Page {
public:
    // Attributes
    int Page_MetaData;  // Metadata for the page
    std::vector<Tuple> tuples; // Vector of tuples
    char* PageData[PAGE_SIZE];
    // Methods
    bool insert_tuple(const std::vector<std::pair<std::string, std::pair<int, std::string>>>& attributes);
    Tuple* get_tuple(const std::pair<std::string, std::string>& attribute);
    bool update_tuple(const std::vector<std::pair<std::string, std::string>>& attributes);
    bool del_tuple(const std::pair<std::string, std::string>& attribute);

private:
    // Additional private members can be added if needed
};

#endif // PAGE_HPP
