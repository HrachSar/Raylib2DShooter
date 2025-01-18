#include "game_object.h"

GameObject::GameObject() : vec2m_position({0.0f, 0.0f}), vec2m_size({1.0f, 1.0f}), m_sprite(),
                            vec2m_velocity({0.0f, 0.0f}), vec2m_direction({0.0f, 0.0f}), m_rotation(0.0f), m_color(RAYWHITE){}
GameObject::GameObject(Vector2 pos, Vector2 size, Texture2D sprite,float speed, float rotation, Vector2 velocity, Vector2 direction, Color color) :
            vec2m_position(pos), vec2m_size(size), m_sprite(sprite),m_speed(speed), m_rotation(rotation), vec2m_velocity(velocity), vec2m_direction(direction), m_color(color){}
GameObject::~GameObject() {
    UnloadTexture(m_sprite);
}
void GameObject::Draw(SpriteRenderer &renderer,int widthX, int widthY, float frameX, float frameY, Color color) {
    renderer.DrawSprite(m_sprite, vec2m_position, vec2m_size, widthX, widthY, m_rotation, frameX, frameY, color);
}
