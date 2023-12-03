#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


int main(int argc , char **argv) {
    std::string line;
    std::ifstream myFile;
    int m[700][700];
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
    int sum = 0;
    bool ok = false;
    for (int i = 0; i < n; i++) {
        bool okv[1000];
        memset(okv, 0, sizeof(okv));
        for (int j = 0; j < n; j++) {
            ok = false;
            if (m[i][j] != 0 && m[i][j] != -1) {
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
                    okv[j] = true;
                }
                int k = j;
                if (m[i][j-1] <= 0) {
                    while (m[i][k+1] > 0 && k + 1 < n) {
                        m[i][k+1] = (m[i][k] * 10) + m[i][k+1];
                        if (okv[k]) {
                            okv[k+1] = true;
                        }
                        k++;
                    }
                }

                if (okv[j]) {
                    if (m[i][j+1] <= 0) {
                        sum += m[i][j];
                    }
                }
            }
        }
    }
    std::cout << "Sum: " << sum << '\n';
    return 0;
}