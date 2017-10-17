using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FirstSceneController : MonoBehaviour
{
	public int score;
	public Vector3 wind;

	public void addScore (int tscore)
	{
		score += tscore;
		wind = new Vector3 (Random.Range (-150f, 150f), Random.Range (-100f, 100f), Random.Range (-100f, 100f));
	}

	public void Reset ()
	{
		score = 0;
		wind = Vector3.zero;
	}

	void Awake ()
	{
		Reset ();
	}

	void Update() {
		if (Input.GetKeyDown (KeyCode.Space)) {
			wind = new Vector3 (Random.Range (-150f, 150f), Random.Range (-100f, 100f), Random.Range (-100f, 100f));
		}
	}

	void OnGUI ()
	{
		// score, start, restart, wind notification
		GUI.TextArea (new Rect (20, 20, 100, 30), "score : " + score.ToString ());
		GUI.TextArea (new Rect (20, 50, 180, 30), "wind :" + wind.ToString ());
		GUI.TextArea (new Rect (120, 20, 200, 30), "Press Space to Change Wind");
			
	}
}
