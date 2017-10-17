using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gameController : MonoBehaviour
{

	enum State
	{
		NONE,
		CIRCLE,
		CROSS
	}

	State[,] paneState = new State[3, 3];

	int turnsDone = 1;

	// Use this for initialization
	void Start ()
	{
		Debug.Log ("Started.");
		reset ();
	}

	void OnGUI ()
	{
		// Debug.Log ("OnGUI");
		if (GUI.Button (new Rect (150, 300, 100, 50), "Reset"))
			reset ();  
		State tmpState = check ();

		switch (tmpState) {
		case State.CIRCLE:
			Debug.Log ("Circle Win");
			GUI.Label (new Rect (180, 250, 100, 50), "O wins!");
			drawButtons ();
			break;
		case State.CROSS:
			Debug.Log ("Cross Win");
			GUI.Label (new Rect (180, 250, 100, 50), "X wins!");
			drawButtons ();
			break;
		case State.NONE:
			// Debug.Log ("not win yet");
			if (turnsDone >= 10) {
				drawButtons ();
				GUI.Label (new Rect (180, 250, 100, 50), "Draw:)");
			} else {
				// Debug.Log ("drawing");
				updateGUIButtons (tmpState);
			}
			break;
		}
	}

	void drawButtons ()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				if (paneState [i, j] == State.CIRCLE) {
					GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "O");  
					Debug.Log ("draw O");
				}
				if (paneState [i, j] == State.CROSS) {
					GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "X"); 
					Debug.Log ("draw X");
				}
				if (paneState [i, j] == State.NONE) {
					GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), ""); 
					Debug.Log ("draw NONE");
				}
			}
	}

	void updateGUIButtons (State tmpState)
	{
		for (int i = 0; i < 3; i++) {  
			for (int j = 0; j < 3; j++) {  
				if (paneState [i, j] == State.CIRCLE) {
					GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "O");  
					Debug.Log ("draw O");
				}
				if (paneState [i, j] == State.CROSS) {
					GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "X"); 
					Debug.Log ("draw X");
				}
				if (GUI.Button (new Rect (i * 50 + 130, j * 50 + 80, 50, 50), "")) {  
					if (tmpState == State.NONE) {  
						if (turnsDone % 2 == 1)
							paneState [i, j] = State.CIRCLE;
						else
							paneState [i, j] = State.CROSS;
						++turnsDone;  
					}  
				}  
			}  
		}
	}

	void reset ()
	{
		Debug.Log ("Reset.");
		turnsDone = 1;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				paneState [i, j] = State.NONE;
		
	}

	State check ()
	{
		// Debug.Log ("Check.");
		// first check rows and cols
		for (int i = 0; i < 3; i++) {
			if (paneState [i, 0] != State.NONE && paneState [i, 0] == paneState [i, 1] && paneState [i, 0] == paneState [i, 2])
				return paneState [i, 0];
			if (paneState [0, i] != State.NONE && paneState [0, i] == paneState [1, i] && paneState [0, i] == paneState [2, i])
				return paneState [0, i];
		}

		// then check the diagonal line
		if (paneState [0, 0] != State.NONE && paneState [0, 0] == paneState [1, 1] && paneState [0, 0] == paneState [2, 2])
			return paneState [1, 1];
		if (paneState [0, 2] != State.NONE && paneState [0, 2] == paneState [1, 1] && paneState [0, 2] == paneState [2, 0])
			return paneState [1, 1];
		// if none
		return State.NONE;
	}
}
