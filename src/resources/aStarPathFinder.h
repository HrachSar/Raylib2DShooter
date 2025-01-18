//
// Created by hrach on 1/16/25.
//

#ifndef ASTARPATHFINDER_H
#define ASTARPATHFINDER_H

#include <map>
#include "../resources/stack.h"
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "../core/grid.h"

class AStarPathFinder {
public:
    std::map<int, int> m_cameFrom;
    std::map<int, int> m_dist;
    Stack m_path;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> m_queue; //min-heap
    /*
     * first argument - each element is a pair of 2 int-s
     * second argument - type of elements to be stored
     * greater - min-heap, less - max-heap
     */
    AStarPathFinder();
    AStarPathFinder(Graph& graph, int from, int to);
    int Heuristic(Graph& graph, int u, int v);
    void Search(Graph& g, int from, int to);
    void ShowPath(Graph& g, int from, int to);
};



#endif //ASTARPATHFINDER_H
