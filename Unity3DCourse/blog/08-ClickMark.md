实现点击效果。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1490654667212.png)

用 Plane 或其他物体做地面， tag 为“Finish”
点击地面后，出现一个圆形攻击标记，两秒后自动消失。注意：该攻击标记不能挡住点击。（Primitive Objects / Cylinder）
请使用一个简单工厂创建、管理这些的标记，并自动收回这些标记（注意，这些对象创建后，放在列表内，不必释放）。

并没有使用CreatePrimitive，而是直接做了Prefab放在里面。
用了3个类。`planeClick.cs`, `PopUp.cs`, `MarkFactory.cs`。PopUp是圆形标记的元动作类，planeClick用来检测对plane的点击，Markfactory用来做动作对象（PopUp和对应的Cylinder）的管理。

使用简单的工厂模式即可。需要注意的是，需要在Cylinder预制中，把其Layer改为`Ignore Raycast`，然后就可以不挡住点击。

附源码地址：
https://github.com/MarshallW906/homeworkSYSU/tree/master/Unity3DCourse/HW05-ClickMark
