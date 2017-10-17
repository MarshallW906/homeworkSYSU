/**
 * Created by Marshall on 2016/11/4.
 */

$(function () {
    var flag_Eval_ed = false;
    var expression = $("#show-expr-res");
    var statusBar = $("#status-bar");
    expression.val("0");

    _($(".number")).forEach(function (singleNumber) {
        $(singleNumber).click(function (btn) {
            if(flag_Eval_ed) {
                expression.val("0");
                flag_Eval_ed = false;
            }
            if (expression.val() == "0") expression.val(btn.target.innerText);
            else expression.val(expression.val() + btn.target.innerText);
            expression.scrollLeft = expression.scrollWidth - expression.clientWidth;
        });
    }).value();
    _($(".op-symbol")).forEach(function (singleOp) {
        $(singleOp).click(function (btn) {
            if (btn.target.innerText != "=") {
                flag_Eval_ed = false;
                var lastChar = expression.val()[expression.val().length - 1];
                if (lastChar == "+" || lastChar == "-" || lastChar == "*" || lastChar == "/") {
                    statusBar.val("double process symbol");
                    alert("double process symbol");
                    return;
                }
                expression.val(expression.val() + btn.target.innerText);
                expression.scrollLeft = expression.scrollWidth - expression.clientWidth;
            }
        });
    }).value();
    $("#equal").click(function () {
        try {
            var result = eval(expression.val().toString());
            if (result == "Infinity" || result == "-Infinity") throw new Error("May Div Zero");
            expression.val(parseFloat(result.toFixed(8)));
            statusBar.val("");
            flag_Eval_ed = true;
        } catch (error) {
            alert(error.message);
            statusBar.val(error.message);
        }
    });
    $("#delOne").click(function () {
        if (flag_Eval_ed) {
            expression.val("");
            flag_Eval_ed = false;
        }
        expression.val(expression.val().toString().substring(0, expression.val().toString().length-1));
        if (expression.val() == "") expression.val("0");
        expression.scrollLeft = expression.scrollWidth - expression.clientWidth;
    });
    $("#delAll").click(function () {
        expression.val("0");
    });
});
