#ifndef LIFE_WORLD_H
#define LIFE_WORLD_H

#include "math/Point2D.h"

#include <unordered_set>
#include <vector>

struct World {
private:
  // double buffer approach to avoid memory reallocation
  std::vector<bool> buffer[2];
  int currentBufferId;
  int sideSize;
  inline std::vector<bool>& currentBuffer() { return buffer[currentBufferId % 2]; }
  inline std::vector<bool>& nextBuffer() { return buffer[(currentBufferId + 1) % 2]; }

public:
  std::unordered_set<size_t> alive;
  std::unordered_set<size_t> deadNeighbors;
  std::unordered_set<size_t> nextState;
  inline const int& SideSize() const { return sideSize; };
  void Resize(int sideSize);
  // to be called at the end of the frame
  void SwapBuffers();
  // todo: make it follow the standard at() function that returns the exactly element
  bool Get(Point2D point);
  // todo: make it follow the standard at() function that returns the exactly element
  void SetNext(Point2D point, bool value);
  void SetCurrent(Point2D point, bool value);
  void Randomize();
  std::unordered_set<size_t> getAliveCells();
  void setNextState(const std::unordered_set<size_t>& nextState) { this->nextState = nextState; };
};

#endif  // MOBAGEN_WORLD_H
