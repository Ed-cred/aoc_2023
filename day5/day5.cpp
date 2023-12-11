#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

int matchString (std::string &line, std::unordered_map<int, std::vector<int>>& seedsMap);
void matchMap(std::string &line , std::unordered_map<int, std::vector<int>>& seedsMap);

int main() {
    std::string line;
    std::ifstream myFile("test.txt");
    std::unordered_map<int, std::vector<int>> seedsMap;

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            matchString(line, seedsMap);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}

int matchString (std::string &line, std::unordered_map<int, std::vector<int>>& seedsMap) {
    int pos = line.find(':');
    std::string token = line.substr(0, pos);
    if (token == "seeds") {
        std::string seeds = line.substr(pos + 2, std::string::npos);
        size_t pos = 0;
        int token;
        while((pos = seeds.find(' ')) != std::string::npos) {
            token = stoi(seeds.substr(0, pos));
            seedsMap[token];
            seeds.erase(0, pos+1);
        }
        token = stoi(seeds.substr(0, pos));
        seedsMap[token];

        for(auto& [k, _] : seedsMap) {
            std::cout << k << ' ';
        }
    } else if (isdigit(line[0])) {
        matchMap(line, seedsMap);
    } 
    return 0;
}

void matchMap(std::string &line , std::unordered_map<int, std::vector<int>>& seedsMap) {
    int pos = line.find(' ');
    int dest = stoi(line.substr(0, pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    int  src = stoi(line.substr(0,pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    int len = stoi(line.substr(0, std::string::npos));
    for (int i = 0; i < len; i++) {
        if (seedsMap.find(src) != seedsMap.end()) {
        seedsMap[src].push_back(dest);
        src++;
        dest++;
    }
    // for (auto& i: map) {
    //     std::cout << "Seed: " << i.first << " " << "Soil: " <<  i.second << std::endl;
    // }
}