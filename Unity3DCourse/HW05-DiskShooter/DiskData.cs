using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface OnReachEndCallback {
	void ReachEndCallback (DiskData disk);
}
public class DiskData : MonoBehaviour, OnReachEndCallback
{
	public int indexInUsed { get; set; }

	public int shotScore { get; set; }

	public int innerDiskCount { get; set; }

	private float shotSpeed;

	private int timeCount;
	private int currentTimeCount;

	private float time;
	private Vector3 pointA;
	private Vector3 pointB;
	public float g = -10f;
	private Vector3 speedv3;
	private Vector3 Gravity;
	private Vector3 currentAngle;


	public bool reachedEnd {
		get {
			return this.currentTimeCount >= timeCount;
		}
	}

	public bool isEnabled { get; set; }

	// Use this for initialization
	void Start ()
	{
		;
	}

	public void ReachEndCallback (DiskData disk) {
		Singleton<DiskFactory>.Instance.FreeDisk (disk);
	}

	public void setShapeColor (int ruler)
	{
		// set the color
		Renderer render = this.transform.GetComponent<Renderer> ();
		render.material.shader = Shader.Find ("Transparent/Diffuse");
		render.material.color = getRandomColor ();

		// set shape (scale)
		this.transform.localScale = new Vector3 (2 - 0.1f * ruler, 2 - 0.1f * ruler, 2 - 0.1f * ruler);
	}

	public void setStart (int ruler)
	{
		// set the start location
		// and the shape, color
		setShapeColor (ruler);
		timeCount = (int)(2f / Time.deltaTime);
		currentTimeCount = 0;
		this.isEnabled = true;
		this.shotScore = 10 * ruler;

		shotSpeed = 20f + 10f * ruler;

		pointA = getRandomStartPoint ();
		pointB = getRandomEndPoint ();
		time = Vector3.Distance (pointA, pointB) / shotSpeed;
		transform.position = pointA;
		speedv3 = new Vector3 ((pointB.x - pointA.x) / time,
			(pointB.y - pointA.y) / time - 0.5f * g * time, (pointB.z - pointA.z) / time);
		Gravity = Vector3.zero;
	}

	public void reset() {
		isEnabled = false;
		this.transform.position = pointA;
		speedv3 = Vector3.zero;
		Gravity = Vector3.zero;
		currentAngle = Vector3.zero;
		this.transform.eulerAngles = currentAngle;
		currentTimeCount = 0;
		dTime = 0;
	}

	private float dTime = 0;

	void FixedUpdate ()
	{	
		if (isEnabled && this.transform.position != pointB) {
			currentTimeCount++;
			Gravity.y = g * (dTime += Time.fixedDeltaTime);
			transform.position += (speedv3 + Gravity) * Time.fixedDeltaTime;
			currentAngle.x = -Mathf.Atan ((speedv3.y + Gravity.y) / speedv3.z) * Mathf.Rad2Deg;
			transform.eulerAngles = currentAngle;
		}
		if (this.reachedEnd) {
			reset ();
			ReachEndCallback (this);
		}
	}

	// start point : (-1.5~+1.5, 1.5, -10) random
	// stop point : x: -5~+5, y : -1~+5, z: 5
	public static Vector3 getRandomStartPoint ()
	{
		return new Vector3 (Random.Range (-1.5f, 1.5f), 1.5f, -12f);
	}

	public static Vector3 getRandomEndPoint ()
	{
		return new Vector3 (Random.Range (-5f, 5f), Random.Range (3f, 8f), 5f);
	}

	public static Color getRandomColor ()
	{
		float r = Random.Range (0f, 1f);  
		float g = Random.Range (0f, 1f);  
		float b = Random.Range (0f, 1f); 
		Color tcolor = new Color (r, g, b);  
		return tcolor;  
	}
}
