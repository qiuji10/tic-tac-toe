#include <game.h>
#include <iostream>

void clearLine(int lineNum, int columnNum) {
    // Move cursor to the start of the specified line and column
    std::cout << "\033[" << lineNum << ";" << columnNum << "H";
    // Clear from cursor to end of line
    std::cout << "\033[K";
}

void Game::drawIntro()
{
    clearLine(2, 1);
    std::cout << "Welcome to Tic Tac Toe!" << std::endl;
    std::cout << "W, A, S, D to navigate, Enter to select" << std::endl;
    std::cout << "Player 1 (X) go first\n" << std::endl;
}

void Game::refreshCellSelection(bool up, bool down, bool left, bool right) {

    if (needRestart)
        return;

    if (up || down || left || right)
        board.moveSelect(up, down, left, right);
    
    clearLine(6, 1); // to refresh the board
    board.drawBoard();
}

void Game::start() {
    drawIntro();
    board.drawBoard();

    input.setOnUpPress([this]{refreshCellSelection(true, false, false, false);});
    input.setOnDownPress([this]{refreshCellSelection(false, true, false, false);});
    input.setOnLeftPress([this]{refreshCellSelection(false, false, true, false);});
    input.setOnRightPress([this]{refreshCellSelection(false, false, false, true);});
    input.setOnEnterPress([this]{
        
        if (needRestart)
            return;

        bool canSet = board.setCell(board.getCurrentSelectCell(), currentPlayer);
        
        if (canSet)
        {
            refreshCellSelection(false, false, false, false);
        }
        else
        {
            std::cout << "You need to select cell that is empty!" << std::endl;

            clearLine(11, 1); // to clear any hint/instructions
            return;
        }


        bool isPlayer1Win = board.isWinner(1);
        bool isPlayer2Win = board.isWinner(2);

        if (isPlayer1Win || isPlayer2Win)
        {
            needRestart = true;
        }

        currentPlayer = currentPlayer == 1 ? 2 : 1; // Switch player
    });
}

void Game::process() {

    while (true) {
        input.processInput();
    }
}

void Game::quit() {
    std::cout << "Game over. Thanks for playing!" << std::endl;
    exit(0);
}