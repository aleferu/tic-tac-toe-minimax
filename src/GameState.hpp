#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP


class GameState {
public:
    GameState(void);
    void resetState(void);
    void nextTurn(void);
    bool isPlayerTurn(void);
    void drawSymbols(const int screenSize, const float hOffset, const float vOffset);
    void setX(const int row, const int col);
    void setO(void);
    bool isGameOver(void);
    void checkWinner(const char symbol);

private:
    bool m_playerTurn;
    bool m_gameOver;
    char m_board[9];
    void drawX(const float screenSize, const float hOffset, const float vOffset, const int row, const int col);
    void drawO(const float screenSize, const float hOffset, const float vOffset, const int row, const int col);
    static int minimax(char board[9], const bool is_max_turn);
    static int evaluateBoard(const char board[9]);
    static bool boardFilled(const char board[9]);
};


#endif // GAMESTATE_HPP
