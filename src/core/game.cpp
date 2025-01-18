//
// Created by hrach on 12/24/24.
//

#include "game.h"
#include <iostream>

float frameCounter = 0.0f;
float timer = 0.0f;
float colorTimer = 0.0f;
float shootingTimer = 0.0f;
float zigzagTimer = 0.0f;
float timeToSearch = 0.0f;
float timeToMove = 10.0f;
float moveProgress = 0.0f;
Game::Game() : Game(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}
Game::Game(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;
}
float Game::Lerp(float a, float b, float t) {
    return a + t * (b - a);
}
void Game::Init() {
    m_tiles[0] = LoadTexture("../src/gfx/tiles/tile_3.png");
    m_tiles[1] = LoadTexture("../src/gfx/tiles/tile_4.png");
    m_tiles[2] = LoadTexture("../src/gfx/tiles/tile_5.png");
    m_tiles[3] = LoadTexture("../src/gfx/tiles/tile_6.png");
    m_walls = LoadTexture("../src/gfx/wall.png");
    m_obstacles[0] = LoadTexture("../src/gfx/tiles/tile_1.png");
    m_obstacles[1] = LoadTexture("../src/gfx/tiles/tile_2.png");
    m_obstacles[2] = LoadTexture("../src/gfx/tiles/tile_7.png");
    m_playerTexture = LoadTexture("../src/gfx/player.png");
    mplayer_renderer = new SpriteRenderer();
    menemy_renderer = new SpriteRenderer();
    mtile_renderer = new SpriteRenderer();
    m_player = new Player({(float)START_POS_X, (float)START_POS_Y},
                {(float)DEFAULT_SIZE, (float)(DEFAULT_SIZE)}, m_playerTexture);
    m_enemy = new Enemy({(float)START_POS_X, 300.0f}, {(float)DEFAULT_SIZE, (float)DEFAULT_SIZE}, m_playerTexture);
    m_playerCamera = {0};
    m_playerCamera.target = m_player->vec2m_position;
    m_playerCamera.offset = (Vector2){(float)m_width / 2, (float)m_height / 2};
    m_playerCamera.rotation = 0.0f;
    m_playerCamera.zoom = 1.0f;
    m_noice = PerlinNoise(3);
    m_grid = new Grid(m_tiles[3]);
    int label = 0;
    for (int i = 0; i < m_grid->m_height; i++) {
        for (int j = 0; j < m_grid->m_width; j++) {
            float ny = i * NOICE_SCALE;
            float nx = j * NOICE_SCALE;

             float noiceValue = m_noice.noise(nx, ny);
             m_grid->m_grid[i][j] = Node(j, i, label++);
             if (noiceValue < 0.13f)
                 m_grid->m_grid[i][j].m_tile = VENT;
             else if (noiceValue < 0.16f)
                 m_grid->m_grid[i][j].m_tile = ZIGZAG;
             else if (noiceValue < 0.19f)
                 m_grid->m_grid[i][j].m_tile = LAVA;
             else
                 m_grid->m_grid[i][j].m_tile = GROUND;
            if (m_grid->m_grid[i][j].m_tile != GROUND && m_grid->m_grid[i][j].m_tile != VENT) {
                m_grid->m_grid[i][j].m_blocking = true;
            }else {
                m_grid->m_grid[i][j].m_blocking = false;
            }
            m_grid->m_grid[i][j].m_cost = ((rand() % 100) > 65) ? 20 : 10;
        }
    }

    m_graph.InitGraph(*m_grid);
    m_graph.ShowGraph();
    m_xFrame = 0.0f;
    m_yFrame = 0.0f;

}
void Game::Render() {
    RenderTiles(16, 2 * (m_width + 8), 16, 2 * (m_height + 8));
    m_player->Draw(*mplayer_renderer,3, 9, m_xFrame, m_yFrame, m_player->m_color);
    m_enemy->Draw(*menemy_renderer, 3, 9, 1, 3, m_enemy->m_color);
    for (auto proj : m_player->m_projectiles) {
        DrawCircle(proj->vec2m_position.x, proj->vec2m_position.y, Projectile::m_Radius, RED);
    }
}
void Game::Update(float deltaTime) {
    frameCounter += deltaTime;
    m_player->UpdateProjectiles(deltaTime);
    UpdateEnemyPosition(deltaTime);
    Render();
    ProcessInput(deltaTime);
    CheckBounds();
    CheckCollisions(deltaTime);
}
void Game::UpdateEnemyPosition(float deltaTime) {
    int x = m_player->vec2m_position.x / 16;
    int y = m_player->vec2m_position.y / 16;

    int enemy_x = m_enemy->vec2m_position.x / 16;
    int enemy_y = m_enemy->vec2m_position.y / 16;
    timeToSearch += deltaTime;

    if (timeToSearch >= 5.0f) {
        m_pathFinder.Search(m_graph, m_grid->m_grid[enemy_y][enemy_x].m_label, m_grid->m_grid[y][x].m_label);
    //    std::cout << m_grid->m_grid[y][x].m_label << '\n';
    //    std::cout << m_grid->m_grid[enemy_y][enemy_x].m_label << '\n';
        timeToSearch = 0.0f;
    }
    while (!m_pathFinder.m_path.Empty()) {
        int p = m_pathFinder.m_path.Top();
        m_pathFinder.m_path.Pop();
        float nx = m_graph.m_vertices[p].m_x * 16.0f;
        float ny = m_graph.m_vertices[p].m_y * 16.0f;

        // m_enemy->vec2m_position.x = nx;
        // m_enemy->vec2m_position.y = ny;

        // Gradually move towards the target
        //moveProgress += deltaTime / 4.0f;

        // Interpolate position
        m_enemy->vec2m_position.x  = nx;
        m_enemy->vec2m_position.y  = ny;
        // m_enemy->vec2m_position.x = Lerp(m_enemy->vec2m_position.x, nx, moveProgress);
        // m_enemy->vec2m_position.y = Lerp(m_enemy->vec2m_position.y, ny, moveProgress);

        std::cout << m_enemy->vec2m_position.x << " " << m_enemy->vec2m_position.y << '\n';
    }
}

void Game::ProcessInput(float deltaTime) {
        if (IsKeyDown(KEY_UP)) {
            m_player->m_dir = UP;
            frameCounter++;
            if(frameCounter >= (float)60 / FRAME_SPEED) {
                frameCounter = 0.0f;
                m_xFrame++;
                if (m_xFrame >= 3.0f)
                m_xFrame = 1.0f;
            }
            m_yFrame = 1.0f;
            m_player->vec2m_position.y -= m_player->m_speed * deltaTime;
            mplayer_renderer->flipped = 1;
        }
        if (IsKeyDown(KEY_DOWN)) {
            m_player->m_dir = DOWN;
            frameCounter++;
            if(frameCounter >= (float)60 / FRAME_SPEED) {
                frameCounter = 0.0f;
                m_xFrame++;
                if (m_xFrame >= 3.0f)
                    m_xFrame = 1.0f;
            }
            m_yFrame = 0.0f;
            m_player->vec2m_position.y += m_player->m_speed * deltaTime;
            mplayer_renderer->flipped = 1;
        }
        if (IsKeyDown(KEY_LEFT)) {
            m_player->m_dir = LEFT;
            frameCounter++;
            if(frameCounter >= (float)60 / FRAME_SPEED) {
                frameCounter = 0.0f;
                m_xFrame++;
                if (m_xFrame >= 3.0f)
                    m_xFrame = 1.0f;
            }
            m_yFrame = 2.0f;
            m_player->vec2m_position.x -= m_player->m_speed * deltaTime;
            mplayer_renderer->flipped = -1;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            m_player->m_dir = RIGHT;
            frameCounter++;
            if(frameCounter >= (float)60 / FRAME_SPEED) {
                frameCounter = 0.0f;
                m_xFrame++;
                if (m_xFrame >= 3.0f)
                    m_xFrame = 1.0f;
            }
            m_yFrame = 2.0f;
            m_player->vec2m_position.x += m_player->m_speed * deltaTime;
            mplayer_renderer->flipped = 1;
        }
        if (IsKeyDown(KEY_SPACE) && !m_player->isShooting) {
            m_player->Shoot();
            m_player->isShooting = true;
        }
        if (m_player->isShooting) {
            shootingTimer += deltaTime;
            if (shootingTimer >= 0.8f) {
                m_player->isShooting = false;
                shootingTimer = 0.0f;
            }
        }
        if (m_xFrame != 1.0f) {
            timer += deltaTime;
            if (timer >= 0.3f) {
                m_xFrame = 1.0f;
                timer = 0.0f;
            }
        }
}
void Game::ProcessCamera() {
    m_playerCamera.target = m_player->vec2m_position;
    m_playerCamera.offset = (Vector2){(float)m_width / 2, (float)m_height / 2};
}
void Game::RenderTiles(unsigned int startX, unsigned int endX, unsigned int startY, unsigned int endY) {

    for (unsigned int i = startY; i < endY; i += 16) {
        for (unsigned int j = startX; j < endX; j += 16) {
            m_grid->Draw(*mtile_renderer, (Vector2){(float)j, (float)i},0.0f, 1, 1, 0, 0);

            int x = j / 16;
            int y = i / 16;
            if (x >= 0 && x < m_grid->m_width && y >= 0 && y < m_grid->m_height) {
                if(m_grid->m_grid[y][x].m_tile == VENT)
                    m_grid->m_tile = m_tiles[1];
                else if (m_grid->m_grid[y][x].m_tile == ZIGZAG)
                    m_grid->m_tile = m_obstacles[0];
                else if (m_grid->m_grid[y][x].m_tile == LAVA)
                    m_grid->m_tile = m_obstacles[2];
                else
                    m_grid->m_tile = m_tiles[3];
            }
        }
    }

    for (unsigned int i = startY * 3; i < endY; i+= m_grid->vec2m_position.y) {
        mtile_renderer->DrawSprite(m_walls, (Vector2){0.0f, (float)i}, {1.0f, 1.0f}, 1,1,0.0f,0,0, RAYWHITE);
    }
    for (unsigned int i = startY * 3; i < endY; i+= m_grid->vec2m_position.y) {
        mtile_renderer->DrawSprite(m_walls, (Vector2){(float)endX - 16, (float)i}, {1.0f, 1.0f}, 1,1,0.0f,0,0, RAYWHITE);
    }
    for (unsigned int i = 0; i < endX - m_walls.height; i+= m_grid->vec2m_position.x) {
        mtile_renderer->DrawSprite(m_walls, (Vector2){(float)i, 0.0f}, {1.0f, 1.0f}, 1,1,90.0f,0,0, RAYWHITE);
    }
    for (unsigned int i = 0; i < endX - m_walls.height; i+= m_grid->vec2m_position.x) {
        mtile_renderer->DrawSprite(m_walls, (Vector2){(float)i, (float)endY - 16}, {1.0f, 1.0f}, 1,1,90.0f,0,0, RAYWHITE);
    }
}
void Game::CheckBounds(){
    if (m_player->vec2m_position.x <= 16.0f)
        m_player->vec2m_position.x = 16.0f;
    if (m_player->vec2m_position.x >= 2 * m_width - 16.0f)
        m_player->vec2m_position.x = 2 * m_width - 16.0f;
    if (m_player->vec2m_position.y <= 0.0f)
        m_player->vec2m_position.y = 0.0f;
    if (m_player->vec2m_position.y  >= 2 * m_height - 32.0f)
        m_player->vec2m_position.y = 2 * m_height - 32.0f;
}
void Game::CheckCollisions(float deltaTime) {
    int x = (m_player->vec2m_position.x / 16);
    int y = ceil(m_player->vec2m_position.y / 16 + 1);
    static int r = rand() % 4;
    if (x >= 0 && x < m_grid->m_width && y >= 0 && y < m_grid->m_height) {
        if (m_grid->m_grid[y][x].m_tile == LAVA) {
            if (m_player->vec2m_position.x >= m_width) {
                m_player->vec2m_position.x -= 16.0f;
                m_player->isHit = true;
            }
            if (m_player->vec2m_position.x <= m_width) {
                m_player->vec2m_position.x += 16.0f;
                m_player->isHit = true;
            }
            if (m_player->vec2m_position.y <= m_height) {
                m_player->vec2m_position.y += 16.0f;
                m_player->isHit = true;
            }
            if (m_player->vec2m_position.y >= m_height) {
                m_player->vec2m_position.y -= 16.0f;
                m_player->isHit = true;
            }
        }
        else if (m_grid->m_grid[y][x].m_tile == ZIGZAG) {
            m_player->isInsideZigzag = true;
        }
        if (m_player->isInsideZigzag) {
            m_player->m_color = DARKGREEN;
            zigzagTimer += deltaTime;

            switch (r) {
                case 0:
                    m_player->vec2m_size = {2.5f, 2.5f};
                break;
                case 1:
                    m_player->m_speed = 2 * DEFAULT_SPEED;
                break;
                case 2:
                    Projectile::m_projSpeed = 5 * PROJECTILE_SPEED;
                break;
                case 3:
                    Projectile::m_Radius = 2 * PROJECTILE_RADIUS;
                Projectile::m_projSpeed = PROJECTILE_SPEED / 2.0f;
                break;
            }
            if (zigzagTimer >= 15.0f) {
                m_player->m_color = RAYWHITE;
                zigzagTimer = 0.0f;
                r = rand() % 4;
                m_player->isInsideZigzag = false;
                m_player->vec2m_size = {DEFAULT_SIZE, DEFAULT_SIZE};
                m_player->m_speed = DEFAULT_SPEED;
                Projectile::m_projSpeed = PROJECTILE_SPEED;
                Projectile::m_Radius = PROJECTILE_RADIUS;
            }
        }
        if (m_player->isHit) {
            m_player->m_health -= LAVA_DAMAGE;
            colorTimer += deltaTime;
            m_player->m_color = RED;
            if (colorTimer >= 0.15f)
                m_player->m_color = RAYWHITE;
            if (colorTimer >= 0.25f)
                m_player->m_color = RED;
            if (colorTimer >= 0.45f)
                m_player->m_color = RAYWHITE;
            if (colorTimer >= 0.65f)
                m_player->m_color = RED;
            if (colorTimer >= 0.8f) {
                m_player->isHit = false;
                colorTimer = 0.0f;
                m_player->m_color = RAYWHITE;
            }
        }
    }
    if (m_player->m_health <= 0.0f)
        m_player->isAlive = false;
}


