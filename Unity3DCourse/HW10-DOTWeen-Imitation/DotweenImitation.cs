using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class MyDotTweenBehavGenerator {
    public static IEnumerator _DoDelay(float timeSec) {   
        yield return new WaitForSeconds(timeSec);
    }
    public static MyDotTween DoDelay(this Transform transform, float timeSec) {
        MonoBehaviour mono = transform.GetComponent<MonoBehaviour>();
        Coroutine coroutine = mono.StartCoroutine(_DoDelay(timeSec));
        MyDotTween myDotW = MyDotTween.GetDotTweenInstance ("DoMove", transform);
        
        myDotW.ApplyCoroutine(coroutine);
        
        return myDotW;
    }

    public static IEnumerator _DoMove(this MonoBehaviour mono, MyDotTween mydot, float timeSec, Vector3 target) {
        Vector3 dis = (target - mydot.trans.position) / timeSec;
        for (float f = timeSec; f >= 0.0f; f -= Time.deltaTime) {
            mydot.trans.Translate(dis * Time.deltaTime);
            yield return null;

            while (mydot.IsPaused == true) {
                yield return null;
            }
        }
        mydot.runOnComplete();
    }

    public static MyDotTween DoMove(this Transform trans, float timeSec, Vector3 target) {
        MonoBehaviour mono = trans.GetComponent<MonoBehaviour>();
        MyDotTween myDotW = MyDotTween.GetDotTweenInstance ("DoMove", trans);
        Coroutine moveCoroutine = mono.StartCoroutine(mono._DoMove(myDotW, timeSec, target));
        myDotW.ApplyCoroutine(moveCoroutine);

        return myDotW;
    }

    public static IEnumerator _DoScale(this MonoBehaviour mono, MyDotTween mydot, float timeSec, Vector3 targetScale) {
        Vector3 dis = (targetScale - mydot.trans.localScale) / timeSec;
        for (float f = timeSec; f >= 0.0f; f -= Time.deltaTime) {
            mydot.trans.localScale += dis * Time.deltaTime;
            yield return null;

            while (mydot.IsPaused == true) {
                yield return null;
            }
        }
        mydot.runOnComplete();
    }

    public static MyDotTween DoScale(this Transform trans, float timeSec, Vector3 targetScale) {
        MonoBehaviour mono = trans.GetComponent<MonoBehaviour>();
        MyDotTween myDotW = MyDotTween.GetDotTweenInstance("DoScale", trans);
        Coroutine scaleCoroutine = mono.StartCoroutine(mono._DoScale(myDotW, timeSec, targetScale));
        Debug.Log(scaleCoroutine);
        myDotW.ApplyCoroutine(scaleCoroutine);

        return myDotW;
    }
}

public class MyDotTween : ScriptableObject {
    private string _name;
    private Coroutine _coroutine;
    internal Transform trans;
    private bool isPaused = true;
    public bool IsPaused {get { return isPaused; } }
    private bool _autoKill = true;

    private Action<MyDotTween> _onComplete;
    private Action<MyDotTween> _onPause;
    private Action<MyDotTween> _onKill;

    public MyDotTween OnComplete(Action<MyDotTween> callback) {
        this._onComplete += callback;
        return this;
    }
    public MyDotTween OnPause(Action<MyDotTween> callback) {
        this._onPause += callback;
        return this;
    }
    public MyDotTween OnKill(Action<MyDotTween> callback) {
        this._onKill += callback;
        return this;
    }

    protected MyDotTween() {}

    // 用ScriptableObject来自动管理内存
    public static MyDotTween GetDotTweenInstance (string name, Transform transform) {
        MyDotTween mydotw = ScriptableObject.CreateInstance<MyDotTween> ();
        mydotw.SetName(name);
        mydotw.trans = transform;
        mydotw.OnComplete(defaultCallback);
        return mydotw;
    }

    internal MyDotTween ApplyCoroutine(Coroutine co) {
        if (_coroutine != null) {
            trans.GetComponent<MonoBehaviour>().StopCoroutine(_coroutine);
        }
        this._coroutine = co;
        return this;
    }
    
    public MyDotTween SetName(string name) {
        this._name = name;
        return this;
    }
    public string GetName() {
        return this._name;
    }

    public MyDotTween Pause() {
        this.isPaused = true;
        if (this._onPause != null) {
            this._onPause(this);
        }
        return this;
    }

    public MyDotTween Kill() {
        if (this._coroutine != null) {
            this.trans.GetComponent<MonoBehaviour>().StopCoroutine(_coroutine);
        }
        if (this._onKill != null) {
            this._onKill(this);
        }
        return this;
    }

    public MyDotTween PlayNow() {
        this.isPaused = false;
        return this;
    }

    static internal void defaultCallback(MyDotTween mydot) {
        Debug.Log(mydot.GetName() + "default Callback");
    }

    internal void runOnComplete() {
        if (this._onComplete != null) {
            this._onComplete(this);
        }
    }
}