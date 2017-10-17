using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IRoundController
{
	void nextRound ();

	void getScore (DiskData disk);

	void startShotDisk ();

	void stopShotDisk ();

	void restartAll ();
}

public class RoundController : MonoBehaviour, IRoundController
{

	private DiskFactory theFactory;
	private ScoreRecorder theScoreRecorder;

	private int roundCount;

	private int currentTimeCount;
	private int timeCountPerSec;
	private bool startShot;

	[Header ("每一轮发出的飞碟数量")]
	public int n;
	private int n_current;

	void Awake ()
	{
		// register the following classes
		theFactory = Singleton<DiskFactory>.Instance;
		theScoreRecorder = Singleton<ScoreRecorder>.Instance;
		roundCount = 0;
		timeCountPerSec = (int)(1f / Time.deltaTime);
		if (n <= 0) {
			// set default to 5
			n = 5;
		}
	}

	public void nextRound ()
	{
		roundCount++;
		// free all the disks
		theFactory.FreeAllDisks ();
		currentTimeCount = 0;
		n_current = 0;
		startShotDisk ();
	}

	public void getScore (DiskData disk)
	{
		theScoreRecorder.Record (disk);
	}

	public void startShotDisk ()
	{
		this.startShot = true;
	}

	public void stopShotDisk ()
	{
		n_current = 0;
		this.startShot = false;
	}

	public void restartAll ()
	{
		stopShotDisk ();
		roundCount = 0;
		theScoreRecorder.Reset ();
	}

	void Update ()
	{
		currentTimeCount++;
		if (this.startShot && n_current < n) {
			if (currentTimeCount % timeCountPerSec == 0) {
				n_current++;
				if (n_current == n) {
					stopShotDisk ();
					return;
				}
				theFactory.getDisk (roundCount);
			}
		}

	}

	void OnGUI ()
	{
		if (n_current == 0 && theFactory.usedCount == 0) {
			if (GUI.Button (new Rect (150, 20, 80, 30), "start")) {
				this.nextRound ();
			}
			if (GUI.Button (new Rect (250, 20, 80, 30), "restartAll")) {
				this.restartAll ();
			}
				
		}
	}
}

