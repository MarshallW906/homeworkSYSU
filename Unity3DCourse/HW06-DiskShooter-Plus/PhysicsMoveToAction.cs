using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PhysicsMoveToAction : SSAction {

	public Vector3 target;
	public float speed;

	private int currentTimeCount;
	private int timeCount;

	private bool reachedEnd {
		get {
			return currentTimeCount >= timeCount;
		}
	}

	private bool reachedMid {
		get {
			return currentTimeCount >= timeCount / 2;
		}
	}

	public static PhysicsMoveToAction GetSSAction (float speed)
	{
		PhysicsMoveToAction action = ScriptableObject.CreateInstance<PhysicsMoveToAction> ();
		action.speed = speed;
		action.originPosition = SSAction.getRandomStartPoint ();
		return action;
	}

	public override void FixedUpdate ()
	{
		Rigidbody rigid = this.gameObject.GetComponent<Rigidbody> ();
		if (this.enable && !this.reachedEnd) {
			currentTimeCount++;
			if (rigid) {
				rigid.velocity = new Vector3 (Random.Range(-5f, 5f), (speed / 4) + Random.Range(-4f, 2f), speed);
			}
		}
		if (this.reachedEnd) {
			reset ();
			rigid.MovePosition (this.originPosition);
			rigid.velocity = Vector3.zero;
			this.callback.SSActionEvent (this);
		}
	}

	public void reset() {
		this.gameObject.transform.position = this.originPosition;
		currentTimeCount = 0;
	}

	public override void Start ()
	{
		this.gameObject.transform.position = this.originPosition;
		this.enable = true;

		timeCount = (int)(2f / Time.deltaTime);
		currentTimeCount = 0;
	}

}