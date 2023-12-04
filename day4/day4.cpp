#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int matchNum(std::string &line);
// static inline void ltrim(std::string &s) {
//     s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
//         return !std::isspace(ch);
//     }));
// }

int main(int argc, char **argv) {
    std::string line;
    std::ifstream myFile;
    if (argc < 2)
    {
        std::cout << "Please provide a filename in the current directory to read" << std::endl;
    }
    else
    {
        myFile.open(argv[1]);
    }

    if (!myFile)
    {
        std::cout << "No such file in the directory\n";
    }

    int sum = 0;
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            int points = matchNum(line);
            std::cout << "Card points -> " << points << '\n';
            sum += points;
        }
        myFile.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
    std::cout << "Sum: " << sum;
    return 0;
}

int matchNum(std::string &line) {
    int win[50];
    memset(win, 0, sizeof(win));
    int pos = line.find(": ");
    line.erase(0, pos + 2);
    pos = line.find('|');
    std::string winners = line.substr(0, pos);
    line.erase(0, pos + 2);
    std::string elfers = line.substr(0, std::string::npos);
    int points = 0;
    std::string strnum;
    for (int i = 0; i < winners.size(); i++) {
        if (isdigit(winners[i])) {
            strnum = winners[i];
            int k = i;
            while (isdigit(winners[i + 1]) && i + 1 < winners.size()) {
                strnum = strnum + winners[i + 1];
                i++;
            }
            win[i] = stoi(strnum);
            strnum.clear();
        }
        else
        {
            continue;
        }
        std::cout << win[i] << " at index " << i << std::endl;
    }
    std::string elfnum;
    int winsize = sizeof(win) / sizeof(win[0]);
    for (int i = 0; i < elfers.size(); i++) {
        if (isdigit(elfers[i])) {
            elfnum = elfers[i];
            int k = i;
            while (isdigit(elfers[i + 1]) && i + 1 < elfers.size()) {
                elfnum = elfnum + elfers[i + 1];
                i++;
            }
            int num = stoi(elfnum);
            for (int j = 0; j < winsize; j++) {
                if (num == win[j]) {
                    if (points >= 1) {
                        points *= 2;
                    }
                    else {
                        points = 1;
                    }
                }
            }
            elfnum.clear();
        }
        else {
            continue;
        }
    }
    return points;
}
// 3199 too low