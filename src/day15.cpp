#include "main.hpp"

struct Cell {
  int x, y;
  int risk;
  int distance;
  std::vector<std::pair<int, int>> adjacent;
};

class CellCompare {
public:
  constexpr bool operator()(const Cell &lhs, const Cell &rhs) {
    return lhs.distance > rhs.distance;
  }
};

void day15() {
  std::ifstream file("sample/day15");
  std::map<std::pair<int, int>, Cell> grid;
  int height = 0;
  int width = 0;
  while (file.good()) {
    std::string line;
    file >> line;
    if (line.empty()) {
      continue;
    }

    width = line.size();
    for (int i = 0; i < line.size(); i++) {
      grid[std::pair(i, height)] = Cell{
          i, height, i == 0 && height == 0 ? 0 : std::stoi(line.substr(i, 1)),
          i == 0 && height == 0 ? 0 : 999999};
    }
    height++;
  }

  std::map<std::pair<int, int>, bool> unvisited;
  for (auto &cell : grid) {
    unvisited.emplace(cell.first, true);

    if (cell.first.first + 1 < width) {
      cell.second.adjacent.push_back(
          std::pair(cell.first.first + 1, cell.first.second));
    }
    if (cell.first.first - 1 >= 0) {
      cell.second.adjacent.push_back(
          std::pair(cell.first.first - 1, cell.first.second));
    }
    if (cell.first.second + 1 < height) {
      cell.second.adjacent.push_back(
          std::pair(cell.first.first, cell.first.second + 1));
    }

    if (cell.first.second - 1 >= 0) {
      cell.second.adjacent.push_back(
          std::pair(cell.first.first, cell.first.second - 1));
    }
  }
  auto dest = std::make_pair(width - 1, height - 1);

  std::priority_queue<Cell, std::vector<Cell>, CellCompare> to_visit;
  to_visit.push(grid[std::pair(0, 0)]);
  while (!to_visit.empty()) {

    auto current = to_visit.top();
    to_visit.pop();
    auto current_coord = std::pair(current.x, current.y);

    for (auto next : grid[current_coord].adjacent) {

      int dist = grid[current_coord].distance + grid[next].risk;
      if (dist < grid[next].distance) {
        grid[next].distance = dist;
        to_visit.push(grid[next]);
      }
    }
  }

  int lowest_p1 = grid[dest].distance;

  std::cout << "Day 15 => Part 1: " << lowest_p1 
            << std::endl;
}
