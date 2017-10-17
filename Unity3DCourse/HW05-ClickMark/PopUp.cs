using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PopUp : MonoBehaviour
{

	private int totalTimeCount;
	private int currentTimeCount;

	public int innerActNumber { get; set; }

	public bool isEnabled { get; set; }

	public bool isEnd {
		get { return currentTimeCount == totalTimeCount && currentTimeCount > 0; }
	}

	private Vector3 origin = new Vector3 (0, 0, -10);
	private Vector3 target;

	// Use this for initialization
	void Start () {
		totalTimeCount = (int)(4f / Time.deltaTime);
	}

	public void reset ()
	{
		this.transform.position = origin;
		currentTimeCount = 0;
		isEnabled = false;
	}

	public void setEnabled (Vector3 theTarget)
	{
		isEnabled = true;
		this.target = theTarget;
		this.transform.position = target;
	}

	void OnCompeletedCallback (PopUp pop)
	{
		Singleton<MarkFactory>.Instance.Free (pop);
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (this.isEnabled && currentTimeCount < totalTimeCount) {
			currentTimeCount++;
			this.transform.position = this.target;
		}
		if (this.isEnd) {
			print ("is end");
			reset ();
			OnCompeletedCallback (this);
		}
	}

}
