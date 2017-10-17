using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CCActionManager : SSActionManager, IActionManager, ISSActionCallback {

	private DiskFactory diskFactory;

	// Use this for initialization
	void Awake () {
		this.sceneController = Singleton<FirstController>.Instance;
		diskFactory = Singleton<DiskFactory>.Instance;
	}

	// Update is called once per frame
	protected new void Update () {
		base.Update ();
	}

	public CCMoveToAction ApplyMoveToAction(GameObject obj, float speed) {
		CCMoveToAction tmpAction = CCMoveToAction.GetSSAction (speed);
		base.RunAction (obj, tmpAction, this);
		return tmpAction;
	}

	#region implementation of IActionManager
	public void playDisk() {
		GameObject diskObj = diskFactory.GetDiskObject (diskFactory.GetDisk (sceneController.round));
		this.ApplyMoveToAction (diskObj, sceneController.getSpeedByRound());
	}

	public void clearActions() {
		base.ClearAction ();
	}
	#endregion

	#region implementation of ISSActionCallback
	public void SSActionEvent (SSAction source, SSActionEventType events = SSActionEventType.Compeleted,
		int intParam = 0,
		string strParam = null,
		Object objectParam = null) {

		source.enable = false;
		source.destory = true;
		source.gameObject.transform.position = source.originPosition;
	}
	#endregion
}
