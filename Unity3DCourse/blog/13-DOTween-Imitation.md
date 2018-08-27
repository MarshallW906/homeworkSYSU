**这是我最喜欢的一次作业，因为可以完全专注于代码本身**

**简述**
[DOTween](http://dotween.demigiant.com/)是Unity下面一个非常有名的插件。它高效地实现了物体的位置、大小、颜色变换等行为的封装，可以节约很多开发者的时间。它以前是NGUI的一部分，自从Unity步入5.0，引入的UGUI并未内置此功能，依然很有必要学习这个插件。

这次的作业是实现DOTween的仿写，实现几个动作，并且实现链式调用。

**原理解释：**
主要是对协程的应用；
链式调用即每个方法之后都返回this；
受lodash.js的启发，我的代码要求每次实例一个新的Tween之后，设置完参数之后，都需要显示地调用PlayNow()函数去运行之。写这个博客之前又发现，DOTween的general settings里面有设置是否自动播放的选项。**如果我要实现的话，会使用一个专用于保存default设置的类，然后每次实例化tween，都以这里的数据为基础。**

**DotwTest.cs**
这里写了一个简单的动作组合：放大→移动→缩小。
是受js的promise启发，配合lambda表达式和链式回调，写出了类似的代码。

代码统一放在我的Github上： https://github.com/MarshallW906/homeworkSYSU/tree/master/Unity3DCourse
本部分源码地址：https://github.com/MarshallW906/homeworkSYSU/tree/master/Unity3DCourse/HW10-DOTWeen-Imitation
