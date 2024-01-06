#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

size_t matchLine (std::string &param);
size_t matchString (std::string &line);

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

std::string readFile2(const std::string &fileName) {
    std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

    std::ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    return std::string(bytes.data(), fileSize);
}

int main() {
    std::string contents = readFile2("input.txt");
    size_t res = matchString(contents);
    std::cout << res << std::endl;
    return 0;
}

size_t matchString (std::string &line){
   int pos = line.find('\n');
   size_t prod = 1;
   std::string time = line.substr(0, pos);
   size_t raceTime = matchLine(time);
   std::cout << raceTime << std::endl;
   std::string dist = line.substr(pos + 1, line.length() - 1);
   size_t raceDist = matchLine(dist);
   std::cout << raceDist << std::endl;
    size_t count = 0;
    for(size_t i = 0; i < raceTime; i++) {
        size_t traveled = (raceTime - i) * i;
        if(traveled > raceDist) {
            ++count;
            // std::cout << "counted -> " << i <<'\n';
        }
    }
   return count;
}

size_t matchLine (std::string &param) {
    int pos = param.find(':');
    std::string duration = param.substr(pos + 1, std::string::npos);
    ltrim(duration);
    size_t num = 0;
    while (pos = duration.find(' ') != std::string::npos) {
        ltrim(duration);
        int count = 0;
        int token = stoi(duration.substr(0, pos+4));
        int temp = token;
        while (temp != 0) {
            temp = temp / 10;
            ++count;
        }
        num = (num * pow(10, count)) + token;
        // std::cout << "Value -> " << time << '\n';
        duration.erase(0, pos + count);
    }
    return num;
}