using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MarkFactory : MonoBehaviour
{
	private List<PopUp> used;
	private List<PopUp> free;
	private int MarkCount;

	void Awake() {
		used = new List<PopUp> ();
		free = new List<PopUp> ();
		MarkCount = 0;
	}

	public GameObject placeAttackMark(Vector3 position) {
		PopUp newMark;
		if (free.Count > 0) {
			newMark = free [free.Count - 1];
			free.RemoveAt (free.Count - 1);
			newMark.setEnabled (position);
			used.Add (newMark);
		} else {
			++MarkCount;
			GameObject theMark = Instantiate (Resources.Load ("simp")) as GameObject;
			newMark = theMark.GetComponent<PopUp> ();
			newMark.innerActNumber = MarkCount;
			newMark.setEnabled (position);
			used.Add (newMark);
		}
		return newMark.gameObject;
	}

	public void Free(PopUp pop) {
		PopUp thepop = null;
		foreach (PopUp one in used) {
			if (one.innerActNumber == pop.innerActNumber) {
				thepop = one;
			}
		}
		if (thepop == null) {
			throw new System.Exception ();
		} else {
			thepop.reset ();
			free.Add (thepop);
			used.Remove (thepop);
		}
	}
}