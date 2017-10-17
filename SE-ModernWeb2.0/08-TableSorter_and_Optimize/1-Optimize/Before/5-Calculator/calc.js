/**
 * Created by Marshall on 2016/10/4.
 */

window.onload = function () {
    var numberList = document.getElementsByClassName("number");
    var opList = document.getElementsByClassName("op-symbol");
    var expression = document.getElementById("show-expr-res");
    var status_bar = document.getElementById("status-bar");
    var flag_Eval_ed = false;
    var i;
    expression.value = "0";

    // apply onclick events to the numbers & brackets buttons
    for(i = 0; i < numberList.length; ++i) numberList[i].onclick = function (btn) {
        if (flag_Eval_ed == true) {
            expression.value = "0";
            flag_Eval_ed = false;
        }
        var content = btn.target.innerText;
        if (expression.value == "0") {
            expression.value = content;
        } else {
            expression.value = expression.value + content;
        }
        // scrollToEnd();
        expression.scrollLeft = expression.scrollWidth - expression.clientWidth;
    };

    // apply onclick events to the +-*/ buttons
    for(i = 0; i < opList.length; ++i) opList[i].onclick = function (btn) {
        if (btn.target.innerText != "=") {
            flag_Eval_ed = false;
            var exp = expression.value;
            var lastChar = exp[exp.length - 1];
            if (lastChar == "+" || lastChar == "-" || lastChar == "*" || lastChar == "/") {
                status_bar.value = "double process symbol";
                alert("double process symbol");
                return;
            }
            var content = btn.target.innerText;
            expression.value = expression.value + content;
            // scrollToEnd();
            expression.scrollLeft = expression.scrollWidth - expression.clientWidth;
        }
    };

    // apply events to the '=' button
    var equal = document.getElementById("equal");
    equal.onclick = function() {
        var content = expression.value.toString();
        try {
            var result = eval(content);
            if(result == 'Infinity' || result == '-Infinity') {
                throw new Error("May Div zero");
            }
            try {
                expression.value = parseFloat(result.toFixed(8)); //to deal with the precision problem;
                status_bar.value = "";
            } catch (error) {}
            flag_Eval_ed = true;
        } catch (error) {
            alert(error.message);
            status_bar.value = error.message;
        }
    };

    // apply events to the "backspace" button
    var delOne =  document.getElementById("delOne");
    delOne.onclick = function () {
        if(flag_Eval_ed == true) {
            expression.value = "";
            flag_Eval_ed = false;
        }
        var content = expression.value.toString();
        var len = content.length;
        expression.value = content.substring(0, len-1);
        if (expression.value == "") expression.value = "0";
        // scrollToEnd();
        expression.scrollLeft = expression.scrollWidth - expression.clientWidth;
    };


    // apply events to the "CE" button
    var delAll = document.getElementById("delAll");
    delAll.onclick = function() {
        expression.value = "0";
    }
};

/**
 * show the right-est numbers
 * function scrollToEnd() {
 *   expression.scrollLeft = expression.scrollWidth - expression.clientWidth;
 * }
 */

// when double click div / span etc, cancel the focus event
document.onselectstart = function() {
    return false;
};