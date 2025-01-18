#include "player.h"

float Projectile::m_projSpeed = PROJECTILE_SPEED;
float Projectile::m_Radius = PROJECTILE_RADIUS;

Player::Player() : GameObject() {
    m_health = MAX_HEALTH;
    isHit = false;
    isShooting = false;
    isInsideZigzag = false;
    isAlive = true;
    m_dir = DOWN;
}
Player::Player(Vector2 pos, Vector2 size, Texture2D sprite,float speed, float rotation, Vector2 velocity, Vector2 direction, Color color)
    : GameObject(pos, size, sprite, speed, rotation, velocity, direction, color) {
    m_health = MAX_HEALTH;
    isHit = false;
    isShooting = false;
    isInsideZigzag = false;
    isAlive = true;
    m_dir = DOWN;
}
Player::~Player() {
    UnloadTexture(m_sprite);
}
void Player::Shoot() {
    Projectile* new_projectile = new Projectile();
    new_projectile->vec2m_position.x = this->vec2m_position.x + this->vec2m_size.x / 2;
    new_projectile->vec2m_position.y = this->vec2m_position.y + this->vec2m_size.y / 2;
    switch (m_dir) {
        case UP:
            new_projectile->vec2m_direction.y = -(this->vec2m_position.y + this->vec2m_size.y / 2) * new_projectile->m_projSpeed;
        break;
        case DOWN:
            new_projectile->vec2m_direction.y = (this->vec2m_position.y + this->vec2m_size.y / 2) * new_projectile->m_projSpeed;
        break;
        case LEFT:
            new_projectile->vec2m_direction.x = -(this->vec2m_position.x + this->vec2m_size.x / 2) * new_projectile->m_projSpeed;
        break;
        case RIGHT:
            new_projectile->vec2m_direction.x = (this->vec2m_position.x + this->vec2m_size.x / 2) * new_projectile->m_projSpeed;
        break;
    }
    m_projectiles.push_back(new_projectile);
}
void Player::UpdateProjectileLifeTime(Projectile* projectile, float deltaTime) {
    if (projectile->isSolid) {
        projectile->m_lifetime -= deltaTime;
    }
    if (projectile->m_lifetime <= 0.0f) {
        projectile->isSolid = false;
    }
}
void Player::UpdateProjectiles(float deltaTime) {
    for (auto proj = m_projectiles.begin(); proj != m_projectiles.end();) {
        (*proj)->vec2m_position.x += (*proj)->vec2m_direction.x * deltaTime;
        (*proj)->vec2m_position.y += (*proj)->vec2m_direction.y * deltaTime;
        UpdateProjectileLifeTime((*proj), deltaTime);
        if (!(*proj)->isSolid) {
            delete (*proj);
            m_projectiles.erase(proj);
        }else {
            ++proj;
        }
    }
}
