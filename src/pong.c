#include <stdio.h>

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2);

// --- ЗОНА 2: Обработка ввода ---
int Input();
int DetectWhitchPlayer(int input);
int GetDirectionByInput(int input);

// --- ЗОНА 3: Обработка ориентации движения ---
int GetBallDirectionX(int x, int ball_x, int ball_y, int player1_pos, int player2_pos, int paddle_size, int screen_width);
int GetBallDirectionY(int y, int ball_y, int screen_height);

// -- ЗОНА 4: Проверка гола и победы --
int CheckWin(int score1, int score2);
int CheckGoal(int ball_x, int ball_y);

int main() {
    int ball_x = 0;
    int ball_y = 0;
    int ball_x_direction = -1;
    int ball_y_direction = 1;
    int player1_pos = 0;
    int player2_pos = 0;
    int score1, score2 = 0;
    int winner;

    while ((winner = CheckWin(score1, score2)) == -1) {
        Draw(ball_x, ball_y, player1_pos, player2_pos, score1, score2);

        int input = Input();

        int which_player = DetectWhitchPlayer(input);
        int player_direction = GetDirectionByInput(input);
        if (which_player == 1) {
            player1_pos += player_direction;
        } else if (which_player == 2) {
            player2_pos += player_direction;
        }

        ball_x_direction =
            GetBallDirectionX(ball_x_direction, ball_x, ball_y, player1_pos, player2_pos, 3, 85);
        ball_y_direction = GetBallDirectionY(ball_y_direction, ball_y, 85);

        ball_x += ball_x_direction;
        ball_y += ball_y_direction;

        int goal_result = CheckGoal(ball_x, ball_y);
        score1 += goal_result / 10;
        score2 += goal_result % 10;
    }

    // DrawWinner();

    return 0;
}