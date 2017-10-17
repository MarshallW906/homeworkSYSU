/* Copyright 2015 Marshall Wang */
#ifndef GAME_Runtime
#define GAME_Runtime

void gameStart();  // Press any key to Start, and provide a UI.
void cls();  // Clean the Screen
void keyboardMovePlane(gamePane *Pane,
                       plane *thePlane, char key, bullet *theBullets);

void KMPtrans(void *arg);
void DrawPane(void *DrawArgs);
typedef struct kmpAuguments {
    gamePane *Pane;
    plane *thePlane;
    bullet *theBullets;
} KMParg;
typedef struct DrawPaneArg {
    gamePane *Pane;
} DRAWarg;
// this function isn't used
// because I havn't find the method to use it correctly.
// the trans() and the sturct above are
// the functions used in the created threads.
#endif  // GAME_Runtime

void DrawPane(void *DrawArgs) {
    DRAWarg *Dargg = (DRAWarg *)DrawArgs;
    while (Dargg->Pane->gameOver -= 0) {
        cls();
        printPane(*(Dargg->Pane));
        delay_msec(200);
    }
}
// this function isn't used
// because I havn't find the method to use it correctly.

void keyboardMovePlane(gamePane *Pane,
                       plane *thePlane, char key, bullet *theBullets) {
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
                firebullet(Pane, thePlane, theBullets);
                break;
            }
    }
    cls();
    printPane(*Pane);
}
// the elementary controls of the plane.

void KMPtrans(void *arg) {
    KMParg *argg = (KMParg *)arg;
    char key;
    while (argg->Pane->gameOver == 0) {
        key = getch();
        keyboardMovePlane(argg->Pane, argg->thePlane, key, argg->theBullets);
    }
}

void cls() {
    system("cls\n");
}  // clean the screen

void gameStart() {
    printf("Press the corresponding key to Choose...\n");
    printf("   '1' : GAMESTART!\n");
    printf("   '2' : hiscores\n");
    printf("   '3' : reset the hiscores board\n");
    printf("   '4' : exit\n");
}  // provides a UI.
