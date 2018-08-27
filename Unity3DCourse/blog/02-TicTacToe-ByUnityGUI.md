这次课是用GUI实现简单的井字棋游戏，规则不必多说。
先说感想吧，用GUI做蛮怪的，主要是并不能发挥设计器所见即所得的优势，不过拿来熟悉借口还是很不错。
贴一个对Unity自带GUI的介绍：http://blog.csdn.net/kuloveyouwei/article/details/23598171

**下面是Step by Step部分**
因为游戏所有内容实际都是按钮，且都要用GUI实现，所以直接写代码即可。
按Cmd+Shift+N（Windows下好像是Ctrl+Shift+N，有错请指正）创建一个空的GameObject，命名为`_Controller`。选中它，并在Inspector中点`Add Component`，选`New Script`，给脚本命名（这里为gameController），因为是C#所以language里选C sharp。然后开始写代码。

井字棋棋盘，每个格子有3种状态：O、X、空白（未填）。用一个枚举类型保存（良好的习惯：可读性）。并且令**空白状态为0**，方便做条件判断。还需要一个int记录行动次数。每次游戏开始时需要重置所有状态，则reset方法的内容很显然。
```cs
int turnsDone = 1;
enum State {
NONE,
CIRCLE,
CROSS
}
void Start () {
Debug.Log ("Started.");
reset ();
}
void reset () {
Debug.Log ("Reset.");
turnsDone = 1;
for (int i = 0; i < 3; i++)
for (int j = 0; j < 3; j++)
paneState [i, j] = State.NONE;

}
```

一开始不了解的话，很容易想到在Start()方法里实例几个Button，然后在OnGUI()中通过类似OnClick的事件进行直接的逻辑处理，然而实际上**这样几乎不可能做到**，因为OnGUI的实现方式是不断刷屏，绘制下一帧时，之前的所有对象都会被删除，所以难以将状态绑定到特定的对象上（这也是我们通常的思路），所以需要一个二维数组记录圈叉状态，每一帧时根据状态直接绘制。
```cs
State[,] paneState = new State[3, 3];
void drawButtons () {
for (int i = 0; i < 3; i++)
for (int j = 0; j < 3; j++) {
if (paneState [i, j] == State.CIRCLE) {
GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "O");
Debug.Log ("draw O");
}
if (paneState [i, j] == State.CROSS) {
GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "X");
Debug.Log ("draw X");
}
if (paneState [i, j] == State.NONE) {
GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "");
Debug.Log ("draw NONE");
}
}
}
```

**check()方法**：判断是否胜利。这里**只判断是否胜利，将平局放到外部判断(未出现胜利&&次数已满9次)**。每行、每列、2个对角线，不必多言。
```cs
State check () {
// Debug.Log ("Check.");
// first check rows and cols
for (int i = 0; i < 3; i++) { if (paneState [i, 0] != State.NONE && paneState [i, 0] == paneState [i, 1] && paneState [i, 0] == paneState [i, 2]) return paneState [i, 0]; if (paneState [0, i] != State.NONE && paneState [0, i] == paneState [1, i] && paneState [0, i] == paneState [2, i]) return paneState [0, i]; } // then check the diagonal line if (paneState [0, 0] != State.NONE && paneState [0, 0] == paneState [1, 1] && paneState [0, 0] == paneState [2, 2]) return paneState [1, 1]; if (paneState [0, 2] != State.NONE && paneState [0, 2] == paneState [1, 1] && paneState [0, 2] == paneState [2, 0]) return paneState [1, 1]; // if none return State.NONE; } ``` **然后是OnGUI方法**： 几条关键逻辑： 如果点击Reset则重新开始、点击空白按钮则画上圈或叉、判断胜利条件是否达成、（若否）判断是否达成平局。 **这里注意**，C#的switch语句，每个case之后必须有一个break作结尾，否则会编译报错。这点与C、C++有所不同。 这里出现了另一个函数`updateGUIButtons(State tmpState)`，是为了使代码清晰。与`drawButtons()`有少量重复，主要是为了区分棋盘状态改变与不变时的两种策略。 ```cs void OnGUI () { // Debug.Log ("OnGUI"); if (GUI.Button (new Rect (150, 300, 100, 50), "Reset")) reset (); State tmpState = check (); switch (tmpState) { case State.CIRCLE: Debug.Log ("Circle Win"); GUI.Label (new Rect (180, 250, 100, 50), "O wins!"); drawButtons (); break; case State.CROSS: Debug.Log ("Cross Win"); GUI.Label (new Rect (180, 250, 100, 50), "X wins!"); drawButtons (); break; case State.NONE: // Debug.Log ("not win yet"); if (turnsDone >= 10) {
drawButtons ();
GUI.Label (new Rect (180, 250, 100, 50), "Draw:)");
} else {
// Debug.Log ("drawing");
updateGUIButtons (tmpState);
}
break;
}
}

void updateGUIButtons (State tmpState) {
for (int i = 0; i < 3; i++) {
for (int j = 0; j < 3; j++) {
if (paneState [i, j] == State.CIRCLE) {
GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "O");
Debug.Log ("draw O");
}
if (paneState [i, j] == State.CROSS) {
GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "X");
Debug.Log ("draw X");
}
if (GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "")) {
if (tmpState == State.NONE) {
if (turnsDone % 2 == 1)
paneState [i, j] = State.CIRCLE;
else
paneState [i, j] = State.CROSS;
++turnsDone;
}
}
}
}
}
```

**至此，所有工作已经完成，保存脚本回到Unity主界面，运行即可。**

###感想###
发现大家普遍提倡使用Unity的第三方库NGUI来代替GUI。这类第三方库已经为我们造好了许多轮子，实际生产环境中显然更有效率。

源码地址：
https://github.com/MarshallW906/homeworkSYSU/tree/master/Unity3DCourse/HW02-TicTacToe
