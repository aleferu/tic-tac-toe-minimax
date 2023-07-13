#include "raylib.h"
#include "GameState.hpp"
#include <iostream>


void drawBoard(const float, const float, const float);


int main(void) {
    float screenWidth = 1600.0f;
    float screenHeight = 900.0f;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow((int) screenWidth, (int) screenHeight, "tic-tac-toe with minimax");
    SetTargetFPS(60);
    GameState gameState;

    // Main loop
    while (!WindowShouldClose()) {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        float screenSize = 0.0f, vOffset = 0.0f, hOffset = 0.0f;
        if (screenWidth < screenHeight) {
            screenSize = screenWidth;
            vOffset = (screenHeight - screenSize) / 2.0f;
        } else {
            screenSize = screenHeight;
            hOffset = (screenWidth - screenSize) / 2.0f;
        }

        // Input
        if (!gameState.isGameOver()) {
            if (gameState.isPlayerTurn()) { // I don't know if I'm going to need this separated or merged
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePos = GetMousePosition();
                    mousePos.x -= hOffset;
                    mousePos.y -= vOffset;
                    float mouseX = screenSize - 1 < mousePos.x ? screenSize - 1 : mousePos.x;
                    float mouseY = screenSize - 1 < mousePos.y ? screenSize - 1 : mousePos.y;
                    gameState.setX(static_cast<int> (mouseY / screenSize * 3.0f), static_cast<int> (mouseX / screenSize * 3.0f));
                    gameState.checkWinner('x');
                }
            } else { 
                //gameState.minimax(true);
                gameState.checkWinner('o');
            }
        } else if (IsKeyPressed(KEY_R)) gameState.resetState();

        // Draw
        BeginDrawing();

            ClearBackground(DARKGRAY);
            drawBoard(screenSize, hOffset, vOffset);
            gameState.drawSymbols(screenSize, hOffset, vOffset);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}


void drawBoard(const float screenSize, const float hOffset, const float vOffset) {
    float firstThird = screenSize / 3.0f;
    float secondThird = 2.0f * screenSize / 3.0f;
    float thickness = 5.0f;
    Color color = BLACK;
    DrawRectangle(hOffset, vOffset, screenSize, screenSize, GRAY);
    DrawLineEx({firstThird + hOffset, vOffset}, {firstThird + hOffset, screenSize + vOffset}, thickness, color);
    DrawLineEx({secondThird + hOffset, vOffset}, {secondThird + hOffset, screenSize + vOffset}, thickness, color);
    DrawLineEx({hOffset, firstThird + vOffset}, {screenSize + hOffset, firstThird + vOffset}, thickness, color);
    DrawLineEx({hOffset, secondThird + vOffset}, {screenSize + hOffset, secondThird + vOffset}, thickness, color);
}
