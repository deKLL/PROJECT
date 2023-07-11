#include <iostream>
#include <cstdlib>
#include <ctime>

const int SIZE = 3;

class FifteenPuzzle {
private:
    int board[SIZE][SIZE];
    int emptyTileX;
    int emptyTileY;
    int moves;
    time_t startTime;
    time_t endTime;

public:
    FifteenPuzzle() {
        emptyTileX = SIZE - 1;
        emptyTileY = SIZE - 1;
        moves = 0;
        startTime = 0;
        endTime = 0;
    }

    // Create the initial board configuration
    void createBoard() {
        int number = 1;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                board[i][j] = number++;
        board[SIZE - 1][SIZE - 1] = 0;
    }

    // Print the current board configuration
    void printBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0)
                    std::cout << "   ";
                else
                    std::cout << "+---";
            }
            std::cout << "+" << std::endl;

            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0)
                    std::cout << "   ";
                else
                    std::cout << "| " << board[i][j] << " ";
            }
            std::cout << "|" << std::endl;
        }

        for (int j = 0; j < SIZE; j++)
            std::cout << "+---";
        std::cout << "+" << std::endl;
    }

    // Shuffle the board by making a given number of random moves
    void shuffleBoard(int moves) {
        srand(time(nullptr));
        for (int i = 0; i < moves; i++) {
            int randomMove = rand() % 4;
            switch (randomMove) {
                case 0: moveUp(); break;
                case 1: moveDown(); break;
                case 2: moveLeft(); break;
                case 3: moveRight(); break;
            }
        }
        startTime = time(nullptr);
    }

    // Check if the puzzle is solved
    bool isSolved() {
        int number = 1;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board[i][j] != number++)
                    return false;
        return true;
    }

    // Make a move based on the user input
    void makeMove(char move) {
        switch (tolower(move)) {
            case 'w': moveUp(); break;
            case 's': moveDown(); break;
            case 'a': moveLeft(); break;
            case 'd': moveRight(); break;
            default: std::cout << "Invalid move!" << std::endl; break;
        }
    }

    // Move the empty tile up
    void moveUp() {
        if (emptyTileX > 0) {
            std::swap(board[emptyTileX][emptyTileY], board[emptyTileX - 1][emptyTileY]);
            emptyTileX--;
            moves++;
            if (isSolved())
                endTime = time(nullptr);
        }
    }

    // Move the empty tile down
    void moveDown() {
        if (emptyTileX < SIZE - 1) {
            std::swap(board[emptyTileX][emptyTileY], board[emptyTileX + 1][emptyTileY]);
            emptyTileX++;
            moves++;
            if (isSolved())
                endTime = time(nullptr);
        }
    }

    // Move the empty tile left
    void moveLeft() {
        if (emptyTileY > 0) {
            std::swap(board[emptyTileX][emptyTileY], board[emptyTileX][emptyTileY - 1]);
            emptyTileY--;
            moves++;
            if (isSolved())
                endTime = time(nullptr);
        }
    }

    // Move the empty tile right
    void moveRight() {
        if (emptyTileY < SIZE - 1) {
            std::swap(board[emptyTileX][emptyTileY], board[emptyTileX][emptyTileY + 1]);
            emptyTileY++;
            moves++;
            if (isSolved())
                endTime = time(nullptr);
        }
    }

    // Get the number of moves
    int getMoves() {
        return moves;
    }

    // Get the elapsed time in seconds
    double getElapsedTime() {
        if (startTime == 0 || endTime == 0)
            return 0.0;
        return difftime(endTime, startTime);
    }
};

int main() {
    FifteenPuzzle game;
    game.createBoard();
    game.shuffleBoard(100);

    while (!game.isSolved()) {
        std::cout << "Moves: " << game.getMoves() << std::endl;
        std::cout << "Time elapsed: " << game.getElapsedTime() << " seconds" << std::endl;
        game.printBoard();

        char move;
        std::cin >> move;

        game.makeMove(move);

        system("cls");

        if (game.isSolved())
            break;
    }

    std::cout << "Congratulations! Puzzle solved." << std::endl;
    std::cout << "Total moves: " << game.getMoves() << std::endl;
    std::cout << "Total time elapsed: " << game.getElapsedTime() << " seconds" << std::endl;

    return 0;
}
