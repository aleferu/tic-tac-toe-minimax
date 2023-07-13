#include "GameState.hpp"
#include <algorithm>
#include <ctime>
#include "raylib.h"

GameState::GameState() : m_playerTurn(time(nullptr) % 2), m_gameOver(false) {
    std::fill(m_board, m_board + 9, ' ');
}

void GameState::resetState() {
    m_playerTurn = time(nullptr) % 2;
    std::fill(m_board, m_board + 9, ' ');
}

void GameState::nextTurn() {
    m_playerTurn = !m_playerTurn;
}

bool GameState::isPlayerTurn() {
    return m_playerTurn;
}

void GameState::drawSymbols(const int screenSize) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            switch (m_board[3 * row + col]) {
                case 'x':
                    drawX(screenSize, row, col);
                    break;
                case 'o':
                    drawO(screenSize, row, col);
                    break;
                default:
                    break;
            }
        }
    }
}

void GameState::setX(const int row, const int col) {
    if (m_board[3 * row + col] == ' ') {
        m_board[3 * row + col] = 'x';
        nextTurn();
    }
}

bool GameState::isGameOver() { return m_gameOver; }

void GameState::checkWinner(const char symbol) {
    // diags (\ and /)
    m_gameOver = (m_board[0] == symbol && m_board[4] == symbol && m_board[8] == symbol)
              || (m_board[2] == symbol && m_board[4] == symbol && m_board[6] == symbol);
    // rows and cols
    for (int i = 0; i < 3; ++i)
        m_gameOver = m_gameOver || (m_board[3*i] == symbol && m_board[3*(i+1)] == symbol && m_board[3*(i+2)] == symbol) // cols
                                || (m_board[3*i] == symbol && m_board[3*i+1] == symbol && m_board[3*i+2] == symbol); // rows
}

void GameState::drawX(const float screenSize, const int row, const int col) {
    float thirdSize = screenSize / 3.0f;
    float offset = thirdSize / 6.0f;
    float thickness = 50.0f;
    Color color = RED;
    DrawLineEx({thirdSize * col + offset, thirdSize * row + offset}, {thirdSize * (col+1) - offset, thirdSize * (row+1) - offset}, thickness, color);
    DrawLineEx({thirdSize * (col+1) - offset, thirdSize * row + offset}, {thirdSize * col + offset, thirdSize * (row+1) - offset}, thickness, color);
}

void GameState::drawO(const float screenSize, const int row, const int col) {
    float thirdSize = screenSize / 3.0f;
    float thirdHalf = thirdSize / 2.0f;
    float outerRadius = 5.0f * thirdHalf / 6.0f;
    float innerRadius = 3.0f * thirdHalf / 6.0f;
    Color color = BLUE;
    DrawRing({thirdSize * col + thirdHalf, thirdSize * row + thirdHalf}, innerRadius, outerRadius, 0.0f, 360.0f, 0, color);
}
