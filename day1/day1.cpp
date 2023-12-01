#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


int getNum(const std::string line); 
int getStringNum(std::string line, std::string strnum[], int &outMax, int size, int &outNum1, int &outNum2);

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
   std::string strnum[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
   int size = sizeof(strnum) / sizeof(strnum[0]);
   int outNum1 = 0;
   int outNum2 = 0;
   int digit1 = 0;
   int digit2 = 0;
   int j = line.size() - 1;
   int i = 0;
    int max = 0;
    size_t found1 = getStringNum(line, strnum, max, size, outNum1, outNum2);
    std::cout << "First word index: " << found1  << " represents -> " << outNum1 << std::endl;
    std::cout << "Last word index: " << max  << " represents -> " << outNum2 << std::endl;
    while (i <= j) {
        if (digit1 == 0 || digit2 == 0) {
            if (line[i] >= 48 && line[i] <= 57) {
                if (i < found1) {
                    digit1 = line[i] - '0';
                } else if ( i == found1) {
                    digit1 = outNum1;
                } else {
                    digit1 = outNum1;
                }
            } else {
                i++;
            }
            if (line[j] >= 48 && line[j] <= 57) {
                if (j > max) {
                    digit2 = line[j] - '0';
                } else if ( j == max) {
                    digit2 = outNum2;
                } else {
                    digit2 = outNum2;
                }
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

int getStringNum(std::string line, std::string strnum[], int &outMax, int size, int &outNum1, int &outNum2) {
    std::unordered_map<int, int> words;
    size_t found;
    for (int i = 0; i < size; i++) {
        found = line.find(strnum[i]);
        if (found != std::string::npos) {
            outNum1 = i + 1; 
            words[found] = outNum1;
        }
    }
    int min = size;
    int max = 0;
    for (auto i : words) {
        if (i.first < min ) {
            min = i.first;
        }
        if (i.first > max) {
            max = i.first;
        }
    }
    outMax = max;
    outNum2 = words[max];
    outNum1 = words[min];
    return min;
}