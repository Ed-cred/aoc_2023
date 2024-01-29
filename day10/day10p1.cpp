#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

struct Position {
  int64_t row;
  int64_t col;
  auto operator<=>(const Position&) const = default;
  Position operator+(const Position& other) {
    return Position{row + other.row, col + other.col};
  }
};

template <>
struct std::hash<Position> {
  std::size_t operator()(const Position& p) const {
    std::size_t h1 = std::hash<int64_t>{}(p.row);
    std::size_t h2 = std::hash<int64_t>{}(p.row);
    return h1 ^ (h2 << 1);
  }
};

int64_t numberOfSteps(std::string_view maze);

std::string readFile2(const std::string& fileName) {
  std::ifstream ifs(fileName.c_str(),
                    std::ios::in | std::ios::binary | std::ios::ate);

  std::ifstream::pos_type fileSize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::vector<char> bytes(fileSize);
  ifs.read(bytes.data(), fileSize);

  return std::string(bytes.data(), fileSize);
}

int main() {
  std::string contents = readFile2("test.txt");
  int64_t result = numberOfSteps(contents);
  std::cout << result << std::endl;
  return 0;
}

int64_t numberOfSteps(std::string_view maze) {
  std::vector<std::string_view> grid;
  std::ranges::copy(
      maze | std::views::split('\n') | std::views::transform([](auto&& rng) {
        return std::string_view(rng.begin(), rng.end());
      }),
      std::back_inserter(grid));  // constructing an array of strings

  Position start = [&] {
    for (int64_t r = 0; r < std::ssize(grid); ++r) {
      for (int64_t c = 0; c < std::ssize(grid); ++c) {
        if (grid[r][c] == 'S') {
          return Position{r, c};
        }
      }
    }
    return Position{0, 0};
  }();

  std::unordered_map<char, std::pair<Position, Position>> offsets{
      {'|', {{-1, 0}, {+1, 0}}}, {'-', {{0, -1}, {0, +1}}},
      {'L', {{-1, 0}, {0, +1}}}, {'J', {{-1, 0}, {0, -1}}},
      {'7', {{+1, 0}, {0, -1}}}, {'F', {{+1, 0}, {0, +1}}},
  };

  std::unordered_map<Position, int64_t> visited;
  std::queue<std::pair<Position, int64_t>> q;
  q.push({start, 0});
  visited[start] = 0;

  auto canStep = [&](Position from, Position to) {
    // out of bounds
    if (to.row < 0 || to.col < 0) {
      return false;
    }
    if (to.row >= std::ssize(grid)) {
      return false;
    }
    if (to.col >= std::ssize(grid[to.row])) {
      return false;
    }
    // check pipe connection
    auto [a, b] = offsets[grid[to.row][to.col]];
    if (from != to + a && from != to + b) {
      return false;
    }
    return true;
  };

  auto tryVisit = [&](Position from, Position to, int64_t distance) {
    if (!canStep(from, to)) {
      return false;
    }
    auto iter = visited.find(to);
    if (iter != visited.end()) {
      if (iter->second != distance) {
        return false;
      }
      return true;
    }
    q.push({to, distance});
    visited[to] = distance;
    return false;
  };

  while (!q.empty()) {
    auto [coord, distance] = q.front();
    q.pop();

    if (grid[coord.row][coord.col] == 'S') {
      // handles the starting point
      tryVisit(coord, {coord.row + 1, coord.col}, distance + 1);
      tryVisit(coord, {coord.row - 1, coord.col}, distance + 1);
      tryVisit(coord, {coord.row, coord.col + 1}, distance + 1);
      tryVisit(coord, {coord.row, coord.col - 1}, distance + 1);
    }
    if (grid[coord.row][coord.col] == '.') {
      continue;
    }
    auto [a, b] = offsets[grid[coord.row][coord.col]];
    if (tryVisit(coord, coord + a, distance + 1) ||
        tryVisit(coord, coord + b, distance + 1)) {
      return distance + 1;
    }
  }
  return 0;
}