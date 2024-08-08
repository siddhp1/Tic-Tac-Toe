#include "human.h"

// Will return a board that has the player input applied
void get_human_input (Board board, Player human)
{
    Coord coord = {-1, -1}; 
    bool valid_coord = false;

    printf("Human (%c), it is your turn.\n", human.icon);
    do {
        // Get coordinates from user
        printf("Enter coordinates (col, row from 0-2): ");
        scanf("%hhd,%hhd", &coord.col, &coord.row);

        // Check that coordinates are within bounds
        if (coord.row < 0 || coord.row > 2 || coord.col < 0 || coord.col > 2) {
            printf("Coordinates out of bounds. Please enter values from 0 to 2.\n");
            continue;
        }

        // Check that coordinates are not occupied
        if (board[coord.row][coord.col] != EMPTY_SPACE) {
            printf("The space is already occupied. Choose another one.\n");
            continue;
        }

        valid_coord = true;
    } while (!valid_coord);
    
    // Edit the board
    edit_board(board, human, coord);
}