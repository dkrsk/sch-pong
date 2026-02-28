#include <stdio.h>

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2);

// --- ЗОНА 2: Обработка ввода ---
int Input();
int DetectWhitchPlayer(int input);
int GetDirectionByInput(int input);

// --- ЗОНА 3: Обработка ориентации движения ---
int DirectionX(int x, int ball_x, int ball_y, int player1_pos, int player2_pos, int paddle_size, int screen_width);
int DirectionY(int y, int ball_y, int screen_height);

// -- ЗОНА 4: Проверка гола и победы --
int CheckWin(int score1, int score2) {
    int win_score = 21;
    int winner = -1;
    if (score1 >= win_score) winner = 1;
    else if (score2 >= win_score) winner = 2;
    return winner;
}

int CheckGoal(int ball_x, int ball_y) {
    int score1 = 0;
    int score2 = 0;
    if (ball_x <= 0) score2++;
    if (ball_x >= screen_width - 1) score1++;
    
    return score2 * 10 + score1;


}

int main() {
    // Инициализация и бесконечный цикл: draw -> update
    // Проверка score и выбор победителя
    return 0;
}