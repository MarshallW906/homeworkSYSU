using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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
