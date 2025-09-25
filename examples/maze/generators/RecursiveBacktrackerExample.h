#ifndef RECURSIVEBACKTRACKER_H
#define RECURSIVEBACKTRACKER_H

#include "../MazeGeneratorBase.h"
#include "math/Point2D.h"
#include <map>
#include <stack>
#include <unordered_set>
#include <vector>

template<>
struct std::hash<std::pair<int, int>>
{
    std::size_t operator()(const std::pair<int, int>& s) const noexcept
    {
        return (size_t)s.first | ((size_t)s.second << 32);
    }
};

class RecursiveBacktrackerExample : public MazeGeneratorBase {
private:
  //std::vector<Point2D> stack;
  //std::map<int, std::map<int, bool>> visited;  // naive. not optimal
  Point2D randomStartPoint(World* world);
  std::vector<Point2D> getVisitables(World* w, const Point2D& p);
  std::stack<std::pair<int, int>> stack;
  std::unordered_set<std::pair<int, int>> visited;
  void removeWall(World* w, std::pair<int, int> current, std::pair<int, int> next);

public:
  RecursiveBacktrackerExample() = default;
  std::string GetName() override { return "Recursive Back-Tracker"; };
  bool Step(World* world) override;
  void Clear(World* world) override;
};

#endif  // RECURSIVEBACKTRACKER_H
