#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

enum Card {
  Joker,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Queen,
  King,
  Ace
};

enum handType {
  HighCard,
  OnePair,
  TwoPair,
  ThreeKind,
  FullHouse,
  FourKind,
  FiveKind
};

struct Hand {
  std::string cards;
  size_t bid;
  handType type;
};

Hand matchHand(std::string& line);
std::array<Card, 5> setValues(std::string& cards);

std::string labels = "AKQT98765432J";

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
  int pos = line.find(' ');
  currHand.cards = line.substr(0, pos);
  std::array<Card, 5> sortedCards = setValues(currHand.cards);
  currHand.bid = stoi(line.substr(pos + 1, std::string::npos));
  std::sort(sortedCards.begin(), sortedCards.end(), std::greater<int>());
  if (sortedCards[0] == Joker) {
    currHand.type = FiveKind;  // special case for all Jokers hand
    return currHand;
  }
  // we can make use of std::array because we know
  // all hands will always have 5 cards
  std::array<int, 5> frequency = {1, 0, 0, 0, 0};
  int jokers = 0;
  auto it = frequency.begin();
  for (int i = 1; i < 5; ++i) {
    if (sortedCards[i] == Joker) {
      ++jokers;
      continue;
    }
    if (sortedCards[i - 1] != sortedCards[i]) {
      ++it;
    }
    ++*it;  // increment the current value in the frequency array by
            // dereferencing the iterator
  }
  std::sort(frequency.begin(), frequency.end(), std::greater<int>());
  // this whole switch business that is happening here might be bad style
  //  or bad practice but it does get the job done
  switch (frequency[0]) {
    case 5:
      currHand.type = FiveKind;
      break;
    case 4:
      if (jokers == 0) {
        currHand.type = FourKind;
      } else if (jokers == 1) {
        currHand.type = FiveKind;
      }
      break;
    case 3:
      if (frequency[1] == 2) {
        currHand.type = FullHouse;
        break;
      } else if (jokers == 1) {
        currHand.type = FourKind;
        break;
      } else if (jokers == 2) {
        currHand.type = FiveKind;
        break;
      }
      currHand.type = ThreeKind;
      break;
    case 2:
      if (frequency[1] == 2 && jokers == 0) {
        currHand.type = TwoPair;
        break;
      } else if (frequency[1] == 2 && jokers == 1) {
        currHand.type = FullHouse;
        break;
      }
      if (frequency[1] != 2 && jokers == 0) {
        currHand.type = OnePair;
        break;
      } else if (frequency[1] != 2 && jokers == 1) {
        currHand.type = ThreeKind;
        break;
      } else if (frequency[1] != 2 && jokers == 2) {
        currHand.type = FourKind;
        break;
      } else if (frequency[1] != 2 && jokers == 3) {
        currHand.type = FiveKind;
        break;
      }
    default:
      if (jokers == 0) {
        currHand.type = HighCard;
        break;
      } else if (jokers == 1) {
        currHand.type = OnePair;
        break;
      } else if (jokers == 2) {
        currHand.type = ThreeKind;
        break;
      } else if (jokers == 3) {
        currHand.type = FourKind;
        break;
      } else if (jokers == 4) {
        currHand.type = FiveKind;
        break;
      }
  }
  return currHand;
}

std::array<Card, 5> setValues(std::string& cards) {
  std::array<Card, 5> result;
  for (int i = 0; i < 5; ++i) {
    switch (cards[i]) {
      case 'J':
        result[i] = Joker;
        break;
      case '2':
        result[i] = Two;
        break;
      case '3':
        result[i] = Three;
        break;
      case '4':
        result[i] = Four;
        break;
      case '5':
        result[i] = Five;
        break;
      case '6':
        result[i] = Six;
        break;
      case '7':
        result[i] = Seven;
        break;
      case '8':
        result[i] = Eight;
        break;
      case '9':
        result[i] = Nine;
        break;
      case 'T':
        result[i] = Ten;
        break;
      case 'Q':
        result[i] = Queen;
        break;
      case 'K':
        result[i] = King;
        break;
      case 'A':
        result[i] = Ace;
        break;
    }
  }
  return result;
}