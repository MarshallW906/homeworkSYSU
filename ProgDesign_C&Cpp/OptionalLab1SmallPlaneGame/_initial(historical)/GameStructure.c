#ifndef GAME_H
#define GAME_H

typedef struct point {
    int x;
    int y;
} point;

typedef enum objects {BLANK = 0, PLANE = 1, OBSTACLE = 2} OBJ;
typedef enum operations {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3} OP;

#define GAME_ROW 2
#define GAME_COL 16

typedef struct gamePane {
    // the game pane, 0 for blank, 1 for plane and 2 for obstacle
    OBJ pane[GAME_ROW][GAME_COL];
    point cursor;
    int gameOver;
} gamePane;

typedef struct plane {
    point position;
} plane;

typedef struct obstacle {
    point position;
} obstacle;

// function list
void init(gamePane * thePane, plane * thePlane, obstacle * theObstacle1, obstacle * theObstacle2);
void setCursor(gamePane * thePane, const int x, const int y);
void setplane(gamePane * thePane, plane * plane);
void setobstacle(gamePane * thePane, obstacle * obstacle);
void removeOBJ(gamePane * thePane, const point p);
void gameOver();
void printPane(const gamePane thePane);
void movePlane(gamePane * thePane, plane * thePlane, OP op);
void moveObstacle(gamePane * thePane, obstacle * theObstacle);
#endif // GAME_H
