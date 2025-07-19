#include <board.h>
#include <iostream>

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

void Board::setCell(int index, int value) {
    if (index >=0 && index < 9) {
        board[index] = value;
    }
}

bool Board::isWinner(int player) const {

    if (board[0] == player && board[1] == player && board[2] == player) return true; // Row 1
    if (board[3] == player && board[4] == player && board[5] == player) return true; // Row 2
    if (board[6] == player && board[7] == player && board[8] == player) return true; // Row 3
    if (board[0] == player && board[3] == player && board[6] == player) return true; // Column 1
    if (board[1] == player && board[4] == player && board[7] == player) return true; // Column 2
    if (board[2] == player && board[5] == player && board[8] == player) return true; // Column 3
    if (board[0] == player && board[4] == player && board[8] == player) return true; // Diagonal 1
    if (board[2] == player && board[4] == player && board[6] == player) return true; // Diagonal 2

    return false;
}

std::string Board::displayBoard() const {
    
    return getCellSymbol(board[0], 0) + " | " + getCellSymbol(board[1], 1) + " | " + getCellSymbol(board[2], 2) + "\n" +
            "---------------\n" +
            getCellSymbol(board[3], 3) + " | " + getCellSymbol(board[4], 4) + " | " + getCellSymbol(board[5], 5) + "\n" + 
            "---------------\n" +
            getCellSymbol(board[6], 6) + " | " + getCellSymbol(board[7], 7) + " | " + getCellSymbol(board[8], 8) + "\n";
}

std::string Board::getCellSymbol(int player, int cell) const {
    return player == 1 ? " X " : player == 2 ? " O " : currentSelectCell == cell ? "[ ]" : "   ";
}