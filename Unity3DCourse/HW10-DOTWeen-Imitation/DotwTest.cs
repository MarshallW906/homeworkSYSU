using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DotwTest : MonoBehaviour {

    public Transform target;

    // Use this for initialization
    void Start () {
        var trans = this.GetComponent<Transform>();
        // 这里是先Scale到原来长宽高的2倍、等2s、最后move到target处。
        trans.DoScale(2f, new Vector3(2f, 2f, 2f)).OnComplete((tmdt) => {
            tmdt.trans.DoMove(2f, target.position).PlayNow().OnComplete( (ttmdt) => {
                ttmdt.trans.DoScale(2f, Vector3.one).PlayNow();
            });
        }).PlayNow();
    }
    
    // Update is called once per frame
    void Update () {
        
    }
}
