#include <ncurses.h>
#define SCR_WD 80
#define SCR_HG 25
#define PDL_SIZE 3
#define WIN_SCR 21
#define BL_SPEED 3

// --- ЗОНА 1: Отрисовка (Интерактивная) ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2) {
    const int score_y_pos = 1;

    erase();

    for (int y = 0; y < SCR_HG; y++) {
        mvaddch(y, SCR_WD / 2, '|');
    }

    for (int i = 0; i < PDL_SIZE; i++) {
        mvaddch(player1_pos + i, 0, '|');
        mvaddch(player2_pos + i, SCR_WD - 1, '|');
    }

    mvprintw(score_y_pos, SCR_WD / 2 - 5, "%d", score1);
    mvprintw(score_y_pos, SCR_WD / 2 + 4, "%d", score2);

    mvaddch(ball_y, ball_x, '*');

    refresh();
}

void DrawWin(int winner) {
    nodelay(stdscr, FALSE);
    clear();

    // Вместо \e[H используем move(0,0) или просто mvprintw
    int start_y = SCR_HG / 2 - 4;
    int start_x = SCR_WD / 2 - 20;

    if (winner == 1) {
        mvprintw(start_y + 0, start_x, "  _____ ___   __          _______ _   _ _ ");
        mvprintw(start_y + 1, start_x, " |  __ \\__ \\  \\ \\        / /_   _| \\ | | |");
        mvprintw(start_y + 2, start_x, " | |__) | ) |  \\ \\  /\\  / /  | | |  \\| | |");
        mvprintw(start_y + 3, start_x, " |  ___/ / /    \\ \\/  \\/ /   | | | . ` | |");
        mvprintw(start_y + 4, start_x, " | |    / /_     \\  /\\  /   _| |_| |\\  |_|");
        mvprintw(start_y + 5, start_x, " |_|   |____|     \\/  \\/   |_____|_| \\_(_)");
    } else {
        mvprintw(start_y + 0, start_x, "  _____  __  __          _______ _   _ _ ");
        mvprintw(start_y + 1, start_x, " |  __ \\/_ | \\ \\        / /_   _| \\ | | |");
        mvprintw(start_y + 2, start_x, " | |__) || |  \\ \\  /\\  / /  | | |  \\| | |");
        mvprintw(start_y + 3, start_x, " |  ___/ | |   \\ \\/  \\/ /   | | | . ` | |");
        mvprintw(start_y + 4, start_x, " | |     | |    \\  /\\  /   _| |_| |\\  |_|");
        mvprintw(start_y + 5, start_x, " |_|     |_|     \\/  \\/   |_____|_| \\_(_)");
    }

    mvprintw(SCR_HG - 2, SCR_WD / 2 - 12, "Press any key to exit...");
    refresh();
    getch();
    endwin();
}
// --- ЗОНА 2: Проверка ввода ---

int Input() {
    int last_input = 0;
    int kbs;

    while ((kbs = getch()) != ERR) {
        if (kbs == 'A' || kbs == 'a') last_input = -11;
        if (kbs == 'Z' || kbs == 'z') last_input = 11;
        if (kbs == 'K' || kbs == 'k') last_input = -12;
        if (kbs == 'M' || kbs == 'm') last_input = 12;
    }
    return last_input;
}

int DetectWhichPlayer(int input) {
    int player = 0;
    if (input != 0) {
        player = (input < 0) ? -input : input;
        player = player % 10;
    }
    return player;
}

int GetDirectionByInput(int input) {
    int dir = 0;
    if (input != 0) {
        dir = input / 10;
    }
    return dir;
}

// --- ЗОНА 3: Обработка ориентации движения ---
int GetBallDirectionX(int x, int ball_x, int ball_y, int player1_pos, int player2_pos) {
    int drpl1 = (ball_x == 1 && ball_y >= player1_pos && ball_y < player1_pos + PDL_SIZE);
    int drpl2 = (ball_x == SCR_WD - 2 && ball_y >= player2_pos && ball_y < player2_pos + PDL_SIZE);

    if (drpl1 || drpl2) {
        x = -x;
    }
    return x;
}

int GetBallDirectionY(int y, int ball_y) {
    if (ball_y == 0 || ball_y == SCR_HG - 1) {
        y = -y;
    }
    return y;
}

int HandlePaddleDirection(int player_direction, int player_pos) {
    if (player_direction == -1 && player_pos < 1)
        player_direction = 0;
    else if (player_direction == 1 && player_pos > SCR_HG - PDL_SIZE - 1)
        player_direction = 0;
    return player_direction;
}

// -- ЗОНА 4: Проверка гола и победы --
int CheckWin(int score1, int score2) {
    int winner = -1;
    if (score1 >= WIN_SCR)
        winner = 1;
    else if (score2 >= WIN_SCR)
        winner = 2;
    return winner;
}

int CheckGoal(int ball_x, int ball_y) {
    int score1 = 0;
    int score2 = 0;
    if (ball_x <= 0) score2++;
    if (ball_x >= SCR_WD - 1) score1++;

    return score2 * 10 + score1;
}

void interective() {
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    timeout(40);
}
int main() {
    interective();
    int ball_x = SCR_WD / 2 - 2;
    int ball_y = SCR_HG / 2;
    int ball_x_direction = -1, ball_y_direction = 1;
    int player1_pos = SCR_HG / 2, player2_pos = SCR_HG / 2;
    int score1 = 0, score2 = 0, winner;
    int frame_counter = 0;

    while ((winner = CheckWin(score1, score2)) == -1) {
        Draw(ball_x, ball_y, player1_pos, player2_pos, score1, score2);

        int input = Input();
        int which_player = DetectWhichPlayer(input);
        int player_direction = GetDirectionByInput(input);
        if (which_player == 1) {
            player1_pos += HandlePaddleDirection(player_direction, player1_pos);
        } else if (which_player == 2) {
            player2_pos += HandlePaddleDirection(player_direction, player2_pos);
        }

        if (frame_counter % BL_SPEED == 0) {
            ball_x_direction = GetBallDirectionX(ball_x_direction, ball_x, ball_y, player1_pos, player2_pos);
            ball_y_direction = GetBallDirectionY(ball_y_direction, ball_y);
            ball_x += ball_x_direction;
            ball_y += ball_y_direction;

            int goal_result = CheckGoal(ball_x, ball_y);
            if (goal_result != 0) {
                int tmp1 = goal_result % 10;
                int tmp2 = goal_result / 10;
                score1 += tmp1;
                score2 += tmp2;
                ball_x = SCR_WD / 2 + 2 * tmp1 - 2 * tmp2;
                ball_y = SCR_HG / 2;
            }
        }
        frame_counter++;
    }
    DrawWin(winner);
    return 0;
}
