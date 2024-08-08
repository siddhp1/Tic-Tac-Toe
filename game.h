#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>

// Board dimensions
#define ROWS 3
#define COLS 3
#define EMPTY_SPACE ' '

typedef char Board[ROWS][COLS];
typedef struct {
    bool is_starting;
    char icon;
} Player;
typedef struct {
    char row;
    char col; 
} Coord;
typedef enum {
    HUMAN_WIN,
    AGENT_WIN,
    DRAW,
    UNDETERMINED,
} GameState;

// Function declarations
bool check_for_win (Board board, Player player);
bool check_for_draw (Board board);
void edit_board (Board board, Player player, Coord coord);
void print_board (Board board);

#endif