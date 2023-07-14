#include "GameState.hpp"
#include <algorithm>
#include <ctime>
#include "raylib.h"


GameState::GameState() : m_playerTurn(time(nullptr) % 2), m_gameOver(false) {
    std::fill(m_board, m_board + 9, ' ');
}


void GameState::resetState() {
    m_playerTurn = time(nullptr) % 2;
    m_gameOver = false;
    std::fill(m_board, m_board + 9, ' ');
}


void GameState::nextTurn() {
    m_playerTurn = !m_playerTurn;
}


bool GameState::isPlayerTurn() {
    return m_playerTurn;
}


void GameState::drawSymbols(const int screenSize, const float hOffset, const float vOffset) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            switch (m_board[3 * row + col]) {
                case 'x':
                    drawX(screenSize, hOffset, vOffset, row, col);
                    break;
                case 'o':
                    drawO(screenSize, hOffset, vOffset, row, col);
                    break;
                default:
                    break;
            }
        }
    }
}


void GameState::setX(const int row, const int col) {
    int index = 3 * row + col;
    if (m_board[index] == ' ') {
        m_board[index] = 'x';
        nextTurn();
    }
}


void GameState::setO() {
    char board_copy[9];
    for (int i = 0; i < 9; ++i)
        board_copy[i] = m_board[i];
    int best_score = -10;
    int best_move = -1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int index = 3 * i + j;
            if (board_copy[index] == ' ') {
                board_copy[index] = 'o';
                int score = GameState::minimax(board_copy, false);
                board_copy[index] = ' ';
                if (score > best_score) {
                    best_score = score;
                    best_move = index;
                }
            }
        }
    }
    m_board[best_move] = 'o';
    nextTurn();
}


bool GameState::isGameOver() { return m_gameOver; }


void GameState::checkWinner(const char symbol) {
    // diags (\ and /)
    m_gameOver = (m_board[0] == symbol && m_board[4] == symbol && m_board[8] == symbol)
              || (m_board[2] == symbol && m_board[4] == symbol && m_board[6] == symbol)
              || GameState::boardFilled(m_board);
    // rows and cols
    for (int i = 0; i < 3; ++i)
        m_gameOver = m_gameOver || (m_board[i] == symbol && m_board[i+3] == symbol && m_board[i+6] == symbol) // cols
                                || (m_board[3*i] == symbol && m_board[3*i+1] == symbol && m_board[3*i+2] == symbol); // rows
}


void GameState::drawX(const float screenSize, const float hOffset, const float vOffset, const int row, const int col) {
    float thirdSize = screenSize / 3.0f;
    float padding = thirdSize / 6.0f;
    float thickness = 50.0f;
    Color color = RED;
    DrawLineEx({thirdSize * col + padding + hOffset, thirdSize * row + padding + vOffset}, 
               {thirdSize * (col+1) - padding + hOffset, thirdSize * (row+1) - padding + vOffset}, 
               thickness, color);
    DrawLineEx({thirdSize * (col+1) - padding + hOffset, thirdSize * row + padding + vOffset}, 
               {thirdSize * col + padding + hOffset, thirdSize * (row+1) - padding + vOffset}, 
               thickness, color);
}


void GameState::drawO(const float screenSize, const float hOffset, const float vOffset, const int row, const int col) {
    float thirdSize = screenSize / 3.0f;
    float thirdHalf = thirdSize / 2.0f;
    float outerRadius = 5.0f * thirdHalf / 6.0f;
    float innerRadius = 3.0f * thirdHalf / 6.0f;
    Color color = BLUE;
    DrawRing({thirdSize * col + thirdHalf + hOffset, thirdSize * row + thirdHalf + vOffset}, 
             innerRadius, outerRadius, 0.0f, 360.0f, 0, color);
}


int GameState::minimax(char board[9], const bool is_max_turn) {
    int board_score = GameState::evaluateBoard(board);
    if (board_score == 1 || board_score == -1) return board_score;
    if (GameState::boardFilled(board)) {
        return 0;
    } 

    if (is_max_turn) {
        int best_score = -10;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int index = 3 * i + j;
                if (board[index] == ' ') {
                    board[index] = 'o';
                    int score = GameState::minimax(board, false);
                    board[index] = ' ';
                    if (score > best_score) {
                        best_score = score;
                    }
                }
            }
        }
        return best_score;
    } else {
        int worst_score = 10;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int index = 3 * i + j;
                if (board[index] == ' ') {
                    board[index] = 'x';
                    int score = GameState::minimax(board, true);
                    board[index] = ' ';
                    if (score < worst_score) {
                        worst_score = score;
                    }
                }
            }
        }
        return worst_score;
    }
}


int GameState::evaluateBoard(const char board[9]) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i] == 'x' && board[i+3] == 'x' && board[i+6] == 'x') ||
            (board[3*i] == 'x' && board[3*i+1] == 'x' && board[3*i+2] == 'x')) return -1;
        if ((board[i] == 'o' && board[i+3] == 'o' && board[i+6] == 'o') ||
            (board[3*i] == 'o' && board[3*i+1] == 'o' && board[3*i+2] == 'o')) return 1;
    }
    if ((board[0] == 'x' && board[4] == 'x' && board[8] == 'x') ||
        (board[2] == 'x' && board[4] == 'x' && board[6] == 'x')) return -1;
    if ((board[0] == 'o' && board[4] == 'o' && board[8] == 'o') ||
        (board[2] == 'o' && board[4] == 'o' && board[6] == 'o')) return 1;
    return 0;
}


bool GameState::boardFilled(const char board[9]) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}
