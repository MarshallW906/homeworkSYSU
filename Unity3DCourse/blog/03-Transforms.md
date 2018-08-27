##移动物品的方式
###Transform
Transform 组件用于描述物体在空间中的状态，它包括 位置(position)， 旋转(rotation)和 缩放(scale)。 其实所有的移动都会导致position的改变，这里所说的通过Transform组件来移动物体，指的是直接操作Transform来控制物体的位置(position)。

####Transform.Translate
该方法可以将物体从当前位置，移动到指定位置，并且可以选择参照的坐标系。 当需要进行坐标系转换时，可以考虑使用该方法以省去转换坐标系的步骤。
```cs
public function Translate(translation: Vector3, relativeTo: Space = Space.Self): void;
```
####Transform.position
直接修改`transform.position`即可

####Transform.RotateAround
绕某点，在与给定法向量垂直的面上旋转。
```cs
public void RotateAround(Vector3 point, Vector3 axis, float angle);
```

###Vector3
####Vector3.Lerp, Vector3.Slerp, Vector3.MoveTowards
Vector3 既可以表示三维空间中的一个点，也可以表示一个向量。这三个方法均为插值方法， Lerp为线性插值，Slerp为球形插值， MoveTowards在Lerp的基础上增加了限制最大速度功能。 当需要从指定A点移动到B点时,可以考虑时候这些方法。
```cs
public static Vector3 Lerp(Vector3 a, Vector3 b, float t);
public static Vector3 Slerp(Vector3 a, Vector3 b, float t);
public static Vector3 MoveTowards(Vector3 current,
Vector3 target, float maxDistanceDelta);
```
####Vector3.SmoothDamp
该方法是可以平滑的从A逐渐移动到B点，并且可以控制速度，最常见的用法是相机跟随目标。
```cs
public static Vector3 SmoothDamp(
Vector3 current,
Vector3 target,
ref Vector3 currentVelocity,
float smoothTime,
float maxSpeed = Mathf.Infinity,
float deltaTime = Time.deltaTime);
```

###Rigidbody(2d / 3d)
Rigidbody组件用于模拟物体的物理状态，比如物体受重力影响，物体被碰撞后的击飞等等。
**注意**：关于Rigidbody的调用均应放在FixedUpdate方法中，该方法会在每一次执行物理模拟前被调用。

####Rigidbody.velocity
设置刚体速度可以让物体运动并且忽略静摩擦力，这会让物体快速从静止状态进入运动状态。可以直接修改。
```cs
public Vector3 velocity;
```

#### Rigidbody.AddForce
给刚体添加一个方向的力，这种方式适合模拟物体在外力的作用下的运动状态。
```cs
public void AddForce(Vector3 force, ForceMode mode = ForceMode.Force);
```

####Rigidbody.MovePosition
刚体受到物理约束的情况下，移动到指定点。
```cs
public void MovePosition(Vector3 position);
```

###通过CharacterController组件移动物体
CharacterController用于控制第一人称或第三人称角色的运动，使用这种方式可以模拟人的一些行为，比如限制角色爬坡的最大斜度,步伐的高度等。

####CharacterController.SimpleMove
用于模拟简单运动，并且自动应用重力，返回值表示角色当前是否着地。
```cs
public bool SimpleMove(Vector3 speed);
```

####CharacterController.Move
模拟更复杂的运动,重力需要通过代码实现，返回值表示角色与周围的碰撞信息。
```cs
public CollisionFlags Move(Vector3 motion);
```
