#include <iostream>
#include <fstream>
#include <string>


int main(int argc , char **argv) {
    std::string line;
    std::ifstream myFile;
    int m[100][100];
    int i = 0;
    int n;
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
            n  = line.size();
            for (int j = 0; j < n; j++) {
                if (line[j] <= '9' && line[j] >= '0') {
                    m[i][j] = line[j] - '0';
                } else if (line[j] == 46) {
                    m[i][j] = 0;
                } else {
                    m[i][j] = -1;
                }
                std::cout << m[i][j] << " ";
            }
            i++;
            std::cout << '\n';
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    bool ok = false;
    int num;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] != 0 && m[i][j] != -1) {
                ok = false;
                if (m[i-1][j-1] == -1 && i - 1 >= 0 && j - 1 >= 0) {
                    ok = true;
                } else if (m[i-1][j] == -1 &&  i - 1 >= 0 ) {
                    ok = true;
                } else if (m[i-1][j+1] == -1 && i -1 >= 0 && j + 1 < n) {
                    ok = true;
                } else if (m[i][j-1] == -1 && j - 1 >= 0) {
                    ok = true;
                } else if (m[i][j+1] == -1 && j + 1 < n) {
                    ok = true;
                } else if (m[i+1][j-1] == -1 && i + 1 < n && j - 1 >= 0) {
                    ok = true;
                } else if (m[i+1][j] == -1 && i + 1 < n) {
                    ok = true;
                } else if(m[i+1][j+1] == -1 && i + 1 < n && j + 1 < n) {
                    ok = true;
                }
                if (ok) {
                    num = m[i][j];
                    while (m[i][j+1] > 0 && j + 1 < n) {
                       num = (num * 10) + m[i][j+1];
                       j++;
                    }
                    std::cout << m[i][j] << "index i: " << i << " index j: " << j << '\n';
                    std::cout << num;
                }
            }
        }
    }
    return 0;
}


