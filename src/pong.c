#include <stdio.h>

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2);

// --- ЗОНА 2: Управление и Физика ---
// Смена bx, by и проверка столкновений. Возможно необходимо изменить набор параметров
void Update(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2);

int main() {
    // Инициализация и бесконечный цикл: draw -> update
    // Проверка score и выбор победителя
    return 0;
}