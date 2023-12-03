#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 


//12 red; 13 green; 14 blue
enum Color {
    red,
    green,
    blue
};

int validateGame(std::string& line);
void validateSet(std::string& set, std::vector<int>& minCubes); 
void validateCube(std::string& cube, std::vector<int>& minCubes); 

//trim function from stack overflow
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

int main(int argc , char **argv) {
    std::string line;
    std::ifstream myFile;
    int sum = 0;
    if (argc < 2) {
        std::cout << "Please provide a filename in the current directory to read" << std::endl;
    } else {
        myFile.open(argv[1]);
    }

    if (!myFile) {
        std::cout << "No such file in the directory\n";
    }

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            int id = validateGame(line);
            sum += id;
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    std::cout << "Sum: " << sum << '\n';
    return 0;
}

//Returns the product of the min values of cubes
int validateGame(std::string& line) {
   std::vector<int> minCubes = {0, 0, 0};
   std::string setDelimeter = ";";
   std::string gameDelimeter = ":";
   
   line.erase(0, line.find(gameDelimeter) + gameDelimeter.length());
   size_t pos = 0;
   std::string token;
   while ((pos = line.find(setDelimeter)) != std::string::npos) {
        token = line.substr(0, pos);
        validateSet(token, minCubes);
        line.erase(0, pos + setDelimeter.length());
   }
   token = line.substr(0, pos);
   validateSet(token, minCubes);
   int power = 1;
   for (auto& i : minCubes) {
        power *= i;
   }
   return power;
}

void validateSet(std::string& set, std::vector<int>& minCubes) {
    std::string cubeDelimeter = ",";
    std::string cube;
    size_t pos = 0;
    while((pos = set.find(cubeDelimeter)) != std::string::npos) {
        cube = set.substr(0, pos);
        validateCube(cube, minCubes);
        set.erase(0, pos + cubeDelimeter.length() + 1);
    }
    cube = set.substr(0, pos);
    validateCube(cube, minCubes);

}

void validateCube(std::string& cube, std::vector<int>& minCubes) {
    ltrim(cube);
    Color c;
    size_t posCube = 0;
    posCube = cube.find(' ');
    std::string strNum = cube.substr(0, posCube);
    // +1 because there is a space after every comma
    std::string color = cube.substr(posCube + 1, std::string::npos);
    if (color == "red") {
        c = red;
        if (stoi(strNum) > minCubes[c] ) {
            minCubes[c] = stoi(strNum);
        }
    } else if (color == "green") {
        c = green;
        if (stoi(strNum) > minCubes[c] ) {
            minCubes[c] = stoi(strNum);
        }
    } else if (color == "blue") {
        c = blue;
        if (stoi(strNum) > minCubes[c] ) {
            minCubes[c] = stoi(strNum);
        }
    }
    std::cout << strNum << " -> " << color << '\n';
}