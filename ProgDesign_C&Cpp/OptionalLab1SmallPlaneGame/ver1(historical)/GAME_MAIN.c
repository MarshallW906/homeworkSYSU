#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include <windows.h>
#include "GameStructure.c"
#include "GameSource.c"

int delay_sec(int interval); //return 1 when delay is successful, 0 for ERROR
void gameStart();// Press any key to Start
void cls(); //Clean the Screen
void keyboardMovePlane(gamePane *Pane, plane *thePlane, char key);
void KMPtrans(void *arg);

typedef struct kmpAuguments {
    gamePane *Pane;
    plane *thePlane;
} KMParg;

int main() {
    // create the basic sprites of the Game.
    gamePane *Pane = (gamePane *)malloc(sizeof(gamePane));
    plane *thePlane = (plane *)malloc(sizeof(plane));
    obstacle *Obs1 = (obstacle *)malloc(sizeof(obstacle));
    obstacle *Obs2 = (obstacle *)malloc(sizeof(obstacle));

    // Game Start code
    cls();
    gameStart();
    char c = getch();

    // Game Playing code
    cls();
    init(Pane, thePlane, Obs1, Obs2);
    KMParg *arg = (KMParg *)malloc(sizeof(KMParg));
    arg->Pane = Pane;
    arg->thePlane = thePlane;
    printPane(*Pane);
    HANDLE keymovePlane;
    if ((keymovePlane = _beginthread(KMPtrans, 0, (void *)arg)) == -1) {
        printf("Process creation failed!!\n");
        return 0;
    }
    //the inner gameplaying code : obstacles moving, etc.
    while (Pane->gameOver == 0) {
        moveObstacle(Pane, Obs1);
        moveObstacle(Pane, Obs2);
        /*if (Obs1->position.y < 0) {
            Obs1->position.y = GAME_ROW - 1;
            setobstacle(Pane, Obs1);
        }
        if (Obs2->position.y < 0) {
            Obs2->position.y = GAME_ROW - 1;
            setobstacle(Pane, Obs2);
        }*/
        cls();
        printPane(*Pane);
        //delay_sec(1);
        sleep(1);
    }
    // GameOver code
    gameOver();

    // Restart code (immediately after GameOver)

    // Things to be done when the program is terminated.
    free(Pane);
    free(thePlane);
    free(Obs1);
    free(Obs2);
    free(arg);
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

void keyboardMovePlane(gamePane *Pane, plane *thePlane, char key) {
    switch (key) {
        case 'w':
        case 'W': {
                movePlane(Pane, thePlane, 0);
                break;
            }
        case 'a':
        case 'A': {
                movePlane(Pane, thePlane, 2);
                break;
            }
        case 's':
        case 'S': {
                movePlane(Pane, thePlane, 1);
                break;
            }
        case 'd':
        case 'D': {
                movePlane(Pane, thePlane, 3);
                break;
            }
        case 'j' :
        case 'J' : {
                break;
            }
    }
    cls();
    printPane(*Pane);
}

void KMPtrans(void *arg) {
    KMParg *argg = (KMParg *)arg;
    char key;
    while (argg->Pane->gameOver == 0) {
        key = getch();
        keyboardMovePlane(argg->Pane, argg->thePlane, key);
    }
    //_endthread();
}

void cls() {
    system("cls");
}

void gameStart() {
    printf("Press any key to Start...\n");
}
