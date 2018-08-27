PS：因为各种原因，做这部分作业比较赶，所以采用了最容易组织代码的GUI来做点击事件的处理。

先放网上做好的游戏地址。这次是实现这个游戏的逻辑，美工部分暂时没有考虑。
http://www.flash-game.net/game/2535/priests-and-devils.html

##思路演变
刚看到作业的时候，第一反应是用**Fungus**之类的插件，直接在Object上挂载各种事件，便可很轻松的实现逻辑(甚至不需要直接写代码)。后来想到作业的本意是熟悉C#和Unity的API，直接上插件与本意相悖。

后来想用GameObject做点击事件的按钮来替代GUI.Button（添加**Collider**，重写`MonoBehaviour.OnMouseDown()`方法），但是想到作业要求**必须使用MVC架构**，而将每个Object在Controller中注册，或采用`Instantiate()`方法保存对象指针，都不如直接用`GUI.Button()`写起来更快，考虑到时间问题，还是直接上了GUI。

##思考过程
先思考游戏的关键的基本元素。
需要的对象：3个牧师、3个魔鬼、1个船、2个岸边。可以用不同形状、颜色的Object表示，实际运行时，从Prefab中Load即可。

游戏的架构：下图为课件中提供的标准的游戏MVC架构，因为这个游戏较为简单，可以考虑简化之。简化过后的架构图也放出。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489413882750.png)
图为简化之后的架构图。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489415659347.png)
`IUserInterface`用来创建GUI对象接受玩家动作，处理GUI事件，使用`IUserActions` 接口控制；
`DNPGameSceneController` 是单实例对象，用来处理对象间通信和实现`IUserActions`接口；
`gameBase`用来保存游戏名称和游戏简介，它注册在`DNPGameSceneController` 中。
`GenGameObject`用来创建游戏对象和处理对象运动，它也注册在`DNPGameSceneController` 中。`IUserActions` 接口通过与`GenGameObject` 互动完成游戏逻辑。

##Step by Step
新建3D项目。在Assets下面建立`Scripts` `Resources/Prefabs` `Glow_Materials`三个文件夹，备用。第三个文件夹是存放自发光Material用的。因为喜欢最近发现的`MK Glow`插件，觉得令对象自发光的视觉效果很炫丽，而且使用简单。
所以下一步是从Assets Store中导入插件`MK Glow`，不多赘述。
然后在Hierarchy中创建空对象（Cmd+Shift+N），命名`_gameController`，用于挂载各种脚本。
在`Scripts/`下建立脚本`gameBase.cs`，挂载到刚才的`_gameController`上。然后编辑。我们将`gameBase`类和`DNPGameSceneController`单例类都写在这个文件中。需要注意的是，`DNPGameSceneController`需要创建一个新的namespace，然后在这个namespace中写。这样的话，在其他脚本中，只要加上 using就可以直接在其他类中获取到单例类的实例。因为单例类与整个游戏所有部件相关，故完整代码在文末给出。此处给出的是有关gameBase的注册，以及单例类的经典实现。

**然后新建脚本**`Scripts/GenGameObject.cs` `Scripts/IUserInterface.cs`，都挂载到`_gameController`上。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489419059258.png)

假设牧师为球体、魔鬼为正方体、河岸为长方体、船也为长方体。分别创建对应的3D Object，调整大小形状之后，拖到Assets中使之成为Prefab。
**注意：**这里要使刚才生成的Prefab保存在`Resources/Prefabs`目录下。如果生成的时候未放在此处，直接用鼠标拖进去即可。
然后设置主摄像机为**正交投影**(Orthographic)，并调整好位置、角度、Size（视野范围），这样看到的所有物体就都是平面了。

接下来是写`GenGameObject.cs`的代码。这个类主要负责创建游戏对象和处理对象运动，**于是把各个Object的状态都存在此处。**先思考游戏的几个基本行为。如下图：
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489419464593.png)
简单来说，就是上船、下船。因为牧师和牧师、魔鬼和魔鬼彼此之间可以看作完全相同，最合适的方法是直接用Stack栈来做两岸状态的存取。Boat中用长度为2的数组记录状态即可。
**由于Instantiate返回的指针并不能直接区分牧师和魔鬼，所以Boat的中二者的区分需要用额外的方法解决。**好在，Unity为GameObject提供了Tag属性。(`string Object.tag`)。
回到Unity设计界面中，找到牧师和魔鬼的Prefab，设置其Tag。这里自行添加了2个Tag用于区分。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489419865422.png)
然后就可以在代码中直接用`boat[0].tag`判断其类型。

考虑到6个人物的位置需要实时根据栈的状态而变化，所以写了一个设置位置的函数（注意`Stack.toArray`方法很好用），可以用在`Update()`中。

然后需要在`GenGameObject`中，对应7中基本游戏行为，写出7种行为动作的对应函数。即各种方式的Move。然后需要一个`check()`函数，每次动作后进行状态检查，判断Win/Lose。

**然后是**`IUserInterface`脚本。即创建GUI对象，设置对应的事件。主要包括几个基本操作的触发，游戏简介的显示，和游戏结束（胜／负）时的显示。
这里使用了interface。使`DNPGameSceneController`实现该接口，然后在`IUserInterface`中通过对这个接口的调用实现对用户交互的实现。与View的分离也很清晰。

到此游戏基本完成。

源码地址：
https://github.com/MarshallW906/homeworkSYSU/tree/master/Unity3DCourse/HW03-DevilNPastor
