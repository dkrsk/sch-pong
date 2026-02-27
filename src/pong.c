#include <stdio.h>

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2);

// --- ЗОНА 2: Обработка ввода ---
int Input();
int DetectWhitchPlayer(int input);
int GetDirectionByInput(int input);

int DirectionX(int x, int ball_x, int ball_y, int player1_pos, int player2_pos, int paddle_size, int screen_width) {
    bool drpl1 = (ball_x == 1 && ball_y >= player1_pos && ball_y < player1_pos + paddle_size);
    bool drpl2 = (ball_x == screen_width - 2 && ball_y >= player2_pos && ball_y < player2_pos + paddle_size);
    
    if (drpl1 || drpl2) {
        x = -x;
    }
    return x;
}

int DirectionY(int y, int ball_y, int screen_height) {
    if (ball_y == 0 || ball_y == screen_height - 1) {
        y = -y;
    }
    return y;
}

/*  ЭТО В main
    if (ball_x <= 0) {
        score2++;
        ball_x = screen_width/2 -1;
        ball_y = screen_height/2;
    }
    if (ball_x >= screen_width - 1) {
        score1++;
        ball_x = screen_width/2 +1;
        ball_y = screen_height/2;
    }
*/

int main() {
    // Инициализация и бесконечный цикл: draw -> update
    // Проверка score и выбор победителя
    return 0;
}

