﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FirstController : MonoBehaviour, ISceneController, IUserInterface
{
	public enum MoveMode
	{
		CCMove,
		PhysicsMove}

	;

	public Camera cam;

	private DiskFactory currentDiskFactory;
	private IActionManager currentActionManager;

	public MoveMode currentMoveMode { get; set; }

	public int round { get; set; }

	public int trials { get; set; }

	public int score { get; set; }

	public bool isStarted { get; set; }

	public bool isPaused { get; set; }

	void Awake ()
	{
		currentDiskFactory = Singleton<DiskFactory>.Instance;
		currentMoveMode = MoveMode.PhysicsMove;
		currentActionManager = Singleton<PhysicsActionManager>.Instance;

		this.isStarted = false;
		this.isPaused = false;

		this.round = 1;
		this.score = 0;
	}

	#region IUserAction implementation

	public void GameOver ()
	{
		this.isStarted = false;
		this.isPaused = true;
	}

	public void ChangeActionManager ()
	{
		if (this.currentMoveMode == MoveMode.CCMove) {
			this.currentActionManager = Singleton<PhysicsActionManager>.Instance;
			this.currentMoveMode = MoveMode.PhysicsMove;
		} else {
			this.currentActionManager = Singleton<CCActionManager>.Instance;
			this.currentMoveMode = MoveMode.CCMove;
		}
	}

	#endregion

	#region ISceneController implementation

	public void Pause ()
	{
		this.isPaused = true;
		CancelInvoke ();
	}

	public void Resume ()
	{
		this.isPaused = false;
		ShootDisk ();
	}

	public void Restart ()
	{
		round = 1;
		score = 0;
		CancelInvoke ();
		FreeDisk ();
		StartGame ();
	}

	public void StartGame ()
	{
		this.isStarted = true;
		this.isPaused = false;
		diskComp = 0;
		diskShot = 0;
		ShootDisk ();
	}

	#endregion

	#region IGamePlaying implementation

	public void ShootDisk ()
	{
		// 先等3秒 然后每隔1.5秒发送一个
		// invoke
		InvokeRepeating ("ShootSingleDisk", 1f, 1.5f);
	}

	int diskShot = 0;
	public int diskComp = 0;
	private void ShootSingleDisk ()
	{
		if (diskShot == 5) {
			CancelInvoke ();
		}
		this.currentActionManager.playDisk ();
	}

	public void FreeDisk ()
	{
		this.currentDiskFactory.FreeAllDisks ();
		this.currentActionManager.clearActions ();
		// and?
	}

	public void NextRound ()
	{
		FreeDisk ();
		++round;
		diskShot = 0;
		diskComp = 0;
		Pause ();

	}

	public void addScoreByRound ()
	{
		this.score += this.round * 10;
	}

	public float getSpeedByRound ()
	{
		return 30f + 5f * round;
	}

	#endregion

	// Update is called once per frame
	void Update ()
	{
		if (diskComp == 5) {
			NextRound ();
		}
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
				if (hit.collider.gameObject.tag.Contains ("Disk") && isPaused == false) { // disk tag
					// get score
					this.addScoreByRound ();

					hit.collider.gameObject.GetComponent<Rigidbody> ().isKinematic = false;

					// explosion:
					float radius = 3f;
					Vector3 explosionPos = hit.collider.gameObject.transform.position;
					Collider[] colliders = Physics.OverlapSphere (explosionPos, radius);
					foreach (Collider chit in colliders) {
						Rigidbody t_rigid = chit.gameObject.GetComponent<Rigidbody> ();
						if (t_rigid != null) {
							t_rigid.AddExplosionForce (600, explosionPos, radius);
						}
					}

					DiskData tmpDiskData = hit.collider.GetComponent<DiskData> ();

					// free the disk
					currentDiskFactory.Free (tmpDiskData.indexInUsed);
//					hit.collider.gameObject.transform.position = new Vector3 (0, 0, -20);

					// free the action
					tmpDiskData.currentSSAction.enable = false;
					tmpDiskData.currentSSAction.destory = true;


				}
			}
		}
	}

	void OnGUI ()
	{
		if (isStarted == false) {
			if (GUI.Button (new Rect (20, 50, 50, 30), "Start")) {
				StartGame ();
			} 
		} else { // started
			/**
			 * Game Runtime GUI :
			 * 	 Button : pause, restart
			 *   Text : score
			 */
			if (GUI.Button (new Rect (260, 20, 100, 30), "Restart")) {
				Restart ();
			}
			if (GUI.Button (new Rect (260, 60, 100, 30), "ChangeMove")) {
				ChangeActionManager ();
				Restart ();
			}
			if (isPaused == true) {
				if (GUI.Button (new Rect (20, 20, 100, 30), "NextRound")) {
					Resume ();
				}
			}
			GUI.TextField (new Rect (120, 20, 100, 30), "Score:" + this.score.ToString ());
		}
	}
}
