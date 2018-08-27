选了学校的3d游戏开发课程，跟着课程作业更新一下博客。
下面是一些基础概念的解释。
包括：对象、资源、MonoBehaviour基本行为等
**解释对象与资源的区别于联系，根据官方案例，分别总结资源和对象组织的规则/规律。**
对象：即GameObject
资源：在Assets中
对象即直接存在于Hierarchy中放置，直接出现在游戏场景中。
对象由资源整合（组合）而成，资源可以被多个对象使用（可复用）。有些资源作为模版，可以实例化成游戏中具体的对象（Prefab：预置）。
资源文件夹通常有对象（GameObject）、材质（Material）、场景（Scene）、声音、预设（Prefab）、贴图、脚本（Scripts）、动作；
对象从不同的角度划分一般有玩家、敌人、环境、摄像机、音乐等虚拟父类。这些父节点本身没有实体（起整合子类的作用），但他们的子类真正包含了游戏中会出现的对象。

**编写简单程序代码，逐一验证 MonoBehaviour 基本行为触发的条件。**
```cs
public classNewBehaviourScript : MonoBehaviour {
void Awake() {
print("onAwake!");
}
void Start() {
print("onStart!");
}
void Update() {
print("onUpdate!");
}
void OnGUI() {
print("onGUI!");
}
void FixedUpdate() {
print("onFixedUpdate!");
}
void LateUpdate() {
print("onLateUpdate!");
}
void Reset() {
print("onReset!");
}
void OnDisable() {
print("onDisable!");
}
void OnDestroy() {
print("onDestroy!");
}
}
```

**通过官方参考手册，查找 GameObject，Transform，Component 对象，简单解释三者之间的关系。（使用UMLet 画教程上图）**
GameObject包含Component，Transform属于Component的一种。GameObject必定包含一个Transform组件，也可能包含其它Component。
![关系图](http://marshallw.me/wp-content/uploads/2017/03/new.png)
Component 强组合于 GameObject，使得内存空间管理富有效率，提高了性能

**整理官方和其他学习材料，介绍如何用程序（代码）管理一个场景的游戏对象树林。编写简单代码验证以下技术的实现：**
**查找对象:**
通过名字查找：`public static GameObject Find(string name)`
通过标签查找单个对象：`public static GameObject FindWithTag(string tag)`
通过标签查找多个对象：`public static GameObject[] FindGameObjectsWithTag(string tag)`

添加子对象
```cs
public static GameObect CreatePrimitive(PrimitiveTypetype)
```
遍历对象树
```cs
foreach (Transform child in transform) {
Debug.Log(child.gameObject.name);
}
```
清除所有子对象
```cs
foreach (Transform child in transform) {
Destroy(child.gameObject);
}
```

**预设有什么好处？与对象克隆 (clone or copy or Instantiate of Unity Object) 关系？**
预设类似于一个模板，通过预设可以创建相同属性的对象，这些对象和预设关联。一旦预设发生改变，所有通过预设实例化的对象都会产生相应的变化（适合批量处理）；
对象克隆不受克隆本体的影响，因此A对象克隆的对象B不会因为A的改变而相应改变。

**解释组合模式。并编写验证程序，向组合对象中子对象 cast 消息， 验证组合模式的优点。**
组合模式允许用户将对象组合成树形结构来表现”部分-整体“的层次结构，使得客户以一致的方式处理单个对象以及对象的组合。组合模式实现的最关键的地方是——简单对象和复合对象必须实现相同的接口。这就是组合模式能够将组合对象和简单对象进行一致处理的原因。
**子类对象（child_obj）方法：**
```cs
void sayHello() {
print("Hello!");
}
```
**父类对象（GameObject）方法：**
```cs
void Start () {
this.BroadcastMessage("sayHello");
}
```
结构：
![类层次结构](http://marshallw.me/wp-content/uploads/2017/03/new2.png)
结果为
```
Hello!
Hello!
```
附官方文档中对BroadcastMessage的示例：
```cs
using UnityEngine;
using System.Collections;

public class ExampleClass : MonoBehaviour {
void ApplyDamage(float damage) {
print(damage);
}
void Example() {
BroadcastMessage("ApplyDamage", 5.0F);
}
}
```
