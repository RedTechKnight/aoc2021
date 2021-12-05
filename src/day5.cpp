#include "main.hpp"

struct point {
  int x,y = 0;
};

struct line {
  point a,b;
};

void show(const line& line) {
  std::cout << "A(" << line.a.x <<","<<line.a.y<<") B("<<line.b.x <<","<<line.b.y<<")"<<std::endl;
}

void day5() {
  std::ifstream file("inputs/day5");
  std::vector<line> lines;
  point max = point{};
  while(file.good()) {
    line l = line{};
    file >> l.a.x;
    file.ignore(std::numeric_limits<std::streamsize>::max(),',');
    file >> l.a.y;
    file.ignore(std::numeric_limits<std::streamsize>::max(),'>');
    file >> l.b.x;
    file.ignore(std::numeric_limits<std::streamsize>::max(),',');
    file >> l.b.y;
    if(max.x < l.a.x) {
      max.x = l.a.x;
    }
    if(max.x < l.b.x) {
      max.x = l.b.x;
    }
    
    if(max.y < l.a.y) {
      max.y = l.a.y;
    }
    if(max.y < l.b.y) {
      max.y = l.b.y;
    }
    lines.push_back(l);
  }
  std::cout << "Max Point: " << max.x << ","<<max.y<<std::endl;
  for(auto l : lines) {
    show(l);
  }
  std::vector<int> grid;
  grid.resize((max.x+1)*(max.y+1));
  std::fill(grid.begin(),grid.end(),0);
  std::map<int,int> squares;
  auto move_closer = [](int a,int b) -> int {
    if(a < b) {
      return a+1;
    } else {
      return a-1;
    }
    
  };
  for(const auto &line : lines) {
    if(line.a.x == line.b.x) {
      for(int i = std::min(line.a.y,line.b.y);i <= std::max(line.a.y,line.b.y);i++) {
	grid[line.a.x + (max.x+1)*i]++;
	squares.insert({line.a.x + (max.x+1) * i,0});
	squares[line.a.x + (max.x+1) * i]++;
      }
    }
    else if(line.a.y == line.b.y) {
      for(int i = std::min(line.a.x,line.b.x);i <= std::max(line.a.x,line.b.x);i++) {
	grid[(max.x+1) * line.a.y + i]++;
	squares.insert({(max.x+1) * line.a.y + i,0});
	squares[(max.x+1) * line.a.y + i]++;
      }
    }
    else if(std::abs(line.a.x - line.b.x) == std::abs(line.a.y - line.b.y)) {
      point start = line.a;
      for(int i = 0;i <= std::abs(line.a.x - line.b.x);i++) {
	squares.insert({(max.x+1)*start.y + start.x,0});
	squares[(max.x+1)*start.y + start.x]++;
	start.x = move_closer(start.x,line.b.x);
	start.y = move_closer(start.y,line.b.y);
      }
    }
  }
  std::cout << std::count_if(grid.begin(),grid.end(),[](auto c){return c > 1;}) << std::endl;
  std::cout << std::count_if(squares.begin(),squares.end(),[](auto kv){return kv.second > 1;}) << std::endl;
}
