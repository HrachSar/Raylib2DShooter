//
// Created by hrach on 12/25/24.
//

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <map>
#include <set>
#include <raylib.h>
#include "../resources/sprite_renderer.h"

enum Tiles {
    VENT, //0
    ZIGZAG, //1
    LAVA, //2
    GROUND //3
};
struct Node {
    int m_x, m_y;
    int m_label;
    bool m_blocking;
    int m_cost;
    Tiles m_tile;

    Node() : m_x(0), m_y(0){}
    Node(int x, int y) : m_x(x), m_y(y){}
    Node(int x, int y, int label) : m_x(x), m_y(y), m_label(label){}
    Node(int x, int y, int label, bool blocking, int cost)
        : m_x(x), m_y(y), m_label(label), m_blocking(blocking), m_cost(cost){}
};
struct Edge {
    int m_from, m_to;
    Edge(int from, int to) : m_from(from), m_to(to) {}
    Edge() : m_from(0), m_to(0) {}
};

class Grid{
public:
    Grid(Texture2D sprite);
    ~Grid();
    void Draw(SpriteRenderer& renderer, Vector2 position, float rotation, int widthX, int widthY, int frameX, int frameY);
    Vector2 vec2m_position;
    Vector2 vec2m_size;
    Texture2D m_tile;
    int m_width;
    int m_height;
    std::vector<std::vector<Node>> m_grid;
};
class Graph {
public:
    Graph();
    void InitGraph(Grid& grid);
    void AddEdge(int f, int t);
    void ShowGraph();
    std::map<int, std::set<int>> m_adjList;
    std::map<int, Node> m_vertices;
};



#endif //GRID_H
