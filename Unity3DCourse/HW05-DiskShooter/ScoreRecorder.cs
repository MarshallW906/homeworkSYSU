using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreRecorder : MonoBehaviour
{

	public int score;

	public void Record (DiskData disk)
	{
		score += disk.shotScore;
	}

	public void Reset ()
	{
		score = 0;
	}

	void Awake ()
	{
		Reset ();
	}

	void OnGUI ()
	{
		GUI.TextArea (new Rect (20, 20, 100, 30), "score : " + score.ToString ());
	}
}
