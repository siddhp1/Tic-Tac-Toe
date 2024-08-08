#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "game.h"
#include "human.h"
#include "agent.h"

GameState game_loop (Player human, Player agent);
GameState perform_human_turn (Board board, Player human); 
GameState perform_agent_turn (Board board, Player human, Player agent);

int main (void) 
{
    GameState result; 

    Player human = {.is_starting = true, .icon = 'X'}, agent = {.is_starting = false, .icon = 'O'};
    
    int total_games = 1, player_wins = 0, agent_wins = 0, draws = 0;
        
    char keep_playing = 'Y'; 

    // Start a game loop in a "match loop"
    while (toupper(keep_playing) == 'Y') {
        // Print match score
        printf("CURRENT SCORE: HUMAN => %d - %d - %d <= AGENT\n", 
                player_wins, draws, agent_wins);

        printf("Game #%d!\n", total_games); // New game statement

        result = game_loop(human, agent);

        // Print the winner and score
        switch (result) {
            case DRAW:
                printf("DRAW\n");
                draws++;
                break;
            case HUMAN_WIN:
                printf("HUMAN WINS\n");
                player_wins++;
                break;
            case AGENT_WIN:
                printf("AGENT WINS\n");
                agent_wins++;
                break;
        }

        // Prompt to keep playing
        printf("Keep playing? (Y/N): ");
        
        scanf(" %c", &keep_playing);
        // Change the starting side (modify the players)

        human.is_starting = !human.is_starting;
        agent.is_starting = !agent.is_starting;

        char temp;
        temp = human.icon;
        human.icon = agent.icon;
        agent.icon = temp;

        total_games++;

        printf("\n");
    }

    // Print final score after match ends
    printf("FINAL SCORE: HUMAN => %d - %d - %d <= AGENT\n", 
                player_wins, draws, agent_wins);

    return 0;
}

// Returns the player that wins the game
GameState game_loop (Player human, Player agent)
{
    // Create a board for the game and populate with spaces
    Board board;
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++) {
            board[row][col] = ' ';
        }
    }

    GameState state = UNDETERMINED; 

    // Print empty board first
    print_board(board);
    
    while(state == UNDETERMINED) {
        if (human.is_starting) {
            state = perform_human_turn(board, human);
            if (state != UNDETERMINED) {
                return state;
            }
            state = perform_agent_turn(board, human, agent);
            if (state != UNDETERMINED) {
                return state;
            }
        }
        else {
            state = perform_agent_turn(board, human, agent);
            if (state != UNDETERMINED) {
                return state;
            }
            state = perform_human_turn(board, human);
            if (state != UNDETERMINED) {
                return state;
            }
        }
    }

    return state;
}

GameState perform_human_turn (Board board, Player human) 
{
    get_human_input(board, human);
    print_board(board);

    if (check_for_win(board, human)) {
        printf("HUMAN!!@");
        return HUMAN_WIN;
    }
    else if (check_for_draw(board)) {
        return DRAW;
    }
    return UNDETERMINED;
}

GameState perform_agent_turn (Board board, Player human, Player agent) 
{
    get_agent_move(board, human, agent);
    print_board(board);

    if (check_for_win(board, agent)) {
        printf("AGENT!!@");
        return AGENT_WIN;
    }
    else if (check_for_draw(board)) {
        return DRAW;
    }
    return UNDETERMINED;
}