//
// Created by hrach on 1/16/25.
//

#include "enemy.h"

Enemy::Enemy() : GameObject(){}
Enemy::Enemy(Vector2 pos, Vector2 size, Texture2D sprite, float speed, float rotation, Vector2 velocity, Vector2 direction, Color color)
    : GameObject(pos, size, sprite, speed, rotation, velocity, direction, color){}
Enemy::~Enemy() {
    UnloadTexture(m_sprite);
}


