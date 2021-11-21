#include <stdio.h>

int LOST = -100;
int WON  =  100;

int check (char board[3][3]) {
    for (int i = 0; i < 3; i ++) {
        if (board[i][0] == 'x' && board[i][1] == 'x' && board[i][2] == 'x') {
            return WON;
        }

        if (board[0][i] == 'x' && board[1][i] == 'x' && board[2][i] == 'x') {
            return WON;
        }


        if (board[i][0] == 'o' && board[i][1] == 'o' && board[i][2] == 'o') {
            return LOST;
        }

        if (board[0][i] == 'o' && board[1][i] == 'o' && board[2][i] == 'o') {
            return LOST;
        }
    }

    if (board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x') {
        return WON;
    }

    if (board[0][2] == 'x' && board[1][1] == 'x' && board[2][0] == 'x') {
        return WON;
    }

    if (board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o') {
        return LOST;
    }

    if (board[0][2] == 'o' && board[1][1] == 'o' && board[2][0] == 'o') {
        return LOST;
    }

    return 0;
}

int best (char board[3][3], int mode, int *x, int *y) {
    int result, res_max, res_min, px, py, nx, ny, no_move = 1;
    result = check(board);

    if (mode <= 0 || result == WON || result == LOST) {
        return result;
    }

    if (!(mode % 2)) {
        for (px = 0, res_max = 2*LOST; px < 3; px++) {
            for (py = 0; py < 3; py++) {
                if (board[px][py] == ' ') {
                    board[px][py] = 'x';
                    result = best(board, mode-1, &nx, &ny);
                    board[px][py] = ' ';
                    if (result > res_max) {
                        res_max = result;
                        *x = px;
                        *y = py;
                    }
                    no_move = 0;
                }
            }
        }
        return no_move ? 0 : res_max;

    } else {
        for (px = 0, res_min = 2*WON; px < 3; px++) {
            for (py = 0; py < 3; py++) {
                if (board[px][py] == ' ') {
                    board[px][py] = 'o';
                    result = best(board, mode-1, &nx, &ny);
                    board[px][py] = ' ';
                    if (result < res_min) {
                        res_min = result;
                        *x = px;
                        *y = py;
                    }
                    no_move = 0;
                }
            }
        }
        return no_move ? 0 : res_min;
    }
}

void print(char board[3][3]) {
    printf("-------------\n");

    for (int x = 0; x < 3; x++) {
        printf("|");
        for (int y = 0; y < 3; y++) {
            printf(" %c |", board[x][y]);
        }
        printf("\n");
        printf("-------------\n");
    }
    printf("\n");
}

int main() {
    char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
    };

    int x, y, result, move_id = 0;

    while (1) {
        best(board, 10, &x, &y);
        board[x][y] = 'x';
        print(board);

        result = check(board);

        if (result == WON) {
            printf("Przegrales!\n");
            return 0;
        }

        if (result == LOST) {
            printf("Wygrales!\n");
            return 0;
        }

        if (move_id == 4) {
            printf("Remis!\n");
            return 0;
        }

        printf("Podaj ruch ([x] [y]):");
        scanf("%d %d", &x, &y);
        board[x][y] = 'o';
        print(board);

        result = check(board);

        if (result == WON) {
            printf("Przegrales!\n");
            return 0;
        }

        if (result == LOST) {
            printf("Wygrales!\n");
            return 0;
        }

        move_id++;
    }
}
