#include <iostream>
#include <fstream>
#include <string>

int getNum(const std::string line); 

int main(int argc, char **argv) {
    std::string line;
    std::ifstream myFile;
    // std::cout << argv[1] << std::endl;
    if (argc < 2) {
        std::cout << "Please provide a filename in the current directory to read" << std::endl;
    } else {
         myFile.open(argv[1]);
    }

    if (!myFile) {
        std::cout << "No such file in the directory\n";
    }

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            std::cout << line << '\n';
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}

int getNum(const std::string line) {
   for (char s : line) {
        if (s >= 48 && s <= 57) {
            
        }
   } 
}