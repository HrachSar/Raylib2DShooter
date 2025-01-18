//
// Created by hrach on 12/24/24.
//

#ifndef GAME_H
#define GAME_H

#include "enemy.h"
#include "player.h"
#include "../resources/aStarPathFinder.h"

#include "../resources/perlin.h"

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define FRAME_SPEED 8
#define LAVA_DAMAGE 0.15f


class Game {
public:
    Game();
    Game(unsigned int width, unsigned int height);
    // ~Game();
    void Init();
    void Render();
    void Update(float deltaTime);
    void ProcessInput(float deltaTime);
    void ProcessCamera();
    void CheckBounds();
    void CheckCollisions(float deltaTime);
    void UpdateEnemyPosition(float deltaTime);
    float Lerp(float a, float b, float t);
    void RenderTiles(unsigned int startX, unsigned int endX, unsigned int startY, unsigned int endY);
    unsigned int m_width, m_height;
    Camera2D m_playerCamera;
private:
    Texture2D m_playerTexture;
    Texture2D m_tiles[4];
    Texture2D m_obstacles[3];
    Texture2D m_walls;
    Player* m_player;
    Enemy* m_enemy;
    SpriteRenderer* mplayer_renderer;
    SpriteRenderer* menemy_renderer;
    SpriteRenderer* mtile_renderer;
    Grid* m_grid;
    Graph m_graph;
    PerlinNoise m_noice;
    AStarPathFinder m_pathFinder;
    float m_xFrame, m_yFrame;
};




#endif //GAME_H
