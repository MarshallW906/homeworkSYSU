using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArrowFactory : MonoBehaviour
{
	public Camera cam;

	public GameObject arrowPrefab;
	private List<ArrowData> used;
	private List<ArrowData> free;
	private int ArrowCount;

	public int usedCount {
		get { return used.Count; }
	}

	void Awake ()
	{
		used = new List<ArrowData> ();
		free = new List<ArrowData> ();
		ArrowCount = 0;
	}

	// Use this for initialization
	void Start ()
	{
		ArrowCount = 0;
		used.Clear ();
		free.Clear ();
	}

	void Update ()
	{
		if (Input.GetButtonDown ("Fire1")) {
			Ray mouseRay= cam.ScreenPointToRay (Input.mousePosition);
			ArrowData tArrow = this.getArrow ();
			tArrow.setShapeColor ();
//			tArrow.isEnable = true;
			tArrow.EnableAndShoot (mouseRay.direction);
		}
	}

	public ArrowData getArrow ()
	{
		ArrowData theArrow;
		if (free.Count > 0) {
			Debug.Log ("re-use from free");
			theArrow = free.ToArray () [free.Count - 1];
			free.RemoveAt (free.Count - 1);
			used.Add (theArrow);
		} else {
			Debug.Log (" generate new ");
			ArrowCount++;
			GameObject newArrow = Instantiate (arrowPrefab) as GameObject;
			newArrow.name = "Arrow" + ArrowCount.ToString ();
			theArrow = newArrow.GetComponent<ArrowData> ();
			theArrow.innerArrowCount = ArrowCount;
			used.Add (theArrow);
		}
		theArrow.indexInUsed = used.Count - 1;
		return theArrow;
	}

	public void FreeArrow (int diskNo)
	{	
		ArrowData theDisk = used.ToArray () [diskNo];
		if (theDisk == null) {
			throw new System.Exception ();
		} else {
			free.Add (theDisk);
			used.Remove (theDisk);
		}
	}

	public void FreeArrow (ArrowData arrow)
	{
		arrow.isEnable = false;
		ArrowData theArrow = null;
		foreach (ArrowData oneArrow in used) {
			if (oneArrow.indexInUsed == arrow.indexInUsed) {
				theArrow = oneArrow;
			}
		}
		if (theArrow == null) {
			throw new System.Exception ();
		} else {
			theArrow.reset ();
			free.Add (theArrow);
			used.Remove (theArrow);
		}
	}

	public void FreeAllArrows ()
	{
		for (int i = used.Count - 1; i >= 0; i--) {
			ArrowData arrow = used [i];
			free.Add (arrow);
			used.Remove (arrow);
		}
	}
}

public class Singleton<T> : MonoBehaviour where T : MonoBehaviour
{
	protected static T instance;

	public static T Instance {
		get {
			if (instance == null) {
				instance = (T)FindObjectOfType (typeof(T));
				if (instance == null) {
					Debug.LogError ("An instance of " + typeof(T) + " is needed in the scene, but there is none.");
				}
			}
			return instance;
		}
	}
}