#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <span>
#include <spanstream>
#include <string>
#include <unordered_map>
#include <vector>

struct nodeNetwork {
  enum Direction { Left, Right };
  std::string& step(const std::string& state, Direction direction) {
    if (direction == Left) {
      return nodeMap[state].first;
    }
    return nodeMap[state].second;
  }
  // operator overloading to read from the stream
  friend std::istream& operator>>(std::istream& s, nodeNetwork& network) {
    auto dropChars = [&] {
      while (s && !std::isupper(s.peek())) {
        s.ignore();  // Ignore all chars that are not uppercase letters
      }
    };
    auto readPath = [&] {
      auto get = [&] { return static_cast<char>(s.get()); };
      return std::string{
          get(), get(),
          get()};  // Construct the string from the 3 characters read
    };
    while (!s.eof()) {
      dropChars();
      std::string location = readPath();
      dropChars();
      std::string left = readPath();
      dropChars();
      std::string right = readPath();
      network.nodeMap[location] = std::pair{left, right};
      dropChars();
      if (location[2] == 'A') {
        network.start.push_back(location);
      }
      dropChars();
    }
    return s;  // Return the input stream to allow for chaining(just learned
               // about this)
  }
  std::vector<std::string> start;
  std::unordered_map<std::string, std::pair<std::string, std::string>> nodeMap;
};

int64_t walk(std::span<const char> map);

int main() {
  std::string line;
  std::ifstream file("input.txt");
  std::string fileContent((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
  std::span<const char> fileSpan(fileContent.data(), fileContent.size());
  int64_t result = walk(fileSpan);
  std::cout << "Number of steps: " << result << std::endl;
  return 0;
}

int64_t walk(std::span<const char> map) {
  std::ispanstream ss(map);
  std::string instructions;
  ss >> instructions;  // ex: R->L
  nodeNetwork network;
  ss >> network;

  auto direction = [](int64_t pos, std::string_view instr) {
    if (instr[pos % instr.size()] == 'L') {
      // Learned this cool modulo trick that lets you loop through
      // the same string like it's a ring buffer
      return nodeNetwork::Left;
    }
    return nodeNetwork::Right;
  };

  int64_t result = 1;
  for (const auto& ghost : network.start) {
    std::string curr = ghost;
    int64_t steps = 0;
    while (curr[2] != 'Z') {
      curr = network.step(curr, direction(steps, instructions));
      ++steps;
    }
    result = std::lcm(result, steps); // this is a very neat way to make sure the ghosts are synced
  }
  return result;
}