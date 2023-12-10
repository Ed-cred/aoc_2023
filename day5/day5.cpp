#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

int matchString (std::string &line, std::unordered_map<int, int> map);
void matchMap(std::string &line , std::unordered_map<int, int> map);
void setMap(std::unordered_map<int, int>& map); 

int main() {
    std::string line;
    std::ifstream myFile("test.txt");
    std::unordered_map<int,int> map;

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            matchString(line, map);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}

int matchString (std::string &line, std::unordered_map<int, int> map) {
    int pos = line.find(':');
    std::string token = line.substr(0, pos);
    if (token == "seeds") {
        std::string seeds = line.substr(pos + 2, std::string::npos);
        std::cout << "Seeds: " << seeds << std::endl;
    } else if(int pos = line.find(':'); pos + 1 == std::string::npos) {
        setMap(map);
    } else if (isdigit(line[0])) {
        matchMap(line, map);
    } 
    return 0;
}

void setMap(std::unordered_map<int, int>& map) {
    for (int i = 0; i < 100; i++) {
        map[i] = i;
    }
}

void matchMap(std::string &line , std::unordered_map<int, int> map) {
    int pos = line.find(' ');
    int dest = stoi(line.substr(0, pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    int  src = stoi(line.substr(0,pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    int len = stoi(line.substr(0, std::string::npos));
    for (int i = 0; i < len; i++) {
        map[src] = dest;
        src++;
        dest++;
    }
    for (auto& i: map) {
        std::cout << "Seed: " << i.first << " " << "Soil: " <<  i.second << std::endl;
    }
}