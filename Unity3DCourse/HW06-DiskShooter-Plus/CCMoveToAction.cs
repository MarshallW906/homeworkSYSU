using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CCMoveToAction : SSAction
{
	public Vector3 target;
	public float speed;

	private int timeCount;
	private int currentTimeCount;

	private float shotSpeed;
	private float time;
	private Vector3 pointA;
	private Vector3 pointB;
	private float g = -10f;
	private Vector3 speedv3;
	private Vector3 Gravity;
	private Vector3 currentAngle;
	private float dTime = 0;

	public bool reachedEnd {
		get {
			return this.currentTimeCount >= timeCount;
		}
	}

	public override void Start ()
	{
		timeCount = (int)(2f / Time.deltaTime);
		currentTimeCount = 0;
		this.enable = true;

		pointA = getRandomStartPoint ();
		pointB = getRandomEndPoint ();
		time = Vector3.Distance (pointA, pointB) / shotSpeed;
		this.gameObject.transform.position = pointA;
		speedv3 = new Vector3 ((pointB.x - pointA.x) / time,
			(pointB.y - pointA.y) / time - 0.5f * g * time, (pointB.z - pointA.z) / time);
		Gravity = Vector3.zero;
	}

	public static CCMoveToAction GetSSAction (float speed)
	{
		CCMoveToAction action = ScriptableObject.CreateInstance<CCMoveToAction> ();
		action.speed = action.shotSpeed = speed;
		return action;
	}

	public override void Update ()
	{
		if (this.enable && this.currentTimeCount < this.timeCount && this.gameObject.transform.position != pointB) {
			currentTimeCount++;
			Gravity.y = g * (dTime += Time.fixedDeltaTime);
			this.gameObject.transform.position += (speedv3 + Gravity) * Time.fixedDeltaTime;
			currentAngle.x = -Mathf.Atan ((speedv3.y + Gravity.y) / speedv3.z) * Mathf.Rad2Deg;
			this.gameObject.transform.eulerAngles = currentAngle;
		}
		if (this.reachedEnd) {
			reset ();
			this.callback.SSActionEvent (this);
		}
	}

	public void reset() {
		this.enable = false;
		this.gameObject.transform.position = pointA;
		speedv3 = Vector3.zero;
		Gravity = Vector3.zero;
		currentAngle = Vector3.zero;
		this.gameObject.transform.eulerAngles = currentAngle;
		currentTimeCount = 0;
		dTime = 0;
	}

}
