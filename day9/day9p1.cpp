#include <algorithm>
#include <cstdint>
#include <functional>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

std::vector<int64_t> formatInput(std::string& line); 
int64_t getPrediction(std::vector<int64_t>& history); 

int main() {
  std::string line;
  std::ifstream myFile("input.txt");
  int64_t result = 0;

  if (myFile.is_open()) {
    while (getline(myFile, line)) {
        std::vector<int64_t> history = formatInput(line);
        int64_t prediction = getPrediction(history);
        result += prediction;
    }
    myFile.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }
  std::cout << result << std::endl;
  return 0;
}

std::vector<int64_t> formatInput(std::string& line) {
  int pos = 0;
  std::vector<int64_t> history;
  while((pos = line.find(' ')) != std::string::npos) {
    history.push_back(stoll(line.substr(0, pos)));
    line.erase(0, pos + 1);
  }
  history.push_back(stoll(line.substr(0, pos)));
  return history;
}

int64_t getPrediction(std::vector<int64_t>& history) {
  auto diff =[](int64_t left, int64_t right) {return right - left;};
  std::vector<int64_t> tails;
  tails.push_back(history.back());
  do {
    std::vector<int64_t> nextHistory;
    std::ranges::copy(history | std::views::pairwise_transform(diff), std::back_inserter(nextHistory));
    if (std::ranges::all_of(nextHistory, [](int64_t v) { return v == 0; })) {
      break;
    }
    tails.push_back(nextHistory.back());
    history = std::move(nextHistory);
  } while(true);
  return std::ranges::fold_left(tails, 0, std::plus<>{});
}