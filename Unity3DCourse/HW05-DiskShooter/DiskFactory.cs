using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DiskFactory : MonoBehaviour
{
	public Camera cam;

	public GameObject diskPrefab;
	private List<DiskData> used;
	private List<DiskData> free;
	private int DiskCount;

	public int usedCount {
		get { return used.Count; }
	}

	void Awake ()
	{
		used = new List<DiskData> ();
		free = new List<DiskData> ();
		DiskCount = 0;
	}

	// Use this for initialization
	void Start ()
	{
		DiskCount = 0;
		used.Clear ();
		free.Clear ();
	}

	void FixedUpdate ()
	{
		if (Input.GetButtonDown ("Fire1")) {
			// if clicked on it, Free it
			Debug.Log ("Fire1 Pressed");
//			Debug.Log (Input.mousePosition);
			Vector3 mp = Input.mousePosition;
			Camera ca = cam.GetComponent<Camera> ();
			Ray ray = ca.ScreenPointToRay (Input.mousePosition);

			RaycastHit hit;
			if (Physics.Raycast (ray, out hit)) {
//				print (hit.transform.gameObject.name);
				if (hit.collider.gameObject.tag.Contains ("Disk")) { // disk tag
					DiskData theDisk = hit.collider.gameObject.GetComponent<DiskData> ();
					// free the disk
					theDisk.reset ();
					FreeDisk (theDisk);
					// get score
					Singleton<ScoreRecorder>.Instance.Record (theDisk);
				}
			}
		}
	}

	public int getDisk (int ruler)
	{
		DiskData theDisk;
		if (free.Count > 0) {
			theDisk = free.ToArray () [free.Count - 1];
			free.RemoveAt (free.Count - 1);
			theDisk.setStart (ruler);
			used.Add (theDisk);
		} else {
			DiskCount++;
			// GameObject newDisk = Instantiate (Resources.Load ("Disk")) as GameObject;
			GameObject newDisk = Instantiate (diskPrefab) as GameObject;
			newDisk.name = "Disk" + DiskCount.ToString ();
			theDisk = newDisk.GetComponent<DiskData> ();
			theDisk.innerDiskCount = DiskCount;
			theDisk.setStart (ruler);
			used.Add (theDisk);
		}
		return theDisk.indexInUsed = used.Count - 1;
	}

	public void FreeDisk (int diskNo)
	{	
		DiskData theDisk = used.ToArray () [diskNo];
		if (theDisk == null) {
			throw new System.Exception ();
		} else {
			free.Add (theDisk);
			used.Remove (theDisk);
		}
	}

	public void FreeDisk (DiskData disk)
	{
		
		DiskData theDisk = null;
		foreach (DiskData oneDisk in used) {
			if (oneDisk.innerDiskCount == disk.innerDiskCount) {
				theDisk = oneDisk;
			}
		}
		if (theDisk == null) {
			throw new System.Exception ();
		} else {
			theDisk.reset ();
			free.Add (theDisk);
			used.Remove (theDisk);
		}
	}

	public void FreeAllDisks ()
	{
		for (int i = used.Count - 1; i >= 0; i--) {
			DiskData disk = used [i];
			free.Add (disk);
			used.Remove (disk);
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