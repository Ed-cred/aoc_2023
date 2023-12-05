#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void matchNum(std::string &line, int cardnum[], int& size);
int totalCards(int cardnum[], int& size, int& cardcount); 
// static inline void ltrim(std::string &s) {
//     s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
//         return !std::isspace(ch);
//     }));
// }

int main(int argc, char **argv)
{
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
    int cardnum[202];
    int cardsize = sizeof(cardnum) / sizeof(cardnum[0]);
    for (int i = 0; i < cardsize ; i++) {
        if (i == 0) {
            cardnum[i] = 0;
        } else {
            cardnum[i] = 1;
        }
    } 
    int cardcount = 0;
    if (myFile.is_open())
    {
        
        while (getline(myFile, line))
        {
            matchNum(line, cardnum, cardsize);
            cardcount++;
        }
        myFile.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
    int cards = totalCards(cardnum, cardsize, cardcount);
    std::cout << "Sum: " << cards;
    return 0;
}

void matchNum(std::string &line, int cardnum[], int& size)
{
    int win[100];
    memset(win, 0, sizeof(win));

    int pos = line.find(": ");
    std::string strID = line.substr(line.find(" "), line.find(":"));
    int id = stoi(strID);
    std::cout << "card id: " << id << std::endl;

    std::string token = line.substr(0, pos);
    line.erase(0, pos + 2);
    pos = line.find('|');
    std::string winners = line.substr(0, pos);
    line.erase(0, pos + 2);

    std::string elfers = line.substr(0, std::string::npos);
    std::string strnum;
    for (int i = 0; i < winners.size(); i++)
    {
        if (isdigit(winners[i]))
        {
            strnum = winners[i];
            int k = i;
            while (isdigit(winners[i + 1]) && i + 1 < winners.size())
            {
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
    }
    std::string elfnum;
    int winsize = sizeof(win) / sizeof(win[0]);
    int counter = 0;
    int mlt = cardnum[id];
    for (int i = 0; i < elfers.size(); i++)
    {

        if (isdigit(elfers[i]))
        {
            elfnum = elfers[i];
            int k = i;
            while (isdigit(elfers[i + 1]) && i + 1 < elfers.size())
            {
                elfnum = elfnum + elfers[i + 1];
                i++;
            }
            int num = stoi(elfnum);
            for (int j = 0; j < winsize; j++)
            {
                if (num == win[j])
                {
                    counter++;
                }
            }
            elfnum.clear();
        }
        else
        {
            continue;
        }
    }
    int rbound = id + counter;
    if (rbound >= size)
    {
        rbound = size - 2;
    }
    for (int k = id + 1; k <= rbound; k++)
    {
        cardnum[k] += mlt;
    }
}

int totalCards(int cardnum[], int& size, int& cardcount) {
    int sum = 0;
    for (int i = 1; i <= cardcount; i++) {
        sum += cardnum[i];
    }
    return sum;
}