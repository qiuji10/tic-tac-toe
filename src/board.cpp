#include <iostream>
#include <board.h>
#include <util.h>

void Board::moveSelect(bool up, bool down, bool left, bool right) {
    if (up && currentSelectCell >= 3) {
        currentSelectCell -= 3;
    }
    else if (down && currentSelectCell < 6) {
        currentSelectCell += 3;
    }
    else if (left && currentSelectCell % 3 != 0) {
        currentSelectCell -= 1;
    }
    else if (right && currentSelectCell % 3 != 2) {
        currentSelectCell += 1;
    }
    // Ensure currentSelectCell is within bounds
    if (currentSelectCell < 0) {
        currentSelectCell = 0;
    } else if (currentSelectCell > 8) {
        currentSelectCell = 8;
    }
}

bool Board::setCell(int index, int value) {
    
    if (board[index] == 1 || board[index] == 2)
        return false;

    if (index >=0 && index < 9) {
        board[index] = value;
        return true;
    }

    return false;
}

bool Board::isWinner(int player, int& winMethod) const {
    
    for (int i = 0; i < 8; i++) {
        const int* line = winConditions[i];
        if (board[line[0]] == player && board[line[1]] == player && board[line[2]] == player) {
            winMethod = i;
            return true;
        }
    }

    return false;
}

void Board::drawBoard() const {
    
    std::cout << getCellSymbol(board[0], 0) + " | " + getCellSymbol(board[1], 1) + " | " + getCellSymbol(board[2], 2) + "\n" +
            "---- ----- ----\n" +
            getCellSymbol(board[3], 3) + " | " + getCellSymbol(board[4], 4) + " | " + getCellSymbol(board[5], 5) + "\n" + 
            "---- ----- ----\n" +
            getCellSymbol(board[6], 6) + " | " + getCellSymbol(board[7], 7) + " | " + getCellSymbol(board[8], 8) << std::endl;
}

void Board::drawBoardWinner(int winMethod) const {
    
    const int* winPatternRow1 = winConditions[winMethod];


    std::cout << getCellSymbol(board[0], 0, winPatternRow1[0]) + " | " + getCellSymbol(board[1], 1, winPatternRow1[0]) + " | " + getCellSymbol(board[2], 2, winPatternRow1[0]) + "\n" +
            "---- ----- ----\n" +
            getCellSymbol(board[3], 3, winPatternRow1[1]) + " | " + getCellSymbol(board[4], 4, winPatternRow1[1]) + " | " + getCellSymbol(board[5], 5, winPatternRow1[1]) + "\n" + 
            "---- ----- ----\n" +
            getCellSymbol(board[6], 6, winPatternRow1[2]) + " | " + getCellSymbol(board[7], 7, winPatternRow1[2]) + " | " + getCellSymbol(board[8], 8, winPatternRow1[2]) << std::endl;
}


std::string Board::getCellSymbol(int player, int cell, int winCell) const {

    bool isSelected = currentSelectCell == cell;
    bool isWinCell = cell == winCell;

    std::string symbol;

    isWinCell ? symbol += COLOR_GREEN : symbol += COLOR_WHITE;
    isSelected || isWinCell ? symbol += "[" : symbol += " ";
    player == 1 ? symbol += COLOR_RED : player == 2 ? symbol += COLOR_BLUE : symbol += COLOR_WHITE;
    symbol += (player == 1 ? "X" : player == 2 ? "O" : " ");
    isWinCell ? symbol += COLOR_GREEN : symbol += COLOR_WHITE;
    isSelected || isWinCell  ? symbol += "]" : symbol += " ";
    symbol += COLOR_WHITE;

    return symbol;
}