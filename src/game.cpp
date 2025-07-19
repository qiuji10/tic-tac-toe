#include <game.h>

void Game::refreshCellSelection(bool up, bool down, bool left, bool right) {
    board.moveSelect(up, down, left, right);
    std::cout << board.displayBoard() << std::endl;
}

void Game::start() {
    board.displayBoard();

    input.setOnUpPress([this]{refreshCellSelection(true, false, false, false);});
    input.setOnDownPress([this]{refreshCellSelection(false, true, false, false);});
    input.setOnLeftPress([this]{refreshCellSelection(false, false, true, false);});
    input.setOnRightPress([this]{refreshCellSelection(false, false, false, true);});
    input.setOnEnterPress([this]{
        board.setCell(board.getCurrentSelectCell(), currentPlayer);
        board.displayBoard();
        currentPlayer = currentPlayer == 1 ? 2 : 1; // Switch player
    });
}

void Game::process() {

    while (true) {
        input.processInput();
    }
}