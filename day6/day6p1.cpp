#include <iostream>
#include <fstream>
#include <string>

void matchString (std::string &line);

int main() {
    std::string line;
    std::ifstream myFile("test.txt");

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            std::cout << line << std::endl;
            // matchString(line);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}

void matchString (std::string &line){

}
