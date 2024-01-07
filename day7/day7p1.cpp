#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

enum handType {
    Five_kind = 5,
    Four_kind = 4,
    Full_house = 3,
    Three_kind = 2,
    Two_kind = 1,
    High_card = 0,
};

struct Hand {
    std::string cards;
    int bid;
    handType type;
};

Hand matchHand(std::string &line); 
void sortRank(std::vector<Hand> &hand); 

std::string labels = "AKQJT98765432";

int main() {
    std::string line;
    std::ifstream myFile("input.txt");
    std::vector<Hand> game;
    int result = 0;

    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            Hand currHand = matchHand(line);
            game.push_back(currHand);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    // std::sort(game.begin(), game.end(), &sortRank);
    sortRank(game);
    for(int i =0 ; i < game.size(); i++) {
        std::cout << game[i].cards << "->" << game[i].type << "->" << game[i].bid << std::endl;
        result += (game[i].bid * (i+1));
    }
        // std::cout << i.cards << "->" << i.bid  << "->" << i.type << std::endl;
    std::cout << result << std::endl;
    return 0;
}

Hand matchHand(std::string &line) {
   Hand currHand;
   std::unordered_map<char, int> cardCount;
   std::vector<int> occurence;
   int pos = line.find(' ');
   currHand.cards = line.substr(0, pos);
   currHand.bid = stoi(line.substr(pos + 1, std::string::npos));
   for(const char &c : currHand.cards) {
    cardCount[c]++;
   }
   for (const auto [k,v] : cardCount) {
    occurence.push_back(v);
   }
   //this is so terribly janky it's fun
   std::sort(occurence.begin(), occurence.end(), std::greater<int>());
   for (int i = 0; i < occurence.size(); ++ i) {
    if (occurence[i] == 5) {
        currHand.type = Five_kind;
        break;
    } else if (occurence[i] == 4) {
        currHand.type = Four_kind;
        break;
    } else if (occurence[i] == 3 && occurence[i+1] == 2 && i+1 < occurence.size()) {
        currHand.type = Full_house;
        break;
    } else if (occurence[i] == 3 && occurence[i+1] == 1 && i+1 < occurence.size()) {
        currHand.type = Three_kind;
        break;
    } else if (occurence[i] == 2) {
        currHand.type = Two_kind;
        break;
    } else if (occurence[i] == 1) {
        currHand.type = High_card;
        break; 
    }
   }
   return currHand;
}

void sortRank(std::vector<Hand> &hand) {
    bool ok = true;
    do {
        ok = true;
        for (int i = 0; i < hand.size(); ++i) {
            if(i+1 < hand.size() && hand[i].type == hand[i+1].type) {
                    for (int j = 0; j < 5; j++) {
                        if (labels.find(hand[i].cards[j]) < labels.find(hand[i+1].cards[j])) {
                            std::swap(hand[i], hand[i+1]);
                            ok = false;
                            break;
                        } else if (labels.find(hand[i].cards[j]) > labels.find(hand[i+1].cards[j])){
                            break;
                        }                 
                    }
            } else if (hand[i].type > hand[i+1].type && i + 1 < hand.size()) {
                std::swap(hand[i], hand[i+1]);
                ok = false;
            }
        }
    } while (!ok);
}