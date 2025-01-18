//
// Created by hrach on 12/24/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "game_object.h"

#define MAX_HEALTH 100
#define PROJECTILE_SPEED 1
#define PROJECTILE_LIFETIME 2
#define PROJECTILE_RADIUS 3

enum Direction {
    UP, //0
    DOWN, //1
    LEFT, //2
    RIGHT //3
};

struct Projectile : GameObject {
    Projectile() : GameObject() {
        m_lifetime = PROJECTILE_LIFETIME;
        isSolid = true;
    }
    float m_lifetime;
    static float m_projSpeed;
    static float m_Radius;
    bool isSolid;
};

class Player : public GameObject {
public:
    Player();
    ~Player();
    Player(Vector2 pos, Vector2 size, Texture2D sprite,float speed = DEFAULT_SPEED, float rotation = 0.0f, Vector2 velocity = {0.0f, 0.0f}, Vector2 direction = {0.0f, 0.0f}, Color color = RAYWHITE);
    void Shoot();
    void UpdateProjectiles(float deltaTime);
    void UpdateProjectileLifeTime(Projectile* projectile, float deltaTime);
    std::vector<Projectile*> m_projectiles;
    Direction m_dir;
    float m_health;
    bool isHit;
    bool isAlive;
    bool isShooting;
    bool isInsideZigzag;
};

#endif //PLAYER_H
