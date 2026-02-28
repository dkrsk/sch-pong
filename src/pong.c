#include <stdio.h>
#define SCR_WD 80
#define SCR_HG 25
#define PDL_SIZE 3

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2) {
    const int score_y_pos = 7;

    printf("\e[H");  // Clear space

    for (int y = 0; y < SCR_HG; y++) {
        for (int x = 0; x < SCR_WD; x++) {
            if (x == ball_x && y == ball_y) {  // Ball
                printf("*");
            } else if (x == 0 && y >= player1_pos && y < player1_pos + PDL_SIZE) {
                printf("|");  // Left paddle
            } else if (x == SCR_WD - 1 && y >= player2_pos && y < player2_pos + PDL_SIZE) {
                printf("|");  // Right paddle
            } else if (x == SCR_WD / 2) {
                printf("|");  // Separator
            } else if (x == SCR_WD / 2 - 3 && y == score_y_pos) {
                int offset = printf("%d", score1);  // Score plr1
                x += offset - 1;
            } else if (x == SCR_WD / 2 + 3 && y == score_y_pos) {
                int offset = printf("%d", score2);  // Score plr2
                x += offset - 1;
            } else
                printf(" ");
        }
        printf("\n");
    }
}

void DrawWin(int winner) {
    printf("\e[H");
    if (winner == 0) {
        printf(
            "  _____ ___   __          _______ _   _ _ \n |  __ \\__ \\  \\ \\        / /_   _| \\ | | |\n | "
            "|__) | ) |  \\ \\  /\\  / /  | | |  \\| | |\n |  ___/ / /    \\ \\/  \\/ /   | | | . ` | |\n | "
            "|    / /_     \\  /\\  /   _| |_| |\\  |_|\n |_|   |____|     \\/  \\/   |_____|_| \\_(_)\n     "
            "                                     \n                                          ");
    } else {
        printf(
            "  _____  __  __          _______ _   _ _ \n |  __ \\/_ | \\ \\        / /_   _| \\ | | |\n | "
            "|__) || |  \\ \\  /\\  / /  | | |  \\| | |\n |  ___/ | |   \\ \\/  \\/ /   | | | . ` | |\n | |  "
            "   | |    \\  /\\  /   _| |_| |\\  |_|\n |_|     |_|     \\/  \\/   |_____|_| \\_(_)\n          "
            "                               \n                                         ");
    }
}

// --- ЗОНА 2: Обработка ввода ---
int Input();
int DetectWhitchPlayer(int input);
int GetDirectionByInput(int input);

// --- ЗОНА 3: Обработка ориентации движения ---
int DirectionX(int x, int ball_x, int ball_y, int player1_pos, int player2_pos, int paddle_size, int screen_width);
int DirectionY(int y, int ball_y, int screen_height);

// -- ЗОНА 4: Проверка гола и победы --
int CheckWin(int score1, int score2);
int CheckGoal(int ball_x, int ball_y);

int main() {
    // Инициализация и бесконечный цикл: draw -> update
    // Проверка score и выбор победителя
    return 0;
}