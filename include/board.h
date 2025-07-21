#pragma once
#include <array>
#include <string>

class Board {
public:
    void moveSelect(bool up, bool down, bool left, bool right);
    bool setCell(int index, int value);
    void drawBoard() const;
    void drawBoardWinner(int winMethod) const;
    bool isWinner(int player, int& winMethod) const;
    int getCurrentSelectCell() const { return currentSelectCell; }
private:
    int currentSelectCell = 0;
    std::array<int, 9> board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    const int winConditions[8][3] = {
        {0, 1, 2}, // Row 1
        {3, 4, 5}, // Row 2
        {6, 7, 8}, // Row 3
        {0, 3, 6}, // Column 1
        {1, 4, 7}, // Column 2
        {2, 5, 8}, // Column 3
        {0, 4, 8}, // Diagonal 1
        {2, 4, 6}  // Diagonal 2
    };

    std::string getCellSymbol(int player, int cell, int winCell = -1) const;
};