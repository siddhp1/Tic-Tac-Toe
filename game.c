#include "game.h"

bool check_for_win (const Board board, const Player *player)
{
    // Check rows and columns
    for (int i = 0; i < ROWS; i++){
        // Check rows
        if (board[i][0] == player->icon && board[i][1] == player->icon && board[i][2] == player->icon) {
            return true;
        }
        // Check columns
        if (board[0][i] == player->icon && board[1][i] == player->icon && board[2][i] == player->icon) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == player->icon && board[1][1] == player->icon &&  board[2][2] == player->icon) {
        return true;
    }
    if (board[0][2] == player->icon && board[1][1] == player->icon &&  board[2][0] == player->icon) {
        return true;
    }

    return false;
}

bool check_for_draw (const Board board) 
{
    // Check for empty spaces
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++) {
            if (board[row][col] == EMPTY_SPACE) {
                return false;
            }
        }
    }

    return true;
}

void edit_board (Board board, const Player *player, const Coord *coord)
{
    board[coord->row][coord->col] = player->icon;
}

void print_board (const Board board)
{
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c   \n", board[0][0], board[0][1], board[0][2]);
    printf("       |       |       \n");
    printf("-----------------------\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c   \n", board[1][0], board[1][1], board[1][2]);
    printf("       |       |       \n");
    printf("-----------------------\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c   \n", board[2][0], board[2][1], board[2][2]);
    printf("       |       |       \n");
}