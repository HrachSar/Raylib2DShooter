//
// Created by hrach on 12/24/24.
//

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "raylib.h"

class SpriteRenderer {
public:
    SpriteRenderer();
    void DrawSprite(Texture2D& texture, Vector2 position, Vector2 size, int widthX, int widthY, float rotation, float frameX, float frameY, Color color);
    int flipped;
};



#endif //SPRITE_RENDERER_H
