#include <limits.h>
#include "agent.h"

#define MAX_DEPTH 9

// Forward declarations
int max (const int n, const int m);
int min (const int n, const int m);
int minimax (Board board, Player human, Player agent, bool is_maximizing, int depth, int max_depth, int alpha, int beta);

void get_agent_move (Board board, Player human, Player agent) {
    Coord coord = {-1, -1}; // Default coordinates
    int best_eval = INT_MIN; // Default evaluation is -infinity
    
    // Find best move
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col] == ' ') {
                // Determine evaluation with every possible move
                board[row][col] = agent.icon;
                int eval = minimax(board, human, agent, false, 0, MAX_DEPTH, INT_MIN, INT_MAX);
                board[row][col] = ' ';

                // Set the best possible move
                if (eval > best_eval) {
                    best_eval = eval;
                    coord.row = row;
                    coord.col = col;
                }
            }
        }
    }

    // Check if a valid move was found
    if (coord.row != -1 && coord.col != -1) {
        // Modify the board
        printf("Agent's (%c), turn.\n", agent.icon);
        edit_board(board, agent, coord);
    }
}

int minimax (Board board, Player human, Player agent, bool is_maximizing, int depth, int max_depth, int alpha, int beta)
{
    // Base case
    if (check_for_win(board, human)) return -1;
    else if (check_for_win(board, agent)) return 1;
    else if (check_for_draw(board) || depth == max_depth) return 0;

    if (is_maximizing) {
        int max_eval = INT_MIN;
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                if (board[row][col] == ' ') {
                    // Determine evaluation with every possible move
                    board[row][col] = agent.icon;
                    int eval = minimax(board, human, agent, false, depth + 1, max_depth, alpha, beta);
                    board[row][col] = ' ';

                    max_eval = max(eval, max_eval);
                    alpha = max(alpha, eval);

                    // Pruning
                    if (beta <= alpha) {
                        return max_eval; 
                    }
                }
            }
        }
        return max_eval;
    }
    else {
        int min_eval = INT_MAX;
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                if (board[row][col] == ' ') {
                    // Determine evaluation with every possible move
                    board[row][col] = human.icon;
                    int eval = minimax(board, human, agent, true, depth + 1, max_depth, alpha, beta);
                    board[row][col] = ' ';

                    min_eval = min(eval, min_eval);
                    beta = min(beta, eval);

                    // Pruning
                    if (beta <= alpha) {
                        return min_eval;
                    }
                }
            }
        }
        return min_eval;
    }
}

// Function to return the maximum of two integers
int max (const int n, const int m) {
    return n > m ? n : m; 
}

// Function to return the minimum of two integers
int min (const int n, const int m) {
    return n < m ? n : m; 
}