#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> matchLine (std::string &param);
int matchString (std::string &line);

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
    int res = matchString(contents);
    std::cout << res << std::endl;
    return 0;
}

int matchString (std::string &line){
   int pos = line.find('\n');
   int prod = 1;
   std::string time = line.substr(0, pos);
   std::vector<int> raceTime = matchLine(time);
   std::string dist = line.substr(pos + 1, line.length() - 1);
   std::vector<int> raceDist = matchLine(dist);
   for(int i = 0; i < raceTime.size(); i ++) {
    int count = 0;
     for(int j = 0; j < raceTime[i]; j++) {
       int traveled = (raceTime[i] - j) * j;
       if(traveled > raceDist[i]) {
        count++;
       }
    }
     prod *= count;
   }
   return prod;
}

std::vector<int> matchLine (std::string &param) {
    std::vector<int> result;
    int pos = param.find(':');
    std::string duration = param.substr(pos + 1, std::string::npos);
    ltrim(duration);
    while (pos = duration.find(' ') != std::string::npos) {
        ltrim(duration);
        int count = 0;
        int time = stoi(duration.substr(0, pos+4));
        int temp = time;
        while (temp != 0) {
            temp = temp / 10;
            ++count;
        }
        std::cout << "Value -> " << time << '\n';
        duration.erase(0, pos + count);
        result.push_back(time);
    }
    return result;
}