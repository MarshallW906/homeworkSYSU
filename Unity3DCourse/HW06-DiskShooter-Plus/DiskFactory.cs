using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DiskFactory : MonoBehaviour
{
	[Header("飞碟预制")]
	public GameObject diskTemplate;

	private List<DiskData> used;
	private List<DiskData> free;
	private int DiskCount;

	private FirstController sceneController;

	void Awake ()
	{
		used = new List<DiskData> ();
		free = new List<DiskData> ();
		DiskCount = 0;
		sceneController = Singleton<FirstController>.Instance;
	}

	public int GetDisk(int roundCount) {
		/**
		 * Generate DiskData due to the Round (corresponding data stored in DiskFactory
		 * return the "generated" disk's id in List<DiskData> used;
		 * the returned id (that is the disk which is in use) will be recorded in the caller.
		 */
		DiskData theDisk;
		if (free.Count > 0) {
			theDisk = free.ToArray () [free.Count - 1];
			Rigidbody rigid = theDisk.gameObject.GetComponent<Rigidbody> ();
			if (sceneController.currentMoveMode == FirstController.MoveMode.CCMove) {
				rigid.isKinematic = true;
				rigid.useGravity = false;
			} else {
				rigid.isKinematic = false;
				rigid.useGravity = true;
			}
			free.RemoveAt (free.Count - 1);
		} else {
			DiskCount++;
			// GameObject newDisk = Instantiate (Resources.Load ("Disk")) as GameObject;
			GameObject newDisk = Instantiate (diskTemplate) as GameObject;
			Rigidbody t_rigidbody = newDisk.GetComponent<Rigidbody> ();
			t_rigidbody.isKinematic = (sceneController.currentMoveMode == FirstController.MoveMode.CCMove) ? true : false;
			t_rigidbody.detectCollisions = true;

			newDisk.name = "Disk" + DiskCount.ToString ();
			theDisk = newDisk.GetComponent<DiskData> ();

			theDisk.innerDiskCount = DiskCount;
		}
		theDisk.set (getDiskDataByRound (roundCount));
		used.Add (theDisk);

		return theDisk.indexInUsed = used.Count - 1;
	}

	/**
	 * 给定id（在used中的位置）
	 * 返回对应的GameObject
	 */
	public GameObject GetDiskObject(int id) {
		return used [id].gameObject;
	}
	/**
	 * 给定id（在used中的位置）
	 * Free掉目标DiskData （从used中取出加入free）
	 */
	public void Free(int id) {
		DiskData theDisk = used[id];
		if (theDisk == null) {
			throw new System.Exception ();
		} else {
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

		for (int i = 0; i < free.Count; i++) {
			free [i].transform.position = new Vector3 (3f * i, 3f * i, -20);
			free [i].gameObject.GetComponent<Rigidbody> ().velocity = Vector3.zero;
		}
	}

	private const float basicDiskSize = 0.6f;
	private static DiskData getDiskDataByRound(int roundCount) {
		// size, color, speed, shoot score
		// size
		float size = basicDiskSize + 0.5f / roundCount;

		// color
		float r = Random.Range (0f, 1f);  
		float g = Random.Range (0f, 1f);  
		float b = Random.Range (0f, 1f); 
		Color tcolor = new Color (r, g, b);

		// speed
		float speed = 10f + 5f * roundCount;

		// shoot score
		int score = 10 * roundCount;

		return new DiskData (size, tcolor, speed, score);
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
