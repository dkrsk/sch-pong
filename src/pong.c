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

// --- ЗОНА 2: Проверка ввода ---

int Input() {
    char kbs = getchar ();
    int input_code = -1;

    while(1) {
        if (kbs == 'A' || kbs == 'a') {
            input_code = 11;  
        }
        else if (kbs == 'Z' || kbs == 'z') {
            input_code = -11; 
        }
        else if (kbs == 'K' || kbs == 'k') {
            input_code = 12;  
        }
        else if (kbs == 'M' || kbs == 'm') {
            input_code = -12; 
        }
        else if (kbs == ' ') {
            input_code = 0;   
        }
        if(input_code != -1){
            break;
        }
    }
    
    
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
int DirectionX(int x, int ball_x, int ball_y, int player1_pos, int player2_pos, int paddle_size, int screen_width);
int DirectionY(int y, int ball_y, int screen_height);

// -- ЗОНА 4: Проверка гола и победы --
int CheckWin(int score1, int score2);
int CheckGoal(int ball_x, int ball_y);

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

