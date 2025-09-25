#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
    // todo: implement this

    if (stack.empty()) {
        auto start = randomStartPoint(w);
        stack.push(std::make_pair(start.x, start.y));
        w->SetNodeColor(Point2D(start.x, start.y), Color32(0, 0, 0));
        visited.insert(std::make_pair(start.x, start.y));
        return true;
    }

    auto current = stack.top();

    auto neighbors = getVisitables(w, Point2D(current.first, current.second));
    auto neighborsCount = neighbors.size();

    if (neighborsCount == 1) {
        auto next = neighbors[0];
        removeWall(w, current, std::make_pair(next.x, next.y));
        w->SetNodeColor(next, Color32(0, 0, 0));
        stack.push(std::make_pair(next.x, next.y));
        visited.insert(std::make_pair(next.x, next.y));
    }

    else if (neighborsCount > 1) {
        auto next = neighbors[rand() % neighborsCount];
        removeWall(w, current, std::make_pair(next.x, next.y));
        w->SetNodeColor(next, Color32(0, 0, 0));
        stack.push(std::make_pair(next.x, next.y));
        visited.insert(std::make_pair(next.x, next.y));
    }

    else {
        stack.pop();
    }
    return !stack.empty();
}

void RecursiveBacktrackerExample::Clear(World* world) {
    visited.clear();
    while (!stack.empty()) {
        stack.pop();
    }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
    auto sideOver2 = world->GetSize() / 2;

    // todo: change this if you want
    for (int y = -sideOver2; y <= sideOver2; y++)
        for (int x = -sideOver2; x <= sideOver2; x++)
            if (!visited.contains(std::make_pair(x, y))) return {x, y};
    return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
    auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> visitables;
    std::vector<std::pair<int, int>> neighbors = {{p.x, p.y - 1}, {p.x + 1, p.y}, {p.x, p.y + 1}, {p.x - 1, p.y}};

    for (auto neighbor : neighbors) {
        auto xi = neighbor.first;
        auto yi = neighbor.second;
        if (xi < -sideOver2 || xi > sideOver2 || yi < -sideOver2 || yi > sideOver2) {
            continue;
        }

        if (!visited.contains(std::make_pair(xi, yi))) {
            visitables.push_back({xi, yi});
        }
    }
    return visitables;
}

void RecursiveBacktrackerExample::removeWall(World* w, std::pair<int, int> current, std::pair<int, int> next) {
    auto deltaX = next.first - current.first;
    auto deltaY = next.second - current.second;
    auto delta = std::make_pair(deltaX, deltaY);

    if (delta == std::make_pair(-1, 0))  // moving left
    {
        w->SetWest(Point2D(current.first, current.second), false);
    }

    else if (delta == std::make_pair(1, 0))  // moving right
    {
        w->SetEast(Point2D(current.first, current.second), false);
    }

    else if (delta == std::make_pair(0, 1)) {
        w->SetSouth(Point2D(current.first, current.second), false);
    }

    else if (delta == std::make_pair(0, -1)) {
        w->SetNorth(Point2D(current.first, current.second), false);
    }
}
