#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void matchString (std::string &line, std::vector<int>& loc, std::vector<int>& copy);
void matchMap(std::string &line, std::vector<int>& loc, std::vector<int>& copy);

int main() {
    std::string line;
    std::ifstream myFile("test.txt");
    std::vector<int> loc;
    std::vector<int> copy;

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            matchString(line, loc, copy);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    for(int i : copy) {
        std::cout << i << std::endl;
    }
    return 0;
}


void matchString (std::string &line, std::vector<int>& loc, std::vector<int>& copy) {
    int pos = line.find(':');
    std::string token = line.substr(0, pos);
    if (token == "seeds") {
        std::string seeds = line.substr(pos + 2, std::string::npos);
        size_t pos = 0;
        int token;
        int i = 0;
        while((pos = seeds.find(' ')) != std::string::npos) {
            token = stoi(seeds.substr(0, pos));
            loc.push_back(token);
            seeds.erase(0, pos+1);
            i++;
        }
        token = stoi(seeds.substr(0, pos));
        loc.push_back(token);
        for(auto& i : loc) {
            std::cout << i << std::endl;
            copy.push_back(i);
        }
    } else if (isdigit(line[0])) {
        matchMap(line, loc, copy);
    } else if ((pos = line.find(':')) + 1 == std::string::npos) {
        for(auto& i : copy) {
            loc.push_back(i);
        }
    }
}

void matchMap(std::string &line, std::vector<int>& loc, std::vector<int>& copy)  {
    int pos = line.find(' ');
    int dest = stoi(line.substr(0, pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    int  src = stoi(line.substr(0,pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    int len = stoi(line.substr(0, std::string::npos));
    for (int i = 0; i < len; i++) {
        for(int j = 0; j < loc.size(); j++) {
            if(loc[j] == src) {
                std::cout << "I'm here" << " " << src << " " << dest << std::endl;
                copy[j] = dest;
                break;
            }
        }
        src++;
        dest++;
    }
}


