
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#define START_POS_X GetScreenWidth()
#define START_POS_Y GetScreenHeight()
#define DEFAULT_SIZE 2
#define DEFAULT_SPEED 100

#include <raylib.h>
#include  "../resources/sprite_renderer.h"

class GameObject {
public:
    GameObject();
    virtual ~GameObject() = 0;
    GameObject(Vector2 pos, Vector2 size, Texture2D sprite,float speed = DEFAULT_SPEED, float rotation = 0.0f, Vector2 velocity = {0.0f, 0.0f}, Vector2 direction = {0.0f, 0.0f}, Color color = RAYWHITE);
    void Draw(SpriteRenderer& renderer, int widthX, int widthY, float frameX, float frameY, Color color);
    Vector2 vec2m_position;
    Vector2 vec2m_size;
    Vector2 vec2m_velocity;
    Vector2 vec2m_direction;
    Texture2D m_sprite;
    Color m_color;
    float m_rotation;
    float m_speed;
};



#endif //GAME_OBJECT_H
