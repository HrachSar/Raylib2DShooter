//
// Created by hrach on 12/25/24.
//

#include "grid.h"
#include <iostream>

Grid::Grid(Texture2D sprite) {
    m_tile = sprite;
    vec2m_size = {1.0f, 1.0f};
    vec2m_position = (Vector2){(float)m_tile.width, (float)m_tile.height};
    m_width = 2 * GetScreenWidth() / m_tile.width;
    m_height = 2 * GetScreenHeight() / m_tile.height;
    m_grid.resize(m_height, std::vector<Node>(m_width));
}


void Grid::Draw(SpriteRenderer &renderer, Vector2 position, float rotation, int widthX, int widthY, int frameX, int frameY) {
    renderer.DrawSprite(m_tile, position, vec2m_size, widthX, widthY, rotation, frameX, frameY, RAYWHITE);
}
Graph::Graph() {}

void Graph::InitGraph(Grid &grid) {
    unsigned int m = grid.m_width * grid.m_height;
    for (int i = 0; i < m; i++) {
        m_adjList[i] = std::set<int>();
    }
    std::vector<Node> dirs = {Node(-1, 0), Node(1, 0), Node(0, 1), Node(0, -1)};
    for (int i = 0; i < grid.m_height; i++) {
        for (int j = 0; j < grid.m_width; j++) {
            for (auto d : dirs) {
                m_vertices[grid.m_grid[i][j].m_label] = Node(j, i, grid.m_grid[i][j].m_label, grid.m_grid[i][j].m_blocking, grid.m_grid[i][j].m_cost);
                Node gridPos(d.m_x + j, d.m_y + i);
                if (gridPos.m_x >= 0 && gridPos.m_x < grid.m_height && gridPos.m_y >= 0 && gridPos.m_y < grid.m_width) {
                    m_adjList[grid.m_grid[i][j].m_label].insert(grid.m_grid[gridPos.m_x][gridPos.m_y].m_label);
                }
            }
        }
    }
}
void Graph::AddEdge(int f, int t) {
    m_adjList[f].insert(t);
    m_adjList[t].insert(f);
}
void Graph::ShowGraph() {
    for (auto vert : m_adjList) {
        std::cout << vert.first<<": ";
        for (auto n : vert.second){
            std::cout << n << " ";
        }
        std::cout << '\n';
    }
}
