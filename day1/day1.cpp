#include <iostream>
#include <fstream>
#include <string>

int getNum(const std::string line); 

int main(int argc, char **argv) {
    std::string line;
    std::ifstream myFile;
    int sum = 0;
    int num = 0;
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
            num = getNum(line);
            std::cout << line << ": " << num << '\n';
            sum += num;
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    std::cout << sum;
    return 0;
}

int getNum(std::string line) {
   int digit1 = -1;
   int digit2 = -1;
   int j = line.size() - 1;
   int i = 0;
    while (i <= j) {
        if (digit1 == -1 || digit2 == -1) {
            if (line[i] >= 48 && line[i] <= 57) {
                digit1 = line[i] - '0';
            } else {
                i++;
            }
            if (line[j] >= 48 && line[j] <= 57) {
                digit2 = line[j] - '0';
            } else {
                j--;
            } 
        } else {
            break;
        }
    }
    int result = (digit1 * 10) + digit2;
    return result;
}