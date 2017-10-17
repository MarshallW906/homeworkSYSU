/* Copyright 2015 Marshall Wang */
#ifndef GAME_H
#define GAME_H

typedef struct point {
    int x;
    int y;
} point;
// use to memory every corresponding sprites's position if necessary.

typedef enum objects {BLANK = ' ', PLANE = 'A',
                      OBSTACLE = 'O', EDGE = '+', BULLET = 'i'
                     } OBJ;
// redefine some constant
// which will make the following programming easier.
typedef enum operations {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3} OP;
// it maps the 4-direction moving action
// to the keyboards and codes.

#define GAME_ROW 16
#define GAME_COL 18
// dim the size of the gamePane.

typedef struct gamePane {
    // the game pane, 0 for blank, 1 for plane and 2 for obstacle
    OBJ pane[GAME_ROW][GAME_COL];
    point cursor;
    int gameOver;
    int current_bullet;
    int Score;
    int HP;
    // the last 3 variables are used
    // to conveniently record the plane's properties.
} gamePane;

// the following three ones
// are the basic dynamic sprites of the game.
typedef struct plane {
    point position;
} plane;

typedef struct obstacle {
    point position;
} obstacle;

typedef struct bullet {
    point position;
} bullet;

// function list of the operations
// of the basic sprites of the game.
void init(gamePane * thePane, plane * thePlane, obstacle theObstacles[],
          int theObstaclesNum, bullet theBullets[], int theBulletsNum);
void setCursor(gamePane * thePane, const int x, const int y);
void setplane(gamePane * thePane, plane * plane);
void setobstacle(gamePane * thePane, obstacle * obstacle);
void setbullet(gamePane * thePane, bullet * bullet);
void firebullet(gamePane * thePane, plane * thePlane, bullet * theBullets);
void removeOBJ(gamePane * thePane, const point p);
void gameOver();
void printPane(const gamePane thePane);
void movePlane(gamePane * thePane, plane * thePlane, OP op);
void moveObstacle(gamePane * thePane
                  obstacle * theObstacle, bullet theBullets[]);
void moveBullet(gamePane * thePane, bullet * theBullet);
#endif  // GAME_H
