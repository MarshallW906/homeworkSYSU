using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IArrowEndCallback
{
	void OutCallback (ArrowData arrow);
	// 脱靶
	void InCallback (ArrowData arrow);
	// 中靶
}

public class ArrowData : MonoBehaviour, IArrowEndCallback
{
	public int indexInUsed { get; set; }

	public int innerArrowCount { get; set; }

	public bool isEnable { get; set; }

	private bool InTarget = false;
	private int currentTimeCount;

	private int TimeCount { get; set; }

	[Header ("箭的飞行速度")]
	public float speed;

	void Start ()
	{
		TimeCount = (int)(5f / Time.deltaTime);
	}

	public void EnableAndShoot (Vector3 direction)
	{
		Debug.Log ("enable & shoot");
		this.isEnable = true;
		this.GetComponent<Rigidbody> ().AddForce (direction * speed, ForceMode.VelocityChange);
	}

	void FixedUpdate ()
	{	
		Debug.Log (this.isEnable);
		if (this.isEnable == true) {
			Debug.Log ("fixed Update");
			this.GetComponent<Rigidbody> ().AddForceAtPosition (Vector3.down * 9.8f, new Vector3 (0.01f, 0.45f, 0.01f));
			this.GetComponent<Rigidbody> ().AddForce (Singleton<FirstSceneController>.Instance.wind);
			currentTimeCount++;
		}
		if (currentTimeCount >= TimeCount) {
			OutCallback (this);
		}
		if (InTarget) {
			InCallback (this);
		}
	}

	public ArrowData reset ()
	{
		Debug.Log ("reset called");
		this.isEnable = false;
		this.InTarget = false;
		this.currentTimeCount = 0;
		this.transform.eulerAngles = new Vector3 (90, 0, 0);
		this.setShapeColor ();
		this.gameObject.GetComponent<Rigidbody> ().velocity = Vector3.zero;
		this.gameObject.GetComponent<Rigidbody> ().MovePosition (new Vector3 (0, 0, -20));
		return this;
	}

	void OnCollisionEnter (Collision col)
	{
		Debug.Log ("Collision GameObject: " + col.gameObject.name);
		InTarget = true;
		var scData = col.gameObject.GetComponent<scoreData> ();
		if (scData != null)
			Singleton<FirstSceneController>.Instance.addScore (col.gameObject.GetComponent<scoreData> ().score);
	}

	#region IArrowEndCallback implementation

	public void OutCallback (ArrowData arrow)
	{
		// free arrow
		Debug.Log ("Out callback");
		Singleton<ArrowFactory>.Instance.FreeArrow (arrow);
	}

	public void InCallback (ArrowData arrow)
	{
		Debug.Log ("In Callback");
		arrow.gameObject.GetComponent<Rigidbody> ().isKinematic = true;
		DestroyObject (arrow.gameObject.GetComponent<ArrowData> ());
		// get score
		// keep the arrow on the target
	}

	#endregion

	public void setShapeColor ()
	{
		Renderer render = this.transform.GetComponent<Renderer> ();
		render.material.shader = Shader.Find ("Transparent/Diffuse");
		render.material.color = getRandomColor ();
	}

	public static Color getRandomColor ()
	{
		float r = Random.Range (0f, 1f);  
		float g = Random.Range (0f, 1f);  
		float b = Random.Range (0f, 1f); 
		Color tcolor = new Color (r, g, b);  
		return tcolor;  
	}
}
