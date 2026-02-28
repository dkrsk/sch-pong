#include <stdio.h>
#define SCR_WD 80
#define SCR_HG 25
#define PDL_SIZE 3
#define WIN_SCR 2

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2) {
    const int score_y_pos = 7;

    printf("\033[H\033[2J\033[3J");  // Clear space

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
    if (winner == 1) {
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

// --- ЗОНА 2: Проверка ввода ---

int Input() {
    int input_code = -1;

    char kbs;

    while(input_code == -1) {
        kbs = getchar();

        if (kbs == 'A' || kbs == 'a') {
            input_code = -11;  
        }
        else if (kbs == 'Z' || kbs == 'z') {
            input_code = 11; 
        }
        else if (kbs == 'K' || kbs == 'k') {
            input_code = -12;  
        }
        else if (kbs == 'M' || kbs == 'm') {
            input_code = 12; 
        }
        else if (kbs == ' ') {
            input_code = 0;
        }
        else if (kbs == '\n') {
            input_code = -2;
        }
    }
    
    while ((kbs = getchar()) != '\n' && kbs != EOF); 
    return input_code;  
}

int DetectWhichPlayer(int input) {  
    int player = 0;
    if (input != 0) { 
        player = (input<0) ? -input : input;
        player = player % 10;
    }
    return player;  
}

int GetDirectionByInput (int input) {
    int dir = 0;
    if ( input != 0) {
        dir = input / 10;
    }
    return dir;
}



//

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

// -- ЗОНА 4: Проверка гола и победы --
int CheckWin(int score1, int score2) {
    int winner = -1;
    if (score1 >= WIN_SCR) winner = 1;
    else if (score2 >= WIN_SCR) winner = 2;
    return winner;
}

int CheckGoal(int ball_x, int ball_y) {
    int score1 = 0;
    int score2 = 0;
    if (ball_x <= 0) score2++;
    if (ball_x >= SCR_WD - 1) score1++;
    
    return score2 * 10 + score1;


}

int main() {
    int ball_x = SCR_WD / 2 - 2;
    int ball_y = SCR_HG / 2;
    int ball_x_direction = -1, ball_y_direction = 1;
    int player1_pos = SCR_HG / 2, player2_pos = SCR_HG / 2;
    int score1 = 0, score2 = 0;
    int winner;

    while ((winner = CheckWin(score1, score2)) == -1) {
        Draw(ball_x, ball_y, player1_pos, player2_pos, score1, score2);

        int input = Input();
        if(input != -2){
            int which_player = DetectWhichPlayer(input);
            int player_direction = GetDirectionByInput(input);
            if (which_player == 1) {
                player1_pos += player_direction;
            } else if (which_player == 2) {
                player2_pos += player_direction;
            }

            ball_x_direction = GetBallDirectionX(ball_x_direction, ball_x, ball_y, player1_pos, player2_pos);
            ball_y_direction = GetBallDirectionY(ball_y_direction, ball_y);

            ball_x += ball_x_direction;
            ball_y += ball_y_direction;

            int goal_result = CheckGoal(ball_x, ball_y);
            if(goal_result != 0)
            {
                int tmp1 = goal_result % 10;
                int tmp2 = goal_result / 10;
                score1 += tmp1;
                score2 += tmp2;
                ball_x = SCR_WD / 2 + 2*tmp1 - 2*tmp2;
                ball_y = SCR_HG / 2;
            }
        }
    }
    DrawWin(winner);
    return 0;
}

