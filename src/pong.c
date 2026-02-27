#include <stdio.h>

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2) {
    const int screen_width = 80;
    const int screen_height = 25;
    const int paddle_size = 3;
    const int score_y_pos = 7;

    printf("\e[H");  // Clear space

    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            if (x == ball_x && y == ball_y) {  // Ball
                printf("*");
            } else if (x == 0 && y >= player1_pos && y < player1_pos + paddle_size) {
                printf("|");  // Left paddle
            } else if (x == screen_width - 1 && y >= player2_pos && y < player2_pos + paddle_size) {
                printf("|");  // Right paddle
            } else if (x == screen_width / 2) {
                printf("|");  // Separator
            } else if (x == screen_width / 2 - 3 && y == score_y_pos) {
                int offset = printf("%d", score1); // Score plr1
                x += offset - 1;
            } else if (x == screen_width / 2 + 3 && y == score_y_pos) {
                int offset = printf("%d", score2); // Score plr2
                x += offset - 1;
            } else
                printf(" ");
        }
        printf("\n");
    }
}

// --- ЗОНА 2: Управление и Физика ---
// Смена bx, by и проверка столкновений. Возможно необходимо изменить набор параметров
void Update(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2);

int main() {
    // Инициализация и бесконечный цикл: draw -> update
    // Проверка score и выбор победителя
    return 0;
}