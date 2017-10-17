void init(gamePane * thePane, plane * thePlane, obstacle * theObstacle1, obstacle * theObstacle2) {
  thePlane->position.x = GAME_ROW - 2;
  thePlane->position.y = GAME_COL / 2;
  theObstacle1->position.x = 1;
  theObstacle1->position.y = GAME_COL-3;
  theObstacle2->position.x = 2;
  theObstacle2->position.y = GAME_COL-6;

  int i, j;

  for (i = 1; i < GAME_ROW - 1; i++) {
    for (j = 1; j < GAME_COL - 1; j++) {
      thePane->pane[i][j] = BLANK;
    }
  }
  for (i = 0; i < GAME_COL; i++) {
    thePane->pane[0][i] = EDGE;
    thePane->pane[GAME_ROW - 1][i] = EDGE;
  }
  for (j = 0; j < GAME_ROW; j++) {
    thePane->pane[j][0] = EDGE;
    thePane->pane[j][GAME_COL - 1] = EDGE;
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

void setbullet(gamePane * thePane, bullet * bullet) {
  // add an if () {} ?
  thePane->pane[bullet->position.x][bullet->position.y] = BULLET;
}

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
      printf("%c", thePane.pane[i][j]);
    }
    printf("\n\n");
  }
}// for Updating the Pane

// operation for plane
void movePlane(gamePane * thePane, plane * thePlane, OP op) {
  removeOBJ(thePane, thePlane->position);
  switch (op) {
    case 0 :
      if (thePlane->position.x > 1 && thePane->pane[thePlane->position.x - 1][thePlane->position.y] != BULLET) {
        thePlane->position.x--;
      }
      break;
    case 1 :
      if (thePlane->position.x < GAME_ROW - 2 && thePane->pane[thePlane->position.x - 1][thePlane->position.y] != BULLET) {
        thePlane->position.x++;
      }
      break;
    case 2:
      if (thePlane->position.y > 1 && thePane->pane[thePlane->position.x - 1][thePlane->position.y] != BULLET) {
        thePlane->position.y--;
      }
      break;
    case 3:
      if (thePlane->position.y < GAME_COL - 2 && thePane->pane[thePlane->position.x - 1][thePlane->position.y] != BULLET) {
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
  if (theObstacle->position.x >= GAME_ROW - 2) {
    theObstacle->position.x = 0;
  }

  theObstacle->position.x++;

  setobstacle(thePane, theObstacle);
}/* Move the Obstacles.
    when the Obstacles is to be outside the pane, it will surely move out.
*/

void moveBullet(gamePane * thePane, bullet * theBullet) {
  removeOBJ(thePane, theBullet->position);
  if (theBullet->position.x <= 1) {
    return;
  }
  theBullet->position.x--;

  setbullet(thePane, theBullet);
}

void firebullet(gamePane * thePane, plane * thePlane) {}
