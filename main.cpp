#include "FileManager.hpp"
#include "DataBase.hpp"
#include <iostream>

int main() {
    // try {
    //     // // Example usage: DB name is "MyDatabase", and file name is "DataFile"
    //     // FileHandler& writer = FileHandler::getInstance("MyDatabase", "DataFile", std::ios::out);
        
    //     // // Writing data to the file
    //     // writer.writeData("This is a test line.\n");
    //     // writer.writeData("Here's another line in the file.\n");
        
    //     // // Flush the output buffer to ensure data is written to disk
    //     // writer.flush();

    //     // std::cout << "Data successfully written to: " << writer.getFilePath() << std::endl;

    //     // // Close the current write mode and reopen in read mode
    //     // writer.reopen(std::ios::in);

    //     // // Reading the data line by line using the new readLine() method
    //     // std::string line;
    //     // std::cout << "Reading data from the file:" << std::endl;
    //     // while (writer.readLine(line)) {
    //     //     std::cout << line << std::endl;
    //     // }

        DataBase db = DataBase("test");
        std::map<std::string, std::string> mp;

  
        mp["one"] = "Alice";
        mp["rwo"] = "Addlice";
        mp["ddd"] = "Addlice";
        mp["oddne"] = "Aliddce";
        db.createDatabase();
        db.createTable("table",mp);
        db.getTable("table");

    // } catch (const std::ios_base::failure& e) {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }

    return 0;
}
