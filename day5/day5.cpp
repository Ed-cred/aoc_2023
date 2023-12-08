#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int matchString(std::string &line); 
void matchMap(std::string &line , std::unordered_map<int, int> map);

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


    std::unordered_map<int,int> map;
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            std::cout << line << '\n'; 
            matchString(line);
        }
        myFile.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}

int matchString (std::string &line, std::unordered_map<int, int> map) {
    int pos = line.find(':');
    std::string token = line.substr(0, pos);
    if (token == "seeds") {
        std::string seeds = line.substr(pos + 2, std::string::npos);
        std::cout << "Seeds: " << seeds;
    } else if(int pos = line.find(':'); pos + 1 == std::string::npos) {
        map.clear();
    } else {
        matchMap(line, map);
    }
    return 0;
}

void matchMap(std::string &line , std::unordered_map<int, int> map) {
    int pos = line.find(' ');
    int dest = stoi(line.substr(0, pos));
    line.erase(0, pos + 1);
    int  src = stoi(line.substr(0,pos));
    line.erase(0, pos + 1);
    int len = stoi(line.substr(0, std::string::npos));
    for (int i = 0; i < len; i++) {

    }

}