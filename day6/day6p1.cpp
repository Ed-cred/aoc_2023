#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> matchLine (std::string &param);
void matchString (std::string &line);

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
    std::string line;
    std::ifstream myFile("test.txt");

    if (myFile.is_open()) {
        std::string contents = readFile2("test.txt");
        matchString(contents);
        // while (getline(myFile, line)) {
        //     std::cout << "Called " << line << std::endl;
        //     // matchString(line);
        // }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return 0;
}

void matchString (std::string &line){
   int pos = line.find('\n');
   std::string time = line.substr(0, pos);
   std::cout << time << std::endl;
   std::vector<int> raceTime = matchLine(time);
   std::string dist = line.substr(pos + 1, line.length() - 1);
   std::vector<int> raceDist = matchLine(dist);
}

std::vector<int> matchLine (std::string &param) {
    std::vector<int> result;
    int pos = param.find(':');
    std::string duration = param.substr(pos + 1, std::string::npos);
    std::cout << duration;
    ltrim(duration);
    std::cout << duration << '\n';
    while (pos = duration.find(' ') != std::string::npos) {
        int time = stoi(duration.substr(0, pos));
        ltrim(duration);
        result.push_back(time);
    }
    int time = stoi(duration.substr(0, pos));
    result.push_back(time);
    // for(const int &r : result) {
    //     std::cout << r << std::endl;
    // }
    return result;
}