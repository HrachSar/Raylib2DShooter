//
// Created by hrach on 12/24/24.
//

#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer() : flipped(1){}
void SpriteRenderer::DrawSprite(Texture2D& texture, Vector2 position, Vector2 size, int widthX, int widthY, float rotation, float frameX, float frameY, Color color) {
    float frameWidth = (float)(texture.width / widthX);
    float frameHeight = (float)(texture.height / widthY);
    Rectangle sourceRect = {frameX * frameWidth, frameY * frameHeight, flipped * frameWidth, frameHeight};
    Rectangle destRect = {position.x, position.y, frameWidth * size.x, frameHeight * size.y};
    Vector2 origin = {frameWidth, frameHeight};

    DrawTexturePro(texture, sourceRect, destRect, origin, rotation, color);
}
