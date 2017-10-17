function init() {
    $('.unread').html("").hide();
    $('#result-li').html("");
    $(".button").removeClass('button-clicked').addClass('button-unclicked');
    $("#order").html("");
    $("#tucao").html("");
    window.clickedButton = [];
    window.cleaning = false;
}
function reset() {
    init();
}

$.ready.promise().done(function () {
    init();
    bindToRingButtons();
    bindToInfobarCalc();
    bindToButtonOnmouseleave(); // reset all
    bindToAtplusButton();
});

function bindToRingButtons() {
    $('#A-button').click(function () {
        return AHandler.call(this, 0);
    });
    $('#B-button').click(function () {
        return BHandler.call(this, 0);
    });
    $('#C-button').click(function () {
        return CHandler.call(this, 0);
    });
    $('#D-button').click(function () {
        return DHandler.call(this, 0);
    });
    $('#E-button').click(function () {
        return EHandler.call(this, 0);
    });
}
function bindToInfobarCalc() {
    $("#info-bar").click(function () {
        // infobarClickFunc
        var theDefer = new $.Deferred();
        if (window.clickedButton.length !== 5) return false;

        var sumRes = _($(".unread")).map(function (singleButton) {
            var res = parseInt($(singleButton).html());
            return res.toString() == "NaN" ? 0 : res;
        }).sum();
        $('#result-li').html(sumRes.toString());
        theDefer.resolve('Calculated.');
        return theDefer;
    });
}
function bindToButtonOnmouseleave() {
    $("#button").mouseleave(reset);
}

function bindToAtplusButton() {
    $(".icon").click(function () {
        reset();
        var arrObj = {
            'A' : AHandler,
            'B' : BHandler,
            'C' : CHandler,
            'D' : DHandler,
            'E' : EHandler
        };
        var arr = ['A', 'B', 'C', 'D', 'E'];
        var randomOrder = arr.sort(function () {
            return 0.5 - Math.random()
        }).join();
        $("#order").html(randomOrder);

        arrObj[arr[0]].call(this, 0).then(function (currentSum) {
            return arrObj[arr[1]].call(this, currentSum);
        }).then(function (currentSum) {
            return arrObj[arr[2]].call(this, currentSum);
        }).then(function (currentSum) {
            return arrObj[arr[3]].call(this, currentSum);
        }).then(function (currentSum) {
            return arrObj[arr[4]].call(this, currentSum);
        }).then(function (Sum) {
            $('.button').addClass('button-unclicked').removeClass('button-clicked');
            return BubbleHandler(Sum);
        });

    });
}