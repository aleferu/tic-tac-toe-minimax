#include "raylib.h"
#include <iostream>


void drawBoard(const float);
void drawX(const float, int, int);
void drawO(const float, int, int);


int main(void) {
    const float screenSize = 800.0f;
    InitWindow((int) screenSize, (int) screenSize, "tic-tac-toe with minimax");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Input
        // nothing yet

        // Draw
        BeginDrawing();

            ClearBackground(DARKGRAY);
            drawBoard(screenSize);
            drawX(screenSize, 2, 1);
            drawO(screenSize, 1, 1);

        EndDrawing();
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


void drawX(const float screenSize, int row, int col) {
    float thirdSize = screenSize / 3.0f;
    float offset = thirdSize / 6.0f;
    float thickness = 50.0f;
    Color color = RED;
    DrawLineEx({thirdSize * col + offset, thirdSize * row + offset}, {thirdSize * (col+1) - offset, thirdSize * (row+1) - offset}, thickness, color);
    DrawLineEx({thirdSize * (col+1) - offset, thirdSize * row + offset}, {thirdSize * col + offset, thirdSize * (row+1) - offset}, thickness, color);
}


void drawO(const float screenSize, int row, int col) {
    float thirdSize = screenSize / 3.0f;
    float thirdHalf = thirdSize / 2.0f;
    float outerRadius = 5.0f * thirdHalf / 6.0f;
    float innerRadius = 3.0f * thirdHalf / 6.0f;
    Color color = BLUE;
    DrawRing({thirdSize * col + thirdHalf, thirdSize * row + thirdHalf}, innerRadius, outerRadius, 0.0f, 360.0f, 0, color);
}
