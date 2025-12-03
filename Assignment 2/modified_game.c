#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}
void hide_cursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(h, &info);
}
void show_cursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);
    info.bVisible = TRUE;
    SetConsoleCursorInfo(h, &info);
}

void print_frame_top() {
    printf("|--- --- ---|\n");
}
void print_empty_row() {
    printf("|           |\n");
}

int main() {
    srand((unsigned)time(0));
    hide_cursor();

    int x = 1;           
    int step1 = 0;
    int step2 = -5;
    int pos1 = rand() % 3;
    int pos2 = rand() % 3;

    int score = 0;
    int lives = 3;
    int gameOver = 0;

    while (pos1 == pos2) pos2 = rand() % 3;
    print_frame_top();
    for (int i = 0; i < 10; i++) print_empty_row();
    printf("|     [^]   |\n");
    printf("\nScore: 0 | Lives: 3\n");

    while (!gameOver) {
        if (_kbhit()) {
            int ch = getch();
            if (ch == 0 || ch == 224) ch = getch();  
            if (ch == 75 && x > 0) x--;   
            if (ch == 77 && x < 2) x++;   
            if (ch == 'a' || ch == 'A') { if (x > 0) x--; }
            if (ch == 'd' || ch == 'D') { if (x < 2) x++; }
        }
        clear_screen_fast();
        print_frame_top();

        for (int i = 0; i < 10; i++) {
            int printed = 0;
            if (i == step1) {
                if (pos1 == 0) { printf("| {*}       |\n"); printed = 1; }
                else if (pos1 == 1) { printf("|    {*}    |\n"); printed = 1; }
                else { printf("|       {*} |\n"); printed = 1; }
            }
            if (!printed && i == step2) {
                if (pos2 == 0) { printf("| {*}       |\n"); printed = 1; }
                else if (pos2 == 1) { printf("|    {*}    |\n"); printed = 1; }
                else { printf("|       {*} |\n"); printed = 1; }
            }

            if (!printed) {
                print_empty_row();
            }
        }
        if (x == 0) printf("| [^]       |\n");
        else if (x == 1) printf("|     [^]   |\n");
        else printf("|       [^] |\n");
        if ((step1 == 9 && x == pos1) || (step2 == 9 && x == pos2)) {
            lives--;
            if (lives <= 0) {
                gameOver = 1;
            } else {
                step1 = 0;
                pos1 = rand() % 3;
                step2 = -5;
                pos2 = rand() % 3;
                while (pos1 == pos2) pos2 = rand() % 3;
            }
        }

        printf("\nScore: %d | Lives: %d\n", score, lives);

        if (gameOver) {
            printf("\nGAME OVER!\nFinal Score: %d\n", score);
            break;
        }

        Sleep(120);
        step1++;
        step2++;

        if (step1 > 9) {
            step1 = 0;
            pos1 = rand() % 3;
            score++;
        }

        if (step2 > 9) {
            step2 = -5;
            pos2 = rand() % 3;
            while (pos1 == pos2) pos2 = rand() % 3;
            score++;
        }
    }
    show_cursor();
    return 0;
}
