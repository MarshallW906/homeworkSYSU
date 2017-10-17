/* Copyright 2015 Marshall Wang */
void init(gamePane * thePane, plane * thePlane, obstacle theObstacles[],
          int theObstaclesNum, bullet theBullets[], int theBulletsNum) {
  thePane->current_bullet = 5;
  thePane->Score = 0;
  thePane->HP = 2;
  thePlane->position.x = GAME_ROW - 4;
  thePlane->position.y = GAME_COL / 2;

  int i, j;

  for (i = 1; i < GAME_ROW; i++) {
    for (j = 1; j < GAME_COL - 1; j++) {
      thePane->pane[i][j] = BLANK;
    }
  }
  for (i = 0; i < GAME_COL; i++) {
    thePane->pane[0][i] = EDGE;
    thePane->pane[GAME_ROW - 3][i] = EDGE;
  }
  for (j = 0; j < GAME_ROW; j++) {
    thePane->pane[j][0] = EDGE;
    thePane->pane[j][GAME_COL - 1] = EDGE;
  }  // initialize the edge

  for (i = 0; i < theObstaclesNum / 2; i++) {
    theObstacles[i].position.x = 1;
    theObstacles[i].position.y = i * 2 + 3;
    setobstacle(thePane, &theObstacles[i]);
  }
  for (; i < theObstaclesNum; i++) {
    theObstacles[i].position.x = 6;
    theObstacles[i].position.y = i * 2 - 6;
  }
  for (i = 0; i < theBulletsNum; i++) {
    theBullets[i].position.x = GAME_ROW - 2;
    theBullets[i].position.y = i + 5;
    setbullet(thePane, &theBullets[i]);
  }
  setplane(thePane, thePlane);
  thePane->gameOver = 0;
  thePane->cursor.x = 0;
  thePane->cursor.y = 0;
}
/*
  The function init INITIALIZES the GAMEPANE,
   initializes the PLANE and the 10 OBSTACLES's positions
   initializes the PLANE's HP = 1, Bullets ready = 5, and the EDGE.
   and initializes the position of BLANKs(the other points be BLANK)
   Initialized the Pane's Cursor
*/


// basic operation for game pane
void setCursor(gamePane * thePane, const int x, const int y) {
  thePane->cursor.x = x;
  thePane->cursor.y = y;
} /*Set the cursor's position of the Pane */

void setplane(gamePane * thePane, plane * plane) {
  if (thePane->pane[plane->position.x][plane->position.y] == OBSTACLE) {
    thePane->HP--;
    if (thePane->HP <= 0) {
      thePane->gameOver = 1;
    }
    return;
  }
  thePane->pane[plane->position.x][plane->position.y] = PLANE;
}
/*
    Set the position of the plane
    which is used when initializing or moving
    Also provides the judge of HP decrease & Gameover.
*/

void setobstacle(gamePane * thePane, obstacle * obstacle) {
  if (thePane->pane[obstacle->position.x][obstacle->position.y] == PLANE) {
    thePane->HP--;
    if (thePane->HP <= 0) {
      thePane->gameOver = 1;
    }
    return;
  }
  thePane->pane[obstacle->position.x][obstacle->position.y] = OBSTACLE;
}
/*
    Set the Obstacles's position
    which is used when initializing or moving
    Also provides the judge of decrease & Gameover.
*/

void removeOBJ(gamePane * thePane, const point p) {
  thePane->pane[p.x][p.y] = BLANK;
}
/* A basic operation used in functions of moving:(first remove then create)
*/

void gameOver() {
  printf("GameOver\n");
}  // Print the signal of Gameover.

void printPane(const gamePane thePane) {
  int i, j;
  for (i = 0; i < GAME_ROW - 2; i++) {
    for (j = 0; j < GAME_COL; j++) {
      printf("%c", thePane.pane[i][j]);
    }
    printf("\n");
  }
  printf("Score : %12d\n\n", thePane.Score);
  printf("HP : %15d\n", thePane.HP);
  printf("Missiles ready : %3d\n", thePane.current_bullet);
}  // for Updating the Pane
// the Pane consists of not only the map, also  the necessary texts.
// including HP, Score, Bullets ready.

// operation for plane
void movePlane(gamePane * thePane, plane * thePlane, OP op) {
  removeOBJ(thePane, thePlane->position);
  switch (op) {
    case 0 :
      if (thePlane->position.x > 1 &&
          thePane->pane[thePlane->position.x - 1]
          [thePlane->position.y] != BULLET) {
        thePlane->position.x--;
      }
      break;
    case 1 :
      if (thePlane->position.x < GAME_ROW - 4 &&
          thePane->pane[thePlane->position.x + 1]
          [thePlane->position.y]
          != BULLET) {
        thePlane->position.x++;
      }
      break;
    case 2:
      if (thePlane->position.y > 1 &&
          thePane->pane[thePlane->position.x]
          [thePlane->position.y - 1]
          != BULLET) {
        thePlane->position.y--;
      }
      break;
    case 3:
      if (thePlane->position.y < GAME_COL - 2 &&
          thePane->pane[thePlane->position.x]
          [thePlane->position.y + 1]
          != BULLET) {
        thePlane->position.y++;
      }
      break;
  }
  setplane(thePane, thePlane);
}
/*
    Move the plane.
    when the plane is on the side of the pane, it won't make it outside.
    also when the plane is beside a bullet it won't move there.
    case 0 is for UP, 1 for DOWN, 2 for LEFT, 3 for RIGHT.
*/

// operations for obstacle
void moveObstacle(gamePane * thePane,
                  obstacle * theObstacle, bullet theBullets[]) {
  removeOBJ(thePane, theObstacle->position);
  if (theObstacle->position.x >= GAME_ROW - 4) {
    theObstacle->position.x = 0;
    thePane->Score += 1;
  }
  int i;
  for (i = 0; i < 5; i++) {
    if ((theBullets[i].position.x == theObstacle->position.x) &&
        (theBullets[i].position.y == theObstacle->position.y)) {
      if (thePane->HP < 3) {
        thePane->HP++;
      }
      point tempBullet;
      tempBullet = theObstacle->position;
      tempBullet.x++;
      theBullets[i].position = theBullets[thePane->current_bullet].position;
      theBullets[thePane->current_bullet].position = tempBullet;

      theBullets[thePane->current_bullet].position.x = GAME_ROW - 2;
      setbullet(thePane, &theBullets[thePane->current_bullet]);
      thePane->current_bullet++;
      theObstacle->position.x = GAME_ROW - 2;
      theObstacle->position.y = rand() % 16 + 1;
      thePane->Score += 100;
      break;
    }
  }
  // when the obstacls is attacked by the bullets, it will crash
  // and the player will get 100 Score.
  // Besides, if the plane's HP is less than 3,
  //      it will also provide a 1-HP recovery.
  // DON'T THINK IT IS EASY, HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA

  // What's more,
  // It is the algorithm about the collision
  // between the bullets and the obstacles.
  // it runs just like a stack.
  // when a collision is to occur
  // first search and judge which bullet is processing.
  // then exchange the searched bullet
  // with the top-number bullets and drop it off.
  // so that it will perform correct collision actions
  // and won't crash with Runtime Error
  //              due to the invalid No. to access the bullet array.

  theObstacle->position.x++;
  theObstacle->position.y = rand() % 16 + 1;
  setobstacle(thePane, theObstacle);
  // this is the basic obstacles-moving action.
  // every time-count, the obstacle will sink for one block
  //    Specially, the position.y is randomly various.
  // so it won't be easy that the plane can remain one place and just
  //    shoot the bullets, or it will quickly crash to gameOver.
}
/* Move the Obstacles.
    when the Obstacles is to be outside the pane, it will surely move out.
*/

// operations for bullet
void moveBullet(gamePane * thePane, bullet * theBullet) {
  if (theBullet->position.x >= GAME_ROW - 4) {
    return;
  }
  removeOBJ(thePane, theBullet->position);
  if (theBullet->position.x <= 1) {
    theBullet->position.x = GAME_ROW - 2;
    if (thePane->current_bullet < 5) {
      thePane->current_bullet++;
    }
    setbullet(thePane, theBullet);
    return;
  }
  // if outside then reposition the bullet to cache
  // so that it is reuseable
  // and looks as if it has been destroyed and reprepared.

  theBullet->position.x--;  // every time-count, it rises one block.
  setbullet(thePane, theBullet);
}

void firebullet(gamePane * thePane, plane * thePlane, bullet *theBullets) {
  if (thePane->current_bullet > 0) {
    thePane->current_bullet--;
    removeOBJ(thePane, theBullets[thePane->current_bullet].position);
    theBullets[thePane->current_bullet].position.x = thePlane->position.x - 1;
    theBullets[thePane->current_bullet].position.y = thePlane->position.y;
    setbullet(thePane, theBullets + thePane->current_bullet);
  }
}
// first judge if any bullet is ready.(bullet-ready > 0)
// if so, then create a bullet in front of the PLANE
// and consequencely the number of the bullet-ready is reduced by 1.

void setbullet(gamePane * thePane, bullet * bullet) {
  thePane->pane[bullet->position.x][bullet->position.y] = BULLET;
}
// simply change the elements of the map of the gamePane.
// all the corresponding other operation will use this function.
