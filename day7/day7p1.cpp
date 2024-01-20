#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum handType {
  Five_kind = 6,
  Four_kind = 5,
  Full_house = 4,
  Three_kind = 3,
  Two_kind = 2,
  One_kind = 1,
  High_card = 0,
};

struct Hand {
  std::string cards;
  size_t bid;
  handType type;
};

Hand matchHand(std::string& line);

std::string labels = "AKQJT98765432";

int main() {
  std::string line;
  std::ifstream myFile("input.txt");
  std::vector<Hand> game;
  size_t result = 0;

  if (myFile.is_open()) {
    while (getline(myFile, line)) {
      Hand currHand = matchHand(line);
      game.push_back(currHand);
    }
    myFile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  std::sort(game.begin(), game.end(), [](Hand a, Hand b) {
    if (a.type == b.type) {
      for (int j = 0; j < 5; j++) {
        if (labels.find(a.cards[j]) < labels.find(b.cards[j])) {
          return false;
        } else if (labels.find(a.cards[j]) > labels.find(b.cards[j])) {
          return true;
        }
      }
    } else if (a.type > b.type) {
      return false;
    }
    return true;
  });

  size_t amount = 0;
  for (int i = 0; i < game.size(); i++) {
    amount = game[i].bid * (i + 1);
    result += amount;
  }
  std::cout << result << std::endl;
  return 0;
}

Hand matchHand(std::string& line) {
  Hand currHand;
  std::unordered_map<char, int> cardCount;
  std::vector<int> occurence;

  int pos = line.find(' ');
  currHand.cards = line.substr(0, pos);
  currHand.bid = stoi(line.substr(pos + 1, std::string::npos));

  for (const char& c : currHand.cards) {
    cardCount[c]++;
  }
  for (const auto [k, v] : cardCount) {
    occurence.push_back(v);
  }
  //a better way to count the cards might be nice
  std::sort(occurence.begin(), occurence.end(), std::greater<int>());
  // this is so terribly janky it's fun
  for (int i = 0; i < occurence.size(); ++i) {
    switch (occurence[i]) {
      case 5:
        currHand.type = Five_kind;
        break;
      case 4:
        currHand.type = Four_kind;
        break;
      case 3:
        if (i + 1 < occurence.size() && occurence[i + 1] == 2) {
          currHand.type = Full_house;
          break;
        }
        currHand.type = Three_kind;
        break;
      case 2:
        if (i + 1 < occurence.size() && occurence[i + 1] == 2) {
          currHand.type = Two_kind;
          break;
        }
        currHand.type = One_kind;
        break;
      default:
        currHand.type = High_card;
        break;
    }
    break;
  }
  return currHand;
}