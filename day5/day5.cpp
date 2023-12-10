#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

int matchString (std::string &line, std::unordered_map<int, int> map);
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
            matchString(line, map);
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
    std::string d = line.substr(0, pos);
    int dest = stoi(d);
    std::cout << dest << std::endl;
    line.erase(0, pos + 1);
    std::string  s = line.substr(0,pos);
    int src = stoi(s);
    std::cout << src << std::endl;
    line.erase(0, pos + 1);
    std::string l = line.substr(0, std::string::npos);
    int len = stoi(l);
    // for (int i = 0; i < len; i++) {
    //     map[src] = dest;
    //     src++;
    //     dest++;
    //  }
    for (auto& i: map) {
        std::cout << i.first << " " << i.second << std::endl;
    }
}