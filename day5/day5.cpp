#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void matchString (std::string &line, std::vector<size_t>& loc, std::vector<size_t>& copy);
void matchMap(std::string &line, std::vector<size_t>& loc, std::vector<size_t>& copy);

int main() {
    std::string line;
    std::ifstream myFile("input.txt");
    std::vector<size_t> loc;
    std::vector<size_t> copy;

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            matchString(line, loc, copy);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    
    size_t min = LLONG_MAX;
    for(auto& i : copy) {
        if (min > i) {
            min = i;
        }
        // std::cout << i << std::endl;
    }
    std::cout << min;
    return 0;
}


void matchString (std::string &line, std::vector<size_t>& loc, std::vector<size_t>& copy) {
    int pos = line.find(':');
    std::string token = line.substr(0, pos);
    if (token == "seeds") {
        std::string seeds = line.substr(pos + 2, std::string::npos);
        size_t pos = 0;
        size_t token;
        int i = 0;
        while((pos = seeds.find(' ')) != std::string::npos) {
            token = stoll(seeds.substr(0, pos));
            loc.push_back(token);
            seeds.erase(0, pos+1);
            i++;
        }
        token = stoll(seeds.substr(0, pos));
        loc.push_back(token);
        std::sort(loc.begin(), loc.end());
        for(auto& i : loc) {
            // std::cout << i << std::endl;
            copy.push_back(i);
        }
    } else if (isdigit(line[0])) {
        matchMap(line, loc, copy);
    } else {
        for(size_t i = 0; i < loc.size(); i ++) {
            loc[i] = copy[i];
        }

    }
}

void matchMap(std::string &line, std::vector<size_t>& loc, std::vector<size_t>& copy)  {
    size_t pos = line.find(' ');
    size_t dest = stoll(line.substr(0, pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    size_t  src = stoll(line.substr(0,pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    size_t len = stoll(line.substr(0, std::string::npos));
    size_t first = loc.front();
    if(src <= first || first < src + len) {
        for (size_t i = 0; i < len; i++) {
            for(size_t j = 0; j < loc.size(); j++) {
                if(loc[j] == src) {
                    // std::cout << "I'm here" << " " << src << " " << dest << std::endl;
                    copy[j] = dest;
                    break;
                }
            }
            size_t dif = loc.back() - src;
            src ++ ;
            dest ++ ;
        }
    }
}


