//
// Created by hrach on 1/16/25.
//

#include "aStarPathFinder.h"

AStarPathFinder::AStarPathFinder(){}
AStarPathFinder::AStarPathFinder(Graph &graph, int from, int to) {
    Search(graph, from, to);
}
int AStarPathFinder::Heuristic(Graph &graph, int u, int v) {
    int delta = 1;
    Node a = graph.m_vertices[u];
    Node b = graph.m_vertices[v];
    int distx = abs(b.m_x - a.m_x);
    int disty = abs(b.m_y - a.m_y);
    distx *= distx;
    disty *= disty;
    int dist = std::sqrt(distx+disty);
    return delta * dist;
}

void AStarPathFinder::Search(Graph &g, int from, int to) {
    int examined = 0;
    bool found = false;
    m_dist[from] = 0;
    m_cameFrom[from] = -1;
    m_queue.push(std::make_pair(0, from));
    while (!m_queue.empty()) {
        int current = m_queue.top().second;
        m_queue.pop();
        if (current == to) {
            found = true;
            break;
        }
        for (auto adj : g.m_adjList[current]) {
            examined++;
            if (!g.m_vertices[current].m_blocking) {
                int new_cost = m_dist[current] + g.m_vertices[adj].m_cost;
                if (m_dist.find(adj) == m_dist.end() || new_cost < m_dist[adj]) {
                    m_dist[adj] = new_cost;
                    m_cameFrom[adj] = current;
                    int priority = new_cost + Heuristic(g, adj, to);
                    m_queue.push(std::make_pair(priority, adj));
                }
            }
        }
    }
    if (found)
        ShowPath(g, from, to);
}
void AStarPathFinder::ShowPath(Graph &g, int from, int to) {
  //  std::vector<int> path;
    int crawl = to;
    while (crawl != from) {
        m_path.Push(crawl);
        crawl = m_cameFrom[crawl];
    }
    m_path.Push(from);

    // while (!m_path.Empty()) {
    //     std::cout << m_path.Top() << " -> ";
    //     m_path.Pop();
    // }
    // std::cout << '\n';
}

