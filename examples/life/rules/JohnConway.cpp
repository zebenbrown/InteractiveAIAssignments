#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
    // todo: implement
    world.deadNeighbors.clear();
    world.nextState = world.alive;
    auto neighborCount = 0;
    for (auto cell : world.alive) {
        neighborCount = CountNeighbors(world, Point2D::unhash(cell));

        for (auto i = -1; i <= 1; i++) {
            for (auto j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) { continue; };

                Point2D cellPosition = Point2D::unhash(cell);

                uint32_t newX = (cellPosition.x + i + world.SideSize()) % world.SideSize();
                uint32_t newY = (cellPosition.y + j + world.SideSize()) % world.SideSize();

                if (!world.alive.contains(Point2D::hash(Point2D(newX, newY)))) {
                    world.deadNeighbors.insert(Point2D::hash(Point2D(newX, newY)));
                }
            }
        }

        if (neighborCount > 3) {
            world.nextState.erase(cell);
        }

        if (neighborCount < 2) {
            world.nextState.erase(cell);
        }
    }

    for (auto deadCell : world.deadNeighbors) {
        neighborCount = CountNeighbors(world, Point2D::unhash(deadCell));

        if (neighborCount == 3) {
            world.nextState.insert(deadCell);
        }
    }
    //world.SwapBuffers();
    //world.deadNeighbors.clear();
    //world.nextState.clear();

}

int JohnConway::CountNeighbors(World& world, Point2D point) {
    // todo: implement
    int count = 0;

    for (auto i = -1; i <= 1; ++i) {
        for (auto j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            // does the wrapping for out of bounds checks
            uint32_t neighborY = ((point.y + i) + world.SideSize()) % world.SideSize();
            uint32_t neighborX = ((point.x + j) + world.SideSize()) % world.SideSize();
            if (world.alive.contains(Point2D::hash(Point2D(neighborX, neighborY))))
            {
                count++;
            }
        }
    }
    return count;

    return 0;
}
