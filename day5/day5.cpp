#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void matchString (std::string &line, std::vector<double>& loc, std::vector<double>& copy);
void matchMap(std::string &line, std::vector<double>& loc, std::vector<double>& copy);

int main() {
    std::string line;
    std::ifstream myFile("input.txt");
    std::vector<double> loc;
    std::vector<double> copy;

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            matchString(line, loc, copy);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    int min = INT_MAX;
    for(auto& i : copy) {
        if (min > i) {
            min = i;
        }
        std::cout << i << std::endl;
    }
    std::cout << min;
    return 0;
}


void matchString (std::string &line, std::vector<double>& loc, std::vector<double>& copy) {
    int pos = line.find(':');
    std::string token = line.substr(0, pos);
    if (token == "seeds") {
        std::string seeds = line.substr(pos + 2, std::string::npos);
        size_t pos = 0;
        double token;
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
            // std::cout << i << std::endl;
            copy.push_back(i);
        }
    } else if (isdigit(line[0])) {
        matchMap(line, loc, copy);
    } else {
        for(double i = 0; i < loc.size(); i ++) {
            loc[i] = copy[i];
        }

    }
}

void matchMap(std::string &line, std::vector<double>& loc, std::vector<double>& copy)  {
    size_t pos = line.find(' ');
    double dest = stoi(line.substr(0, pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    double  src = stoi(line.substr(0,pos));
    line.erase(0, pos + 1);
    pos = line.find(' ');
    double len = stoi(line.substr(0, std::string::npos));
    for (double i = 0; i < len; i++) {
        for(double j = 0; j < loc.size(); j++) {
            if(loc[j] == src) {
                // std::cout << "I'm here" << " " << src << " " << dest << std::endl;
                copy[j] = dest;
                break;
            }
        }
        src++;
        dest++;
    }
}


