using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class planeClick : MonoBehaviour {
	public Camera cam;

	private MarkFactory myFactory;

	// Use this for initialization
	void Start () {
		myFactory = Singleton<MarkFactory>.Instance;
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetButtonDown ("Fire1")) {
			// if clicked on it, Free it
			//Debug.Log ("Fire1 Pressed");
			//			Debug.Log (Input.mousePosition);
			Vector3 mp = Input.mousePosition;
			Camera ca = cam.GetComponent<Camera> ();
			Ray ray = ca.ScreenPointToRay (Input.mousePosition);

			RaycastHit hit;
			if (Physics.Raycast (ray, out hit)) {
				//				print (hit.transform.gameObject.name);
				if (hit.collider.gameObject.tag.Contains ("Finish")) { // disk tag
					GameObject newObj = myFactory.placeAttackMark(hit.point);
				}
			}
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