#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Board dimensions
#define ROWS 3
#define COLS 3

// Game states
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define DRAW 2
#define NO_RESULT_YET 3 // Is this needed?

// Icons
#define STARTING_PLAYER_ICON 'X'
#define SECOND_PLAYER_ICON 'O'

// Using char since coordinates can be stored in one byte
typedef char Coordinate;
typedef char Board[ROWS][COLS];
typedef bool Player;
typedef char GameState;

// Function declarations
GameState game_loop (Player starting_player);
void get_player_input (Board board, Player player, Player starting_player);
GameState check_for_win (Board board, Player turn);
void print_board (Board board);

int main (void) 
{
    GameState result; 
    Player starting_player = PLAYER_ONE;
    int total_games = 1, player_one_wins = 0, player_two_wins = 0, draws = 0;
    char keep_playing = 'Y'; 

    // Start a game loop in a "match loop"
    while (toupper(keep_playing) == 'Y') {
        // Print match score
        printf("CURRENT SCORE: PLAYER ONE => %d - %d - %d <= PLAYER TWO\n", 
                player_one_wins, draws, player_two_wins);

        printf("Game #%d!\n", total_games); // New game statement

        result = game_loop(starting_player);

        // Print the winner and score
        switch (result) {
            case DRAW:
                printf("DRAW\n");
                draws++;
                break;
            case PLAYER_ONE:
                printf("PLAYER ONE WINS\n");
                player_one_wins++;
                break;
            case PLAYER_TWO:
                printf("PLAYER TWO WINS\n");
                player_two_wins++;
                break;
        }

        // Prompt to keep playing
        printf("Keep playing? (Y/N): ");
        

        scanf(" %c", &keep_playing);
        // Change the starting player
        starting_player = !starting_player;
        total_games++;


        printf("\n");
    }

    // Print final score after match ends
    printf("FINAL SCORE: PLAYER ONE => %d - %d - %d <= PLAYER TWO\n", 
                player_one_wins, draws, player_two_wins);
    printf("THANKS FOR PLAYING!\n");

    return 0;
}

// Returns the player that wins the game
GameState game_loop (Player starting_player)
{
    // Create a board for the game and populate with spaces
    Board board;
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++) {
            board[row][col] = ' ';
        }
    }
    Player turn = starting_player;
    GameState state = NO_RESULT_YET;

    // Print empty board first
    print_board(board);
    
    while(state == NO_RESULT_YET) {
        get_player_input(board, turn, starting_player);

        // Print board after every turn
        print_board(board);
    
        state = check_for_win(board, turn);
        if (state != NO_RESULT_YET) {
            return state;
        }

        // Switch player
        turn = !turn;
    }

    return state;
}

// Will return a board that has the player input applied
void get_player_input (Board board, Player player, Player starting_player)
{
    Coordinate x_coord, y_coord;

    printf("Player %d (%c), it is your turn.\n", player + 1, player == starting_player ? STARTING_PLAYER_ICON : SECOND_PLAYER_ICON);
    printf("Enter coordinates (col, row from 1-3): ");
    
    // PERFORM VALIDATION HERE (add after I read the book)
    // Check that input is in the correct format, and that the board isnt already occupied in that spot
    scanf("%hhd,%hhd", &y_coord, &x_coord);

    // Modify the board
    if (player == starting_player) {
        board[x_coord - 1][y_coord - 1] = STARTING_PLAYER_ICON;
    }
    else {
        board[x_coord - 1][y_coord - 1] = SECOND_PLAYER_ICON;
    }
}

GameState check_for_win (Board board, Player turn)
{
    for (int row = 0; row < ROWS; row++){
        if (board[row][0] == board[row][1] && board [row][1] == board[row][2] && board[row][0] != ' ') {
            return turn;
        }
    }
    for (int col = 0; col < COLS; col++){
        if (board[0][col] == board[1][col] && board [1][col] == board[2][col] && board[0][col] != ' ') {
            return turn;
        }
    }
    if (board[0][0] == board[1][1] && board [1][1] == board[2][2] && board[1][1] != ' ') {
        return turn;
    }
    if (board[0][2] == board[1][1] && board [1][1] == board[2][0] && board[1][1] != ' ') {
        return turn;
    }
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++) {
            if (board[row][col] == ' ') {
                return NO_RESULT_YET;
            }
        }
    }
    return DRAW;
}

void print_board (Board board)
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