/* Copyright 2015 Marshall Wang */
// this game's programming include the structure, pointers
// also it is about a simple practice of
//                       MULTITHREADED programming(......)
// process.h and windows.h are both available On just windows NT
// for instance, MULTITHREADED is implemented by another .h file on unix.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "GameStructure.c"
// basic diminations of the basic spirtes and the declarations of the functions.
#include "GameSource.c"
// the diminations of the functions above.
#include "GameRuntime.c"
// some functions used to control the processing during the game running.



int delay_sec(int interval);  // return 1 when delay is successful, 0 for ERROR
int delay_msec(int interval);
// the two is used so that the program can perform "sleep".
void gameplaying();  // it's the main gameplay code.

void read_print_Hiscores();
void submit_scores(int sc);
void reset_Hiscores();
// the three above are related to the file I/O to record the hiscores.

int main() {
    // Game Start code
    cls();
    int c;
    while (1) {
        gameStart();  // it prints a simple UI.
        fflush(stdin);
        scanf("%d", &c);  // request an input.
        fflush(stdin);
        switch (c) {  // the menu's implement
            case 1 : {
                    gameplaying();
                    break;
                }
            case 2 : {
                    read_print_Hiscores();
                    break;
                }
            case 3 : {
                    reset_Hiscores();
                    break;
                }
            case 4 : {
                    return 0;  // exit the Game.
                }
            default : {
                    printf("Invalid command.Please try again.\n");
                    break;
                }
        }
    }
    return 0;
}

int delay_sec(int interval) {
    time_t current_time, start_time;
    time(&start_time);
    do {
        time(&current_time);
    } while (current_time - start_time < interval);
    return 1;
}
int delay_msec(int interval) {
    clock_t current_time, start_time;
    start_time = clock();
    do {
        current_time = clock();
    } while (current_time - start_time < interval);
    return 1;
}

void gameplaying() {
    // create the basic sprites of the Game.
    gamePane *Pane = (gamePane *)malloc(sizeof(gamePane));
    plane *thePlane = (plane *)malloc(sizeof(plane));
    obstacle *obstacles = (obstacle *)malloc(sizeof(obstacles) * 10);
    bullet *bullets = (bullet *)malloc(sizeof(bullet) * 5);
    // Game Playing code
    cls();
    init(Pane, thePlane, obstacles, 10, bullets, 5);

    // Create another two threads, one to Draw, one to keyboard

    // DRAWarg *Darg = (DRAWarg *)malloc(sizeof(DRAWarg));
    // Darg->Pane = Pane;
    // this function isn't used because
    // I havn't find the method to use it correctly.

    KMParg *arg = (KMParg *)malloc(sizeof(KMParg));
    arg->Pane = Pane;
    arg->thePlane = thePlane;
    arg->theBullets = bullets;
    printPane(*Pane);
    HANDLE keymovePlane, Draws;
    if ((keymovePlane = _beginthread(KMPtrans, 0, (void *)arg)) == -1) {
        printf("Process creation failed!!\n");
        return;
    } else {
        printf("Process 1 successfully Created.\n");
    }
    /*if ((Draws = _beginthread(DrawPane, 0, (void *)Darg)) == -1) {
        printf("Process creation failed!!\n");
        return 0;
    } else printf("Process 2 successfully Created.\n");
    //the inner gameplaying code : obstacles moving, etc.*/
    int obstaclesNum = 0, bulletsNum = 0;
    while (Pane->gameOver == 0) {
        for (bulletsNum = 0; bulletsNum < 5; bulletsNum++) {
            moveBullet(Pane, bullets + bulletsNum);
        }
        for (obstaclesNum = 0; obstaclesNum < 10; obstaclesNum++) {
            moveObstacle(Pane, obstacles + obstaclesNum, bullets);
        }

        cls();
        printPane(*Pane);
        delay_msec(700);
        // the main loop of the Game.
        // it repeatedly updates the gamePane and other informations.
    }
    // GameOver code
    gameOver();
    printf("Your final score is : %d\n\n.......\n", Pane->Score);
    submit_scores(Pane->Score);
    printf("Press any key and <CR> to back...\n");
    char ss[200];
    gets(ss);

    // Things to be done when the process is terminated.
    free(Pane);
    free(thePlane);
    free(arg);
    // free(Darg);
    free(obstacles);
    free(bullets);
}

void read_print_Hiscores() {
    cls();
    FILE *fp = fopen("hiscores.txt", "r");
    int hisc[10] = {0}, i = 0, n = 0, j;
    while (!feof(fp)) {
        fscanf(fp, "%d", &hisc[i]);
        i++;
        n++;
    }
    n--;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (hisc[i] < hisc[j]) {
                int t = hisc[i];
                hisc[i] = hisc[j];
                hisc[j] = t;
            }
    for (i = 0; i < n; i++) {
        printf("%2d %5d\n", i + 1, hisc[i]);
    }
    fclose(fp);
    printf("Press any key and <CR> to back\n");
    char s[200];
    gets(s);
}
// it reads the file which storing the hiscores records
// and prints it out to stdout.

void submit_scores(int sc) {
    printf("Submitting score......\n");
    delay_sec(1);
    FILE *fp = fopen("hiscores.txt", "r+");
    int hisc[10] = {0}, i = 0, n = 0, j, min = 0;
    while (!feof(fp)) {
        fscanf(fp, "%d", &hisc[i]);
        i++;
        n++;
    }
    for (i = 0; i < 10; i++) {
        if (hisc[min] > hisc[i]) min = i;
    }
    if (sc <= hisc[min]) {
        fclose(fp);
        printf("Sorry....\n");
        printf("Your score isn't high enough to submit.\n");
        return;
    }
    hisc[min] = sc;
    for (i = 0; i < 9; i++)
        for (j = 0; i + j  + 1 < 10; j++)
            if (hisc[j] < hisc[j + 1]) {
                int t = hisc[j];
                hisc[j] = hisc[j + 1];
                hisc[j + 1] = t;
            }  // a simple bubble sort
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < 10; i++) {
        fprintf(fp, "%d\n", hisc[i]);
    }
    fclose(fp);
    printf("Score submitted successfully.\n");
    delay_sec(1);
}
// every time one game is terminated, this function will submit the score.
// records 10 scores at most.

void reset_Hiscores() {
    FILE *fp = fopen("hiscores.txt", "w");
    int i;
    for (i = 0; i < 10; i++)
        fprintf(fp, "0\n");
    fclose(fp);
    printf("Reset hiscores to all zero.....\n");
    delay_sec(1);
    printf("Succeed.\n\n");
}
// reset all the hiscores to zero.
