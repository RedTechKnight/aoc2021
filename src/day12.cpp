#include "main.hpp"

int path_count_part1(std::map<std::string, std::vector<std::string>> &paths,
                     std::map<std::string, int> visited, std::string start) {

  if (start == "end") {
    return 1;
  }

  visited[start]++;

  std::vector<std::string> destinations;

  destinations = paths[start];
  if (destinations.empty()) {
    return 0;
  }
  int num_paths = 0;
  for (auto dest : destinations) {
    if (visited[dest] > 0 && std::all_of(dest.begin(), dest.end(), [](char c) {
          return std::islower(c);
        })) {
      continue;
    }

    num_paths += path_count_part1(paths, visited, dest);
  }
  return num_paths;
}


void day12() {
  std::ifstream file("inputs/day12");
  std::map<std::string, std::vector<std::string>> edges;
  while (file.good()) {
    std::string edge;
    file >> edge;
    std::replace(edge.begin(), edge.end(), '-', ' ');
    std::stringstream stream(edge);
    std::string a, b;
    stream >> a;
    stream >> b;

    if (!a.empty()) {
      edges[a].push_back(b);
      edges[b].push_back(a);
    }
  }
  std::map<std::string, int> visited;

  std::cout << "Day 12 => Part 1: "
            << path_count_part1(edges, visited, "start")
            
            << std::endl;
}
