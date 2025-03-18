#ifndef PATHNODE_H
#define PATHNODE_H

#include <cmath>
#include <vector>

struct PathNode
{
    int x;
    int y;
    bool isVisited = false;
    bool isObstacle = false;
    float localGoal = INFINITY;
    float globalGoal = INFINITY;

    // Store ( pointers ) Connections to other PathNodes ( Neighbours )
    std::vector<PathNode*> neighbors;
    PathNode* parent = nullptr; // Each node's Parent ( initialize nullptr )
};

#endif //PATHNODE_H
