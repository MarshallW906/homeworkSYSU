using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

	public float speed = 3.0f;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		float translationZ = Input.GetAxis("Vertical");
		float translationX = Input.GetAxis("Horizontal");
		Vector3 tmp = new Vector3(translationX, 0, translationZ);

		transform.Translate(tmp.normalized * speed);
	}
}
