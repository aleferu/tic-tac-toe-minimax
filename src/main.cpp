#include "raylib.h"
#include "GameState.hpp"
#include <iostream>


void drawBoard(const float);


int main(void) {
    const float screenSize = 800.0f;
    InitWindow((int) screenSize, (int) screenSize, "tic-tac-toe with minimax");
    SetTargetFPS(60);
    GameState gameState;

    // Main loop
    while (!WindowShouldClose()) {
        // Input
        if (!gameState.isGameOver()) {
            if (gameState.isPlayerTurn()) { // I don't know if I'm going to need this separated or merged
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePos = GetMousePosition();
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
            drawBoard(screenSize);
            gameState.drawSymbols(screenSize);

        EndDrawing();

        std::cout << gameState.isGameOver() << std::endl;
    }
    CloseWindow();

    return 0;
}


void drawBoard(const float screenSize) {
    float firstThird = screenSize / 3.0f;
    float secondThird = 2.0f * screenSize / 3.0f;
    float thickness = 5.0f;
    Color color = BLACK;
    DrawLineEx({firstThird, 0}, {firstThird, (float) screenSize}, thickness, color);
    DrawLineEx({secondThird, 0}, {secondThird, (float) screenSize}, thickness, color);
    DrawLineEx({0, firstThird}, {(float) screenSize, firstThird}, thickness, color);
    DrawLineEx({0, secondThird}, {(float) screenSize, secondThird}, thickness, color);
}
