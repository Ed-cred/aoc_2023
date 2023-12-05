#include <iostream>
#include <fstream>
#include <string>

int getSeeds (std::string &line); 

int main(int argc, char **argv) {
    std::string line;
    std::ifstream myFile;
    if (argc < 2) {
        std::cout << "Please provide a filename in the current directory to read" << std::endl;
    }
    else {
        myFile.open(argv[1]);
    }

    if (!myFile) {
        std::cout << "No such file in the directory\n";
    }

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            std::cout << line; 
        }
        myFile.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}

int getSeeds (std::string &line) {
    int pos = line.find(':');
    
    return 0;

}