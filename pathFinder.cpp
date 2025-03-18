#include "pathFinder.h"
#include <algorithm>
#include <cstdio>
#include <list>

PathFinder::PathFinder(Grid &grid) : grid(grid) { }

std::vector<PathNode> PathFinder::FindPath(int startX, int startY, int endX, int endY)
{
    // Creating grid of nodes ( we can also store them )
    std::vector<PathNode> nodes(Grid::GetHeight() * Grid::GetWidth());

    // Initialize nodes
    for (int y = 0; y < Grid::GetHeight(); ++y)
    {
        for (int x = 0; x < Grid::GetWidth(); ++x)
        {
            // Converting 2D coordinates to 1D index
            int index = y * Grid::GetWidth() + x;
            nodes[index].x = x;
            nodes[index].y = y;

            if (grid.GetCell(x, y).valueId == 10)
            {
                nodes[index].isObstacle = true;
            }

            /* Neighbour Setup:
             * - Take PathNode at position[index] in our 'nodes' vector
             * -- Access its neighbours vector => which stores pointers to adjacent nodes;
             * --- Add a new pointer to the end of this neighbours vector:
             * ---- (A) -> (B) * (C)
             * ----            * (E)
             *
             */

            // if not at edge (y: 0 in grid)
            if (y > 0)
            {
                /* Syntax:
                 * - (y-1) * Grid::GetWidth() + x => calculate the index of the node above
                 * - &nodes[...] gets the memory address of that node
                 *
                 * - nodes[index].neighbors.push_back(...) :
                 * -- adds that memory address to the current node's neighbors vector
                 * -- new value = 4. vector (1,2,3). push_back (4) => (1,2,3,4)
                 *
                 */
                nodes[index].neighbors.push_back(&nodes[(y - 1) * Grid::GetWidth() + x]);
            }
            if (y < Grid::GetHeight() - 1)
            {
                nodes[index].neighbors.push_back(&nodes[(y + 1) * Grid::GetWidth() + x]);
            }
            if (x > 0)
            {
                nodes[index].neighbors.push_back(&nodes[y * Grid::GetWidth() + (x - 1)]);
            }
            if (x < Grid::GetWidth() - 1)
            {
                nodes[index].neighbors.push_back(&nodes[y * Grid::GetWidth() + (x + 1)]);
            }
        }
    }

    PathNode* startNode = &nodes[startY * Grid::GetWidth() + startX];
    PathNode* endNode = &nodes[endY * Grid::GetWidth() + endX];

    // Initialize
    startNode -> localGoal = 0.0f;
    startNode -> globalGoal = CalculateHeuristic(startNode, endNode);

    std::list<PathNode*> openList; // nodes that need to be calculated
    openList.push_back(startNode);

    // Main A*
    while (!openList.empty())
    {
        /* Sort List ( find node with lowest global value ) ( LAMBDA )
         * C#: openList.Sort((a, b) => a.GlobalGoal.CompareTo(b.GlobalGoal));
         */
        openList.sort([] (const PathNode* a, const PathNode* b)
        {
            return a->globalGoal < b->globalGoal;
        });

        // Front node ( current best )
        PathNode* currentNode; // .front() first element

        // removed visited from front
        while (!openList.empty() && openList.front()->isVisited)
        {
            openList.pop_front(); // pop - remove
        }

        // all nodes used, no path found
        if (openList.empty())
        {
            printf("FRONT LIST EXHAUSTED: NO PATH FOUND");
            break;
        }

        currentNode = openList.front();
        currentNode->isVisited = true;

        if (currentNode == endNode)
        {
            break;
        }

        // Check each neighbour
        for (auto nodeNeighbor : currentNode->neighbors)
        {
            // analyze new
            if (!nodeNeighbor->isVisited && !nodeNeighbor->isObstacle)
            {
                openList.push_back(nodeNeighbor);
            }

            // Calculate new potential path length
            float possibleLowerGoal = currentNode->localGoal +
                CalculateDistance(currentNode, nodeNeighbor);

            // If new path is shorter
            if (possibleLowerGoal < nodeNeighbor->localGoal)
            {
                // update parent to later define total path
                nodeNeighbor->parent = currentNode;
                nodeNeighbor->localGoal = possibleLowerGoal;
                nodeNeighbor->globalGoal = nodeNeighbor->localGoal +
                    CalculateHeuristic(nodeNeighbor, endNode);
            }
        }
    }

    // Reconstruct final path ( store the path objects )
    std::vector<PathNode> path;

    if (endNode->parent != nullptr)
    {
        PathNode* currentNode = endNode; // point current to end node

        while (currentNode != startNode)
        {
            path.push_back(*currentNode); // de-reference to get object ( this node )
            currentNode = currentNode->parent;
        }

        path.push_back(*startNode);
        std::reverse(path.begin(), path.end()); // start to end path
    }

    return path;
}

/* Euclidean distance: (pythagoras)
 * distance = √((x₂ - x₁)² + (y₂ - y₁)²)
 * : straight line distance
 */
float PathFinder::CalculateDistance(const PathNode *a, const PathNode *b)
{
    return sqrtf(static_cast<float>((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)));
}

/* Manhattan distance: ( heuristic )
 * h(n) = |x₂ - x₁| + |y₂ - y₁|
 * : sum of absolute differences
 */
float PathFinder::CalculateHeuristic(const PathNode *a, const PathNode *b)
{
    return static_cast<float>(abs(a->x - b->x) + abs(a->y - b->y));
}