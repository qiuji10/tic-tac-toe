#pragma once
#include <iostream>
#include <array>
#include <board.h>
#include <input.h>

// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8

class Game {
public:
    void start();
    void process();
    void quit();
    int getCurrentPlayer() const { return currentPlayer; }
private:
    int currentPlayer = 1; // 1 for player 1, 2 for player 2
    Board board;
    Input input;

    void refreshCellSelection(bool up, bool down, bool left, bool right);
};