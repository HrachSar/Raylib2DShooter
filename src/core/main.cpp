#include "game.h"
#include "grid.h"
#include "raylib.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720


Color darkRed = {149, 6, 6, 0};
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
Game game = Game();

void UpdateDrawFrame();// Update and Draw one frame
int main()
{

    InitWindow(game.m_width, game.m_height, "Shooter");
    game.Init();
    SetTargetFPS(60);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}


void UpdateDrawFrame()
{
    float currentTime = (float)GetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    game.ProcessCamera();
    BeginDrawing();
    BeginMode2D(game.m_playerCamera);
    game.Update(deltaTime);
    ClearBackground(darkRed);
    EndMode2D();
    EndDrawing();
}