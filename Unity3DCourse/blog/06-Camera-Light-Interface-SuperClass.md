#3d游戏开发 HW4

##摄像机
**左手法则**
Unity3D采用的是左手坐标系：沿屏幕横向为x轴，沿屏幕纵向为y轴，垂直屏幕方向为z轴。右、上、背向观众的三个方向为正方向。
左手法则的应用：左手先四指并到一起，指向**x轴正方向**，然后左手自然握拳，手指弯至90度时指向的是**Y轴正方向**，此时拇指指向的即为Z轴正方向。
**Field of View(FOV)**
视野范围。只针对透视镜头（perspective），用于控制视角宽度与纵向角度。
调节FOV可发现，FOV**越大**的时候，视角**越大**，物体看起来**越小**。FOV**越小**，视角**越小**，物体看起来**越大**。

**添加一个 Empty 游戏对象， 添加一个 Camera 部件（Rendering 分类下），有什么效果**
这个对象变成了一个Camera，拥有其自己的view。

**坐标体系**
**屏幕空间点**用像素定义，屏幕的左下为(0,0);右上是（PixelWidth，pixelHeight）.Z的位置是以世界单位衡量的到相机的距离。
**视口空间点**是归一化的并相对于相机的。相机的左下为（0,0）；右上是（1,1）；Z的位置是以世界为单位衡量的到相机的距离。
**世界空间点**是以全局坐标定义的（例如：`Transform.position`）

**Camera继承树：UML图**
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489929184706.png)

**静态属性+程序验证**
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489929266921.png)
1.测试`allCameras` `main` `current`，新建2个摄像机，并新建脚本。脚本挂载在3个摄像机中的任意，这里选择了Cube内的Camera。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489930096547.png)

```cs
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class testStaticVar : MonoBehaviour {

int count;

// Use this for initialization
void Start () {
count = Camera.allCameras.Length;
CameraCount ();
print ("Camera.current : ");
print (Camera.current);
print ("Camera.main : ");
print (Camera.main);
}

void CameraCount() {
print("We've got " + count + " cameras");
print(count == Camera.allCamerasCount);
}
}
```
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489930009931.png)

2.测试`OnPostRender`
```cs
// callback to be called after any camera finishes rendering
public void MyPostRender(Camera cam)
{
Debug.Log("PostRender " + gameObject.name + " from camera " + cam.gameObject.name);
}
public void OnEnable()
{
Debug.Log ("On enable");
// register the callback when enabling object
Camera.onPostRender += MyPostRender;
}
public void OnDisable()
{
Debug.Log ("On disable");
// remove the callback when disabling object
Camera.onPostRender -= MyPostRender;
}
```
onEnable和onDisable：play之后在Inspector中选中/取消选中最上方的checkbox即可。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489930365637.png)
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489930399806.png)
3.测试`OnPreCull`
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489930796870.png)
4.测试`OnPreRender`
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489930854859.png)

**切换摄像机**
新建了一个Cube对象，并在主Camera之外新建了一个Camera，调整其为俯瞰图。在Cube对象上新建脚本，内容如下。点击play后显示的是新Camera的视图，点击按钮之后变为主视图。
```cs
// 遍历所有摄像机对象，关闭非主摄像机外的摄像机
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class chgCam : MonoBehaviour {
void OnGUI() {
if (GUI.Button (new Rect (20, 20, 20, 20), "chgCam")) {
foreach(Camera c in Camera.allCameras) {
if (c.name != "Main Camera") {
print (c.name);
c.enabled = false;
}
}
}
}
}
```
点击前：
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489931414804.png)
点击后：
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489931390581.png)

##光源
光源不是GameObject。光源可以照亮别人但是自己不会发光。

###类型
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489931548825.png)

给Camera加一个Spot光源。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489932092868.png)
给太阳添加点光源之后，自己并不会发光。在周围放上物体可以照亮周围的物体。这个问题在之前的作业提到过。物体的自发光可以通过shader实现。AssetsStore里有很多Glow插件。

###不是游戏对象的好处
Light在unity中并没有被设计成GameObject，而是作为一个Component，这样子Light就能被添加到游戏对象上。既可以固定位置，也可以跟随着物体一起移动。更加便于实现一些需求。Camera同理。

##面向对象语言接口和超类
###接口
接口：让规范和实现相分离；接口只是一个规范，不再是一个有具体功能的类
###超类
通过继承创建的新类称为“子类”或“派生类”。
被继承的类称为“基类”、“父类”或“超类”。
**相同点**
超类和接口都是抽象了具体事件，提取了共同信息，把他们集合起来，隐藏了具体的实现过程。提供了一种可以使用的方法。
**不同点**
接口完成方法的定义，**不实现具体的内容**，只要接受到参数完成所需要的工作，完成对对象的创建即可。
超类**要完成**对方法的**定义和实现**。

**(问题解答)**
1.ISSActionCallback 能设计为超类吗？为什么？ 画 UML 图说明
2.SSAction, SSActionManager 能设计为接口吗？为什么？画 UML 图说明
都不能。ISSActionCallback 需要在不同类中有不同作用；SSAction, SSActionManager需要本身可以实例化并直接使用。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489949207515.png)

###使用 Fantasy Skybox FREE 构建自己的游戏场景
贴一个“测试样例”（……
![Alt text](./1489950426258.png)
1.天空盒子。给主摄像机添加一个skybox组件，然后新建一个Material，shader选skybox->6 sided，拖入6张图片完成，最后把material拖到skybox组件上。
2.Terrain
造山、高度、平缓工具：选择好形状、大小等参数之后在Terrain上按住鼠标左键拖动即可。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489950611172.png)
地面纹理、种草、种树同理。不过要先选好纹理/草/树的样式。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489950683522.png)
