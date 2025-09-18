#include "World.h"
#include "Random.h"
void World::Resize(int size) {
  currentBufferId = 0;
  sideSize = size;
  buffer[0].clear();
  buffer[0].resize(size * size);
  buffer[1].clear();
  buffer[1].resize(size * size);
}
void World::SwapBuffers() {
  //currentBufferId = (currentBufferId + 1) % 2;
  //for (int i = 0; i < buffer[currentBufferId].size(); i++) buffer[(currentBufferId + 1) % 2][i] = buffer[currentBufferId][i];
  std::swap(alive, nextState);
}
// todo: improve those set / get accessors
void World::SetNext(Point2D point, bool value) {
  // if (point.x < 0) point.x += sideSize;
  // if (point.x >= sideSize) point.x %= sideSize;
  // if (point.y < 0) point.y += sideSize;
  // if (point.y >= sideSize) point.y %= sideSize;
  // auto index = point.y * sideSize + point.x;
  // auto sideSquared = sideSize * sideSize;
  // if (index >= sideSquared) index %= sideSquared;
  // buffer[(currentBufferId + 1) % 2][index] = value;

  if (point.x < 0)
    point.x += sideSize;

  if (point.x >= sideSize)
    point.x %= sideSize;

  if (point.y < 0)
    point.y += sideSize;

  if (point.y >= sideSize)
    point.y %= sideSize;

  if (value)
    nextState.insert(Point2D::hash(point));
}
// todo: improve those set / get accessors
void World::SetCurrent(Point2D point, bool value) {
  // if (point.x < 0) point.x += sideSize;
  // if (point.x >= sideSize) point.x %= sideSize;
  // if (point.y < 0) point.y += sideSize;
  // if (point.y >= sideSize) point.y %= sideSize;
  // auto index = point.y * sideSize + point.x;
  // auto sideSquared = sideSize * sideSize;
  // if (index >= sideSquared) index %= sideSquared;
  // buffer[currentBufferId % 2][index] = value;

  if (point.x < 0)
    point.x += sideSize;

  if (point.x >= sideSize)
    point.x %= sideSize;

  if (point.y < 0)
    point.y += sideSize;

  if (point.y >= sideSize)
    point.y %= sideSize;

  if (value)
    alive.insert(Point2D::hash(point));
}
// todo: improve those set / get accessors
bool World::Get(Point2D point) {
  // if (point.x < 0) point.x += sideSize;
  // if (point.x >= sideSize) point.x %= sideSize;
  // if (point.y < 0) point.y += sideSize;
  // if (point.y >= sideSize) point.y %= sideSize;
  // auto index = point.y * sideSize + point.x;
  // auto sideSquared = sideSize * sideSize;
  // if (index >= sideSquared) index %= sideSquared;
  // return buffer[currentBufferId % 2][index];

  return alive.contains(Point2D::hash(point));
}

std::unordered_set<size_t> World::getAliveCells()
{
  return alive;
}
void World::Randomize()
{
  //for (auto&& elem : buffer[0]) elem = (Random::Range(0, 1) != 0);

  //for (int i = 0; i < buffer[0].size(); i++) buffer[1][i] = buffer[0][i];

  alive.clear();
  nextState.clear();
  // for (auto&& cell : alive)
  //   {
  //     Point2D point = point.unhash(cell);
  //     auto randomX = Random::Range(0, sideSize);
  //     auto randomY = Random::Range(0, sideSize);
  //
  //     point.x = randomX;
  //     point.y = randomY;
  //
  //     alive.insert(point.hash(point));
  //   }

    for (auto i = 0; i < sideSize; i++) {
        for (auto j = 0; j < sideSize; j++) {
            if (Random::Range(0, 1) != 0) {
                alive.insert(Point2D::hash(Point2D(j, i)));
            }
        }
    }

  nextState = alive;
}
