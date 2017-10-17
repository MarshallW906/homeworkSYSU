void init(gamePane * thePane, plane * thePlane, obstacle * theObstacle1, obstacle * theObstacle2) {
  thePlane->position.x = 0;
  thePlane->position.y = 0;
  theObstacle1->position.x = 0;
  theObstacle1->position.y = GAME_COL-1;
  theObstacle2->position.x = 1;
  theObstacle2->position.y = GAME_COL-4;

  int i, j;

  for (i = 0; i < GAME_ROW; i++) {
    for (j = 0; j < GAME_COL; j++) {
      thePane->pane[i][j] = BLANK;
    }
  }

  setplane(thePane, thePlane);
  setobstacle(thePane, theObstacle1);
  setobstacle(thePane, theObstacle2);
  thePane->gameOver = 0;
  thePane->cursor.x = 0;
  thePane->cursor.y = 0;
}
/* The function init INITIALIZES the GAMEPANE, the PLANE , the 2 OBSTACLES
   It initializes the position of PLANE & OBSTACLES, BLANKS(the other points be BLANK)
   Initialized the Pane's Cursor
*/


// basic operation for game pane
void setCursor(gamePane * thePane, const int x, const int y) {
  thePane->cursor.x = x;
  thePane->cursor.y = y;
} /*Set the cursor's position of the Pane */

void setplane(gamePane * thePane, plane * plane) {
  if (thePane->pane[plane->position.x][plane->position.y] == OBSTACLE) {
    thePane->gameOver = 1;
    gameOver();
    return;
  }
  thePane->pane[plane->position.x][plane->position.y] = PLANE;
}/* Set the position of the plane
    which is used when initializing or moving
    Also provides the judge of Gameover
*/

void setobstacle(gamePane * thePane, obstacle * obstacle) {
  if (thePane->pane[obstacle->position.x][obstacle->position.y] == PLANE) {
    thePane->gameOver = 1;
    gameOver();
    return;
  }
  thePane->pane[obstacle->position.x][obstacle->position.y] = OBSTACLE;
}/* Set the Obstacles's position
    which is used when initializing or moving
    Also provides the judge of Gameover
*/

void removeOBJ(gamePane * thePane, const point p) {
  thePane->pane[p.x][p.y] = BLANK;
}/* A basic operation used in functions of moving:(first remove then create)
*/

void gameOver() {
  printf("GameOver\n");
}// Print the signal of Gameover.

void printPane(const gamePane thePane) {
  int i, j;
  for (i = 0; i < GAME_ROW; i++) {
    for (j = 0; j < GAME_COL; j++) {
      printf("%d", thePane.pane[i][j]);
    }
    printf("\n\n");
  }
}// for Updating the Pane

// operation for plane
void movePlane(gamePane * thePane, plane * thePlane, OP op) {
  removeOBJ(thePane, thePlane->position);
  switch (op) {
    case 0 :
      if (thePlane->position.x > 0) {
        thePlane->position.x--;
      }
      break;
    case 1 :
      if (thePlane->position.x < GAME_ROW - 1) {
        thePlane->position.x++;
      }
      break;
    case 2:
      if (thePlane->position.y > 0) {
        thePlane->position.y--;
      }
      break;
    case 3:
      if (thePlane->position.y < GAME_COL - 1) {
        thePlane->position.y++;
      }
      break;
  }
  setplane(thePane, thePlane);
}/* Move the plane.
    when the plane is on the side of the pane, it won't make it outside.
*/

//operations for obstacle
void moveObstacle(gamePane * thePane, obstacle * theObstacle) {
  removeOBJ(thePane, theObstacle->position);
  if (theObstacle->position.y <= 0) {
    theObstacle->position.y = GAME_COL - 1;
  }

  theObstacle->position.y--;

  setobstacle(thePane, theObstacle);
}/* Move the Obstacles.
    when the Obstacles is to be outside the pane, it will surely move out.
*/
