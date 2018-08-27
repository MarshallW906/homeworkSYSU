实现一个简单的太阳系。主要是用到`transform.RotateAround()`方法，即绕某点，在与给定法向量垂直的面上旋转。
```cs
public void RotateAround(Vector3 point, Vector3 axis, float angle);
```

##思路
场景中需要1个太阳和9个行星。比较直接的方法是创建10个Sphere(1个Solar和9个行星)，但**稍微思考一下就会发现，9个行星的性质是几乎一样的，只有与太阳的距离不同，而与太阳的距离又可以轻松用分段区分**，所以在该题目（仅模拟不同物体在不同法平面上旋转）中，9个行星其实可以用Prefab统一定制。

**法平面的选取：**可以随机产生行星的坐标$(x, y, z)$，利用简单的三位向量知识即可知道，取$(m, n, p)$，使得
$$mx + ny + pz = 0$$
即可得到一个需要的法向量。过程很简单，先随机生成坐标$(x, y, z)$，再随机生成$(m, n, p)$中的两项，根据方程求出第三项即可。

则行星Object的定制思路是：**先创建一个Sphere，编写通用Rotation脚本并挂载到该Sphere上，脚本中令公转速度(speed)和离日距离段(distanceMode)为public可调，再留出旋转中心参数用于挂接Solar即可。**

##Step by Step部分
###1. 行星环绕部分
创建一个Sphere，选中之，按Cmd+Shift+D（win下对应为Ctrl）复制一个。两个分别命名为`Solar`和`Planet`。备用。

然后选中Planet，在Inspector中选`Add Component`-->`New Script`，命名为`Rotate`。添加完之后Edit。

代码如下。几个地方需要解释：
1. Header：在public变量前面一行加`[Header("Descriptive String")]`（**注意，没有分号**），可以在Inspector中显示辅助信息。如下图： ![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489407126940.png)
2. `px, py, pz`为行星的初始坐标，`rx, ry, rz`为法向量坐标。
3. 与太阳的距离：用一个`public int`控制。1位最近，9为最远。具体实现在`Start()`方法中通过`distanceMode`与预设距离段相乘即可。注意要合理设置，保证计算的合法性，**不能让Sqrt开负数平方根**（……）。小心设置好下限即可。

```cs
public class Rotate : MonoBehaviour
{

[Header ("公转中心")]
public Transform origin;
[Header ("公转速度")]
public float speed = 20;
[Header ("与太阳的距离(1-9)")]
public int distanceMode = 1;

float rx, ry, rz;
float px, py, pz;

void Start ()
{
float trueDistance = (distanceMode + 1) * 5;
px = Random.Range (distanceMode * 3, (distanceMode + 1) * 3);
py = Random.Range (distanceMode * 3, (distanceMode + 1) * 3);
pz = Mathf.Sqrt (trueDistance * trueDistance - px * px - py * py);
this.transform.position = new Vector3 (px, py, pz);
rx = Random.Range (1, 360);
ry = Random.Range (1, 360);
rz = (-(px * rx + py * ry)) / pz;
}

void Update ()
{
Vector3 axis = new Vector3 (rx, ry, rz);
this.transform.RotateAround (origin.position, axis, speed * Time.deltaTime);
}
}
```

写完之后保存回到Unity主界面。这时可以将`Planet`拖入Assets中生成Prefab了。
然后将Hierarchy中的Planet删除，并从Assets中将刚才生成的Planet的Prefab拖入Hierarchy。同样用Cmd+Shift+d复制生成9个，按9大行星依次命名即可。
再选中每个行星，在Inspector中修改`Rotate`脚本的参数。与太阳的距离由近到远设置成1-9的9个整数，速度由近到远依次降低。再把每个的Origin（公转中心）处，拖入刚才创建的Solar对象。
一番设置完之后，点击运行（记得调整摄像机的角度和位置），已经可以看到9个球体在围着中心的太阳转了。
如果想要看轨迹，则可以**在Planet的Prefab中直接添加组件**`Trail Renderer`将Time设置长一些、轨迹宽度窄一点，就可以比较清楚的看到。附简单设置。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489408066225.png)

###2. 视觉效果部分
光围着转还不行，还要有比较真实的视觉效果。
首先，把每个球体的大小调整一下，这里不再赘述。
其次，太阳是要发光的。给Solar物件添加组件`Light`，简单设置一下颜色和光照强度（见下图），即可对周围的物体发光。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489408201241.png)

**然后问题来了**。我们发现太阳确实照亮了周围的物体，但是自己却依然是黑的。Unity的自带组件中并没有找到可以实现自发光的组件，于是在Assets Store搜索了一下。搜索“Glow”（自发光），找到了一个**免费的组件**，名字为`MK Glow`。（附作者个人官网：http://michaelkremmel.de/）可以实现物体的自发光。下面说明用法。
1. 首先去Assets Store搜索下载该插件，下载完后直接Import，不再赘述。
2. 在Assets中创建一个Material，挂载到Solar上面；然后在Solar的Inspector->Shader处选择`MK -> MK Glow -> Illumin -> Diffuse`。然后展开该处的详细设置菜单，选择适合的颜色和Glow Texture等等，调整视觉效果到满意为止。
3. 在`Main Camera`中挂载脚本`MK Glow`，是MKGlow提供的组件。Import之后，直接Add Component就能找到。
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489408624310.png)
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489408822920.png)

至此，一个简易的模拟太阳系就完成了。附我的效果截图：
![Alt text](http://marshallw.me/wp-content/uploads/2017/04/1489408987875.png)
可以看到，Scene中和实际视觉效果（Game窗口中）有明显的差别，应当是渲染的问题。而且最内圈的公转，看到轨迹不时会出现直线，应该是Speed设置太高（导致跳帧）所致，调低后这种情况消失。

源码地址：
https://github.com/MarshallW906/homeworkSYSU/tree/master/Unity3DCourse/HW03-Solar
