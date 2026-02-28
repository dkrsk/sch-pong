#include <stdio.h>

// --- ЗОНА 1: Отрисовка ---
void Draw(int ball_x, int ball_y, int player1_pos, int player2_pos, int score1, int score2);

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

int main() {
    // Инициализация и бесконечный цикл: draw -> update
    // Проверка score и выбор победителя
    return 0;
}