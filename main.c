#include <stdio.h>

#define ROWS 6
#define COLS 7

// Function to initialize the game board
void initialize_board(char board[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            board[r][c] = ' ';
        }
    }
}

// Function to print the game board
void print_board(char board[ROWS][COLS]) {
    printf("\n");
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            printf("| %c ", board[r][c]);
        }
        printf("|\n");
        for (int c = 0; c < COLS; c++) {
            printf("----");
        }
        printf("\n");
    }
}

// Function to check if a column is full
int is_column_full(char board[ROWS][COLS], int col) {
    return board[0][col] != ' ';
}

// Function to make a move for a player
int make_move(char board[ROWS][COLS], int col, char player) {
    if (col < 0 || col >= COLS || is_column_full(board, col)) {
        printf("Invalid move! Column is full or out of bounds.\n");
        return 0;
    }

    for (int r = ROWS - 1; r >= 0; r--) {
        if (board[r][col] == ' ') {
            board[r][col] = player;
            return 1;
        }
    }
    return 0;
}

// Function to check if a player has won
int check_win(char board[ROWS][COLS], char player) {
    // Check horizontal
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS - 3; c++) {
            if (board[r][c] == player && board[r][c + 1] == player &&
                board[r][c + 2] == player && board[r][c + 3] == player) {
                return 1;
            }
        }
    }

    // Check vertical
    for (int r = 0; r < ROWS - 3; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] == player && board[r + 1][c] == player &&
                board[r + 2][c] == player && board[r + 3][c] == player) {
                return 1;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int r = 3; r < ROWS; r++) {
        for (int c = 0; c < COLS - 3; c++) {
            if (board[r][c] == player && board[r - 1][c + 1] == player &&
                board[r - 2][c + 2] == player && board[r - 3][c + 3] == player) {
                return 1;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int r = 0; r < ROWS - 3; r++) {
        for (int c = 0; c < COLS - 3; c++) {
            if (board[r][c] == player && board[r + 1][c + 1] == player &&
                board[r + 2][c + 2] == player && board[r + 3][c + 3] == player) {
                return 1;
            }
        }
    }

    return 0;
}

// Function to check if the board is full (for a draw)
int is_board_full(char board[ROWS][COLS]) {
    for (int c = 0; c < COLS; c++) {
        if (board[0][c] == ' ') {
            return 0;
        }
    }
    return 1;
}

// Main game loop
int main() {
    char board[ROWS][COLS];
    int column;
    char player = 'X';
    int game_over = 0;

    initialize_board(board);

    while (!game_over) {
        print_board(board);
        printf("Player %c's turn. Enter column (1-7): ", player);
        scanf("%d", &column);
        column--;  // Adjust for 0-indexed array

        if (make_move(board, column, player)) {
            if (check_win(board, player)) {
                print_board(board);
                printf("Player %c wins!\n", player);
                game_over = 1;
            } else if (is_board_full(board)) {
                print_board(board);
                printf("It's a draw!\n");
                game_over = 1;
            } else {
                player = (player == 'X') ? 'O' : 'X';  // Switch player
            }
        }
    }

    return 0;
}
