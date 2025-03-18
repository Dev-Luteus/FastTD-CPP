#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "grid.h"
#include "pathNode.h"
#include <vector>

class PathFinder
{
private:
    Grid& grid;

    float CalculateDistance(const PathNode* a, const PathNode* b);
    float CalculateHeuristic(const PathNode* a, const PathNode* b);

public:
    explicit PathFinder(Grid& grid);
    std::vector<PathNode> FindPath(int startX, int startY, int endX, int endY);
};

#endif //PATHFINDER_H
