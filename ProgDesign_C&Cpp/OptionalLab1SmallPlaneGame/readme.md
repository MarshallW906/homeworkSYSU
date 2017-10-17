#week10 Optional Experiment : Small Plane Game (C Programming)
@(小飞机游戏)[15331302|王翔宇|C语言|软件工程2015级1班]

[toc]

## Assignment 0 : (implement in the code)
## Assignment 1 : 游戏内容改进
改进主要分如下几个方面：
1. 修改显示元素
2. 扩大地图
3. 计分系统、生命值、高分榜
4. 为小飞机增加子弹
5. 更改障碍物行进模式

###Part 1 修改显示元素
将原来用以表示地图元素的“0， 1， 2”换掉，对应为：
1. 空地为空格
2. 飞机为大写字母“A”
3. 障碍物为大写字母“O”

同时新增几种元素：墙（符号“+”）、子弹（小写字母“i”）。

代码中需要修改的地方主要是：
enum OBJ
init（Pane部分）
printPane。

代码如下：
enum OBJ :
```c
typedef enum objects {BLANK = ' ', PLANE = 'A', OBSTACLE = 'O', EDGE = '+', BULLET = 'i'} OBJ;
```

init :
```c
  for (i = 1; i < GAME_ROW; i++) {
    for (j = 1; j < GAME_COL - 1; j++) {
      thePane->pane[i][j] = BLANK;
    }
  }
  for (i = 0; i < GAME_COL; i++) {
    thePane->pane[0][i] = EDGE;
    thePane->pane[GAME_ROW - 3][i] = EDGE;
  } // initialize the edge
  for (j = 0; j < GAME_ROW; j++) {
    thePane->pane[j][0] = EDGE;
    thePane->pane[j][GAME_COL - 1] = EDGE;
  } // initialize the edge
```
这里预留了两行不输出的GAME_ROW是为了方便储存未发射的子弹和刚飞过的陨石，方便其重新出现，做出不断产生和消失的效果。

printPane();
```c
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
}// for Updating the Pane
// the Pane consists of not only the map, also  the necessary texts.
// including HP, Score, Bullets ready.
```

###Part 2 扩大地图
很简单，只需要修改预定义的`GAME_ROW``GAME_COL`即可。
```cpp
#define GAME_ROW 16
#define GAME_COL 18
```

###Part 3 计分系统以及高分榜
计分需要一个Score，本次将Score为方便，保存在了GamePane当中，令其每次游戏开始时初始化为0。每次游戏结束，在释放gamePane之前将Score作为参数提交给对应函数即可。
####计分、生命值
```cpp
typedef struct gamePane {
    // the game pane, 0 for blank, 1 for plane and 2 for obstacle
    OBJ pane[GAME_ROW][GAME_COL];
    point cursor;
    int gameOver;
    int current_bullet;
    int Score;
    int HP;
    // the last 3 variables are used to conveniently record the plane's properties.
} gamePane;
```
初始化：
```cpp
void init(gamePane * thePane, ...) {
	/* some code */
	thePane->Score = 0;
	thePane->HP = 2;
	/* some other code */
}
```

数值增减：每使用子弹击毁一个障碍物，HP+1（上限为3）、Score + 100；
飞机每碰到一次障碍物，HP - 1，HP 小于等于0时游戏结束；
每当一个障碍物走到地图最下方，Score + 1.
```cpp
void setplane(gamePane * thePane, plane * plane) {
  if (thePane->pane[plane->position.x][plane->position.y] == OBSTACLE) {
    thePane->HP--;
    }
    /* other code */
}
```
```cpp
void setobstacle(gamePane * thePane, obstacle * obstacle) {
  if (thePane->pane[obstacle->position.x][obstacle->position.y] == PLANE)
    thePane->HP--;
    /* other code */
}
```
```
  if (theObstacle->position.x >= GAME_ROW - 4) {
    theObstacle->position.x = 0;
    thePane->Score += 1;
  }
```
```cpp
  for (i = 0; i < 5; i++) {
    if ((theBullets[i].position.x == theObstacle->position.x) && (theBullets[i].position.y == theObstacle->position.y)) {
      if (thePane->HP < 3) {
        thePane->HP++;
      }
	  /* other code */
      thePane->Score += 100;
      break;
    }
  }
```
####高分榜
高分榜分三个函数：
1. 显示高分榜：在主界面上通过输入指令调用。调用过程中使用只读方式即可。
2. 提交分数：每轮游戏结束之后自动提交记录申请，若分数可以进入高分榜，显示`submit success`，否则显示`not enough score`。满足条件的分数将替换掉原最低值进入榜单。
3. 重置高分榜：可以将高分榜中所有数据全部清空，重置为0。

```cpp
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
            } // a simple bubble sort
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i < 10; i++) {
        fprintf(fp, "%d\n", hisc[i]);
    }
    fclose(fp);
    printf("Score submitted successfully.\n");
    delay_sec(1);
}

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
```

###Part 4 为小飞机增加子弹
子弹在地图中用小写字母`i`表示。
####小型感想
添加子弹模块是程序书写过程中最花费时间的环节之一。因其是在原有的完整版上再进行修改，（该部分实现）在修改接口，增加方法上花费的时间远比从零开始多。
conclusion：在开发之前决定好程序的功能和每个函数的接口很重要。
####实现过程
游戏中小飞机最多可以装填5枚子弹。
每发射一枚子弹，现有装填数-1；每当子弹遇到障碍物（将其“摧毁”）或者子弹超出地图上界之后，将该子弹移动到gamePane预留的缓冲区中。缓冲区中的子弹不会因为moveBullet()方法而不断上移。从而做出较为正确的子弹发射逻辑。
子弹的摧毁和重置，若仅通过数组下标增减，每次几乎都不能将正确（编号，因为是以数组的形式存放）的子弹重置成未使用的状态。程序中使用了类似栈的方法：每当摧毁情况即将发生时，先对整个bullet数组进行遍历，找到对应位置的子弹的正确编号，然后将其与“栈顶”的子弹进行交换，后执行出栈操作，即可实现正确的逻辑。
```cpp
      point tempBullet;
      tempBullet = theObstacle->position;
      tempBullet.x++;
      theBullets[i].position = theBullets[thePane->current_bullet].position;
      theBullets[thePane->current_bullet].position = tempBullet;

      theBullets[thePane->current_bullet].position.x = GAME_ROW - 2;
      setbullet(thePane, &theBullets[thePane->current_bullet]);
      thePane->current_bullet++;
```

###Part 5 更改障碍物前进模式
原本：以直线向下移动，每当该障碍物被摧毁或是移动到地图最下方后，会议随机的横坐标重新出现在地图顶端。
现为提高这个游戏的趣味性（毒性），将障碍物直线向下移动改为每下沉一格都会随机变化其横坐标。所以无法判断障碍物在接近自身只后究竟会如何移动。
```cpp
theObstacle->position.y = rand() % 16 + 1;
```
在本程序中，x为直观意义上的纵坐标，且为向下递增；y为横坐标。主要是为了进行二维遍历时书写不容易出错的代码。

##已知bug及原因推测
1. 子弹永远需要在同一位置打两发才可以真正摧毁一个障碍物。否则单发子弹会穿过障碍物，两者相安无事。推测原因是子弹和障碍物的碰撞判定代码的位置存在问题。原版代码中有关碰撞判定的代码都是包含在`setXXXX`函数中，而我之后加入的判定写在了move函数中。
2. 打空的子弹的重置未进行编号交换，但仍执行了bullet_ready++以及归位，这应该会造成某些子弹在地图上移动的过程中突然卡住不动（在飞机按J发射某一颗编号的子弹时）。原因很显然，原位置丢失了控制它的句柄，故只能停住。【这一点bug未经过验证，是看到代码时发现可能会出现这种情况】。
3. 【界面有关】【明显】影响视图但不影响游戏逻辑的bug：在键盘有控制飞机进行移动和射击的按键动作时，偶尔会出现屏幕上所有的字符一瞬间杂乱无章。这个现象会在下一次更新UI（通常是零点几秒后）恢复正常。而后偶尔往复。原因是，本程序多线程中每个线程的循环内斗有一个更新UI的语句。虽然程序分两个线程分开进行，但stdout只有一个，当两个线程恰巧同时运行到printPane()方法时，就会造成冲突，系统不知道应当先以哪一方的指令执行，故同时接收来自两个函数的printf信息，故会出现这种状况。
4. 【对问题3的解决方案】【想到了方法但迫于时间，没能实现】使用一个队列，每当Pane有更新时，将该更新后的状态进入队列中，然后用一个Draw()方法，以较快的频率不断获取队首状态来更新。若恰巧碰到队列为空时，则等待（因为队列为空时——虽然该情境下这种可能性极小——代表没有状态更新）；或是直接取当前Pane进行输出。

##Assignment Tucao
这个作业说是熟悉结构体和指针，然后被我做成了C语言多线程的入门……
吐槽结束。
不管怎么说，学到了很多东西。非常感谢师兄的实验题目。