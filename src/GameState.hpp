#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class GameState {
public:
    GameState();
    void resetState();
    void nextTurn();
    bool isPlayerTurn();
    void drawSymbols(const int screenSize);
    void setX(const int row, const int col);
    bool isGameOver();
    void checkWinner(const char symbol);

private:
    bool m_playerTurn;
    bool m_gameOver;
    char m_board[9];
    void drawX(const float screenSize, const int row, const int col);
    void drawO(const float screenSize, const int row, const int col);
};

#endif // GAMESTATE_HPP
