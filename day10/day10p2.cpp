#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
    std::size_t h2 = std::hash<int64_t>{}(p.col);
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
  std::string contents = readFile2("input.txt");
  int64_t result = numberOfSteps(contents);
  std::cout << result << std::endl;
  return 0;
}

int64_t numberOfSteps(std::string_view maze) {
  std::vector<std::string_view> grid;
  std::ranges::copy(
      maze | std::views::split('\n') | std::views::transform([](auto&& range) {
        return std::string_view(range.begin(), range.end());
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

  char startSpace = [&] {
    if (canStep(start, {start.row - 1, start.col}) &&
        canStep(start, {start.row + 1, start.col})) {
      return '|';
    }
    if (canStep(start, {start.row, start.col - 1}) &&
        canStep(start, {start.row, start.col + 1})) {
      return '-';
    }
    if (canStep(start, {start.row - 1, start.col}) &&
        canStep(start, {start.row, start.col + 1})) {
      return 'L';
    }
    if (canStep(start, {start.row - 1, start.col}) &&
        canStep(start, {start.row, start.col - 1})) {
      return 'J';
    }
    if (canStep(start, {start.row + 1, start.col}) &&
        canStep(start, {start.row, start.col - 1})) {
      return '7';
    }
    if (canStep(start, {start.row + 1, start.col}) &&
        canStep(start, {start.row, start.col + 1})) {
      return 'F';
    }
    return '.';
  }();  // determine what kind of pipe S actually is

  auto getSpace = [&](Position to) {
    char space = grid[to.row][to.col];
    if (space == 'S') {
      return startSpace;
    }
    return space;
  };

  std::unordered_map<Position, int64_t> visited;
  std::queue<std::pair<Position, int64_t>> q;
  q.push({start, 0});
  visited[start] = 0;

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
    char space = getSpace(coord);
    if (space == '.') {
      continue;
    }
    auto [a, b] = offsets[space];
    if (tryVisit(coord, coord + a, distance + 1) ||
        tryVisit(coord, coord + b, distance + 1)) {
      break;
    }
  }  // BFS to find the loop

  std::unordered_set<Position> expandedVisited;
  auto expandedCanStep = [&](Position to) {
    if (to.row < 0 || to.col < 0) {
      return false;
    }
    // canStep but with fake spaces accounted
    if (to.row > std::ssize(grid) * 2) {
      return false;
    }
    if (to.col > std::ssize(grid[0]) * 2) {
      return false;
    }

    if (expandedVisited.contains(to)) {
      return false;  // already visited
    }
    // All odd positions are part of the original grid
    // and this should avoid spaces that are part of the loop
    if (to.row % 2 != 0 && to.col % 2 != 0) {
      if (visited.contains(Position{(to.row - 1) / 2, (to.col - 1) / 2})) {
        return false;
      }
    }

    if (to.row % 2 == 0 && to.col % 2 != 0 && to.row != 0 &&
        to.row != std::ssize(grid) * 2) {
      auto north = Position{(to.row - 2) / 2, (to.col - 1) / 2};
      auto south = Position{(to.row) / 2, (to.col - 1) / 2};
      // check if they are part of the loop
      if (!(visited.contains(north) && visited.contains(south))) {
        return true;
      }
      // check for a connection between them
      if ((north == south + offsets[getSpace(south)].first ||
           north == south + offsets[getSpace(south)].second) &&
          (south == north + offsets[getSpace(north)].first ||
           south == north + offsets[getSpace(north)].second)) {
        return false;
      }
    }
    // same check as before but this time for horizontal case
    if (to.row % 2 != 0 && to.col % 2 == 0 && to.col != 0 &&
        to.col != std::ssize(grid) * 2) {
      auto west = Position{(to.row - 1) / 2, (to.col - 2) / 2};
      auto east = Position{(to.row - 1) / 2, (to.col) / 2};
      // check if they are part of the loop
      if (!(visited.contains(west) && visited.contains(east))) {
        return true;
      }
      // check for a connection between them
      if ((west == east + offsets[getSpace(east)].first ||
           west == east + offsets[getSpace(east)].second) &&
          (east == west + offsets[getSpace(west)].first ||
           east == west + offsets[getSpace(west)].second)) {
        return false;
      }
    }
    return true;
  };

  std::queue<Position> expandedQ;
  expandedQ.push({0, 0});
  expandedVisited.insert({0, 0});

  while (!expandedQ.empty()) {
    auto coord = expandedQ.front();
    expandedQ.pop();
    if (expandedCanStep({coord.row - 1, coord.col})) {
      expandedVisited.insert({coord.row - 1, coord.col});
      expandedQ.push({coord.row - 1, coord.col});
    }
    if (expandedCanStep({coord.row + 1, coord.col})) {
      expandedVisited.insert({coord.row + 1, coord.col});
      expandedQ.push({coord.row + 1, coord.col});
    }
    if (expandedCanStep({coord.row, coord.col + 1})) {
      expandedVisited.insert({coord.row, coord.col + 1});
      expandedQ.push({coord.row, coord.col + 1});
    }
    if (expandedCanStep({coord.row, coord.col - 1})) {
      expandedVisited.insert({coord.row, coord.col - 1});
      expandedQ.push({coord.row, coord.col - 1});
    }
  }  // BFS to find all other accesible positions outside the loop

  // After this step visited should contain the positions of the loop
  // and expandedVisited should have all spaces that we can
  // reach from outside the loop

  int64_t contained = std::ssize(grid) * std::ssize(grid[0]);
  contained -= std::ranges::count_if(expandedVisited, [](auto& c) {
    return c.row % 2 != 0 && c.col % 2 != 0;
  });                                // remove outside  elements
  contained -= std::ssize(visited);  // remove loop elements
  return contained;
}