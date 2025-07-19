#pragma once
#include <array>
#include <string>

class Board {

public:
    void moveSelect(bool up, bool down, bool left, bool right);
    void setCell(int index, int value);
    std::string displayBoard() const;
    bool isWinner(int player) const;
    int getCurrentSelectCell() const { return currentSelectCell; }
private:
    int currentSelectCell = 0;
    std::array<int, 9> board = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::string getCellSymbol(int player, int cell) const;
};