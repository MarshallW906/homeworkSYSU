using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DiskData : MonoBehaviour
{
	public float size { get; set; }

	public Color color { get; set; }

	public float speed { get; set; }

	public int shotScore { get; set; }

	public SSAction currentSSAction;

	public DiskData(float tsize, Color tcolor, float tspeed, int score) {
		this.size = tsize;
		this.color = tcolor;
		this.speed = tspeed;
		this.shotScore = score;
	}

	public void set(DiskData newData) {
		this.size = newData.size;
		this.color = newData.color;
		this.speed = newData.speed;
		this.shotScore = newData.shotScore;

		this.gameObject.transform.localScale = new Vector3 (size, size, size);

		Renderer render = this.transform.GetComponent<Renderer> ();
		render.material.shader = Shader.Find ("Transparent/Diffuse");
		render.material.color = this.color;
	}
		
	public int indexInUsed { get; set; }

	public int innerDiskCount { get; set; }
}
