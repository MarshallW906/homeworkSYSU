using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DnP.gameController;

public class IUserInterface : MonoBehaviour
{

	DNPGameSceneController theGame;
	IUserActions action;

	float width, height;

	float castw (float scale)
	{
		return (Screen.width - width) / scale;
	}

	float casth (float scale)
	{
		return (Screen.height - height) / scale;
	}

	// Use this for initialization
	void Start ()
	{
		theGame = DNPGameSceneController.GetInstance ();
		action = theGame as IUserActions;
	}

	void OnGUI ()
	{
		width = Screen.width / 12;
		height = Screen.height / 12;
		print (theGame.state);
		if (theGame.state == State.WIN) {
			if (GUI.Button (new Rect (castw (2f), casth (6f), width, height), "Win!")) {
				action.restart ();
			}
		} else if (theGame.state == State.LOSE) {
			if (GUI.Button (new Rect (castw (2f), casth (6f), width, height), "Lose!")) {
				action.restart ();
			}
		} else {
			if (GUI.RepeatButton (new Rect (10, 10, 120, 20), theGame.GetBaseGame ().gameName)) {
				GUI.TextArea (new Rect (10, 40, Screen.width - 20, Screen.height / 2), theGame.GetBaseGame ().gameRule);
			} else if (theGame.state == State.BoatSTART || theGame.state == State.BoatEND) {
				if (GUI.Button (new Rect (castw (2f), casth (6f), width, height), "Go")) {
					Debug.Log ("moveboat");
					action.moveBoat ();
				}
				if (GUI.Button (new Rect (castw (10.5f), casth (4f), width, height), "On")) {
					Debug.Log ("devilSonB");
					action.devilSOnB ();
				}
				if (GUI.Button (new Rect (castw (4.3f), casth (4f), width, height), "On")) {
					Debug.Log ("priestSonB");
					action.priestSOnB ();
				}
				if (GUI.Button (new Rect (castw (1.1f), casth (4f), width, height), "On")) {
					Debug.Log ("devilEonB");
					action.devilEOnB ();
				}
				if (GUI.Button (new Rect (castw (1.3f), casth (4f), width, height), "On")) {
					Debug.Log ("priestEonB");
					action.priestEOnB ();
				}
				if (GUI.Button (new Rect (castw (2.5f), casth (1.3f), width, height), "Off")) {
					Debug.Log ("offBoatL");
					action.offBoatL ();
				}
				if (GUI.Button (new Rect (castw (1.7f), casth (1.3f), width, height), "Off")) {
					Debug.Log ("offBoatR");
					action.offBoatR ();
				}
			}
		}
	}
}
