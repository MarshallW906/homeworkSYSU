using UnityEngine;
using System.Collections;
using DnP.gameController;
using UnityEngine.SceneManagement;

namespace DnP.gameController
{

	public enum State
	{
		BoatSTART,
		BoatSEMOVING,
		BoatESMOVING,
		BoatEND,
		WIN,
		LOSE
	};

	public interface IUserActions
	{
		void priestSOnB ();

		void priestEOnB ();

		void devilSOnB ();

		void devilEOnB ();

		void moveBoat ();

		void offBoatL ();

		void offBoatR ();

		void restart ();
	}

	public class DNPGameSceneController : System.Object, IUserActions
	{
		// 单例
		private static DNPGameSceneController _instance;
		private gameBase _baseGame;
		private GenGameObject _genGameObj;
		public State state = State.BoatSTART;

		public static DNPGameSceneController GetInstance ()
		{
			if (_instance == null) {
				_instance = new DNPGameSceneController ();
			}
			return _instance;
		}

		public gameBase GetBaseGame ()
		{
			return _baseGame;
		}

		internal void setBaseGame (gameBase t_bc)
		{
			if (_baseGame == null) {
				_baseGame = t_bc;
			}
		}

		public GenGameObject getGenGameObject ()
		{
			return _genGameObj;
		}

		internal void setGenGameObject (GenGameObject ggo)
		{
			if (null == _genGameObj) {
				_genGameObj = ggo;
			}
		}

		public void priestSOnB ()
		{
			_genGameObj.priestStartOnBoat ();
		}

		public void priestEOnB ()
		{
			_genGameObj.priestEndOnBoat ();
		}

		public void devilSOnB ()
		{
			_genGameObj.devilStartOnBoat ();
		}

		public void devilEOnB ()
		{
			_genGameObj.devilEndOnBoat ();
		}

		public void moveBoat ()
		{
			_genGameObj.moveBoat ();
		}

		public void offBoatL ()
		{
			_genGameObj.getOffTheBoat (0);
		}

		public void offBoatR ()
		{
			_genGameObj.getOffTheBoat (1);
		}

		public void restart ()
		{
			SceneManager.LoadScene (SceneManager.GetActiveScene ().name);
			// Application.LoadLevel (Application.loadedLevelName);
			state = State.BoatSTART;
		}

	}
}


public class gameBase : MonoBehaviour
{

	public string gameName { get; set;}
	public string gameRule { get; set;}

	void Start ()
	{
		DNPGameSceneController theGame = DNPGameSceneController.GetInstance ();
		gameName = "Priests and Devils";
		gameRule = "Priests and Devils is a puzzle game in which you will help the Priests and Devils to cross the river within the time limit. There are 3 priests and 3 devils at one side of the river. They all want to get to the other side of this river, but there is only one boat and this boat can only carry two persons each time. And there must be one person steering the boat from one side to the other side. In the flash game, you can click on them to move them and click the go button to move the boat to the other direction. If the priests are out numbered by the devils on either side of the river, they get killed and the game is over. You can try it in many ways. Keep all priests alive! Good luck!             Sphere -- Priest    Cube -- Devil";
		theGame.setBaseGame (this);
	}
}