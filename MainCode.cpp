#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime> // For time

using namespace std;

const int SIZE = 3;

class FifteenPuzzle {
private:
    int board[SIZE][SIZE]; // Game board
    int emptyTileX; // X-coordinate of the empty tile
    int emptyTileY; // Y-coordinate of the empty tile
    int moves; // Number of moves made by the player
    time_t startTime; // Start time of the game
    time_t endTime; // End time of the game

public:
    FifteenPuzzle() {
        emptyTileX = SIZE - 1;
        emptyTileY = SIZE - 1;
        moves = 0;
        startTime = 0;
        endTime = 0;
    }

    // Create the initial game board
    void createBoard() {
        int number = 1;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                board[i][j] = number++;
        board[SIZE - 1][SIZE - 1] = 0; // Set the empty tile
    }

    // Print the current game board
    void printBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0)
                    cout << "   "; // Print empty tile as spaces
                else
                    cout << "+---"; // Print border between tiles
            }
            cout << "+" << endl;

            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0)
                    cout << "   "; // Print empty tile as spaces
                else
                    cout << "| " << board[i][j] << " "; // Print tile value
            }
            cout << "|" << endl;
        }

        for (int j = 0; j < SIZE; j++)
            cout << "+---";
        cout << "+" << endl;
    }

    // Mix the game board
    void shuffleBoard(int moves) {
        srand(time(nullptr));
        for (int i = 0; i < moves; i++) {
            int randomMove = rand() % 4; // Generate a random number from 0 to 3
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

    // Make a move based on the input
    void makeMove(char move) {
        switch (tolower(move)) {
            case 'w': moveUp(); break;
            case 's': moveDown(); break;
            case 'a': moveLeft(); break;
            case 'd': moveRight(); break;
        }
    }

    // Move the empty tile up
    void moveUp() {
        if (emptyTileX > 0) {
            swap(board[emptyTileX][emptyTileY], board[emptyTileX - 1][emptyTileY]);
            emptyTileX--;
            moves++;
            if (isSolved())
                endTime = time(nullptr);
        }
    }

    // Move the empty tile down
    void moveDown() {
        if (emptyTileX < SIZE - 1) {
            swap(board[emptyTileX][emptyTileY], board[emptyTileX + 1][emptyTileY]);
            emptyTileX++;
            moves++;
            if (isSolved())
                endTime = time(nullptr);
        }
    }

    // Move the empty tile left
    void moveLeft() {
        if (emptyTileY > 0) {
            swap(board[emptyTileX][emptyTileY], board[emptyTileX][emptyTileY - 1]);
            emptyTileY--;
            moves++;
            if (isSolved())
                endTime = time(nullptr);
        }
    }

    // Move the empty tile right
    void moveRight() {
        if (emptyTileY < SIZE - 1) {
            swap(board[emptyTileX][emptyTileY], board[emptyTileX][emptyTileY + 1]);
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

    // Game loop
    while (!game.isSolved()) {
        cout << "Moves: " << game.getMoves() << endl;
        cout << "Time elapsed: " << game.getElapsedTime() << " seconds" << endl;
        game.printBoard();

        char move;
        cin >> move;

        game.makeMove(move); //method of the FifteenPuzzle class which is used to make a move in game

        system("cls"); //Clear the console 

        if (game.isSolved())
            break;
    }

    cout << "Congratulations! Puzzle solved." << endl;
    cout << "Total moves: " << game.getMoves() << endl;
    cout << "Total time elapsed: " << game.getElapsedTime() << " seconds" << endl;

    return 0;
}
