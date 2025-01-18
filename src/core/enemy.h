//
// Created by hrach on 1/16/25.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "game_object.h"

#define DEFAULT_ENEMY_SPEED 200

class Enemy : public GameObject {
public:
    Enemy();
    ~Enemy();
    Enemy(Vector2 pos, Vector2 size, Texture2D sprite,float speed = DEFAULT_ENEMY_SPEED, float rotation = 0.0f, Vector2 velocity = {0.0f, 0.0f}, Vector2 direction = {0.0f, 0.0f}, Color color = RAYWHITE);
};



#endif //ENEMY_H
