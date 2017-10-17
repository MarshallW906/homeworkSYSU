function init() {
    $('.unread').html("").hide();
    $('#result-li').html("");
    $(".button").removeClass('button-clicked').addClass('button-unclicked');
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
    var $ringButtons = $(".button");
    _.chain($ringButtons).forEach(function (singleButton) {
        $(singleButton).click(ringButtonsClickFunc);
    }).value();
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

function ringButtonsClickFunc() {
    var theDefer = new $.Deferred();
    var $thisButton = $(this);
    var $thisBalloon = $thisButton.find('.unread');
    var $ringButtons = $('.button');
    var thisIndex = $thisButton.index();

    var isClicked = _.findIndex(window.clickedButton, function (index) {
        return index === thisIndex;
    });
    if (isClicked !== -1)
        return false;

    var promiseShow = $thisBalloon.show().promise();
    promiseShow.then(function () {
        $thisBalloon.text("...");
        $ringButtons.removeClass('button-unclicked').addClass('button-clicked');
        $.post("/", function (data) {
            $thisBalloon.html(data.toString());
            window.clickedButton.push($thisButton.index());
        }).promise().then(
            function () {
                $ringButtons.addClass('button-unclicked').removeClass('button-clicked');
                // $thisButton.removeClass('button-unclicked').addClass('button-clicked');
                _.chain(window.clickedButton).forEach(function (singleIndex) {
                    $($ringButtons[singleIndex]).removeClass('button-unclicked').addClass('button-clicked');
                }).value();
                theDefer.resolve('Completed.');
            }
        );
    });
    return theDefer.promise();
}

function bindToAtplusButton() {
    $(".icon").click(function () {
        reset();
        var clickA = ringButtonsClickFunc.apply($("#A-button"));
        var clickB = ringButtonsClickFunc.apply($("#B-button"));
        var clickC = ringButtonsClickFunc.apply($("#C-button"));
        var clickD = ringButtonsClickFunc.apply($("#D-button"));
        var clickE = ringButtonsClickFunc.apply($("#E-button"));
        $.when(clickA, clickB, clickC, clickD, clickE).then(function () {
            $("#info-bar").click();
        })
    });
}