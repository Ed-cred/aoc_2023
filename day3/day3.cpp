#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


int main(int argc , char **argv) {
    std::string line;
    std::ifstream myFile;
    if (argc < 2) {
        std::cout << "Please provide a filename in the current directory to read" << std::endl;
    } else {
        myFile.open(argv[1]);
    }
    if (!myFile) {
        std::cout << "No such file in the directory\n";
    }
    std::string strNum;
    if (myFile.is_open()) {
        char map[500][500];
        int i = 0;
        while (getline(myFile, line)) {
            int n = line.size();
            for (int j = 0; j < n; j++) {
                map[i][j] = line[j];
                std::cout << map[i][j];
            }
            i++;
            std::cout << '\n'; 
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}
