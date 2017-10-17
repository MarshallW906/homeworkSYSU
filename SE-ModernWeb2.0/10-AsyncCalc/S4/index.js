function init() {
    $('.unread').html("").hide();
    $('#result-li').html("");
    $(".button").removeClass('button-clicked').addClass('button-unclicked');
    $("#order").html("");
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
        var arrObj = {
            'A': 0,
            'B': 1,
            'C': 2,
            'D': 3,
            'E': 4
        };
        var arr = ['A', 'B', 'C', 'D', 'E'];
        var randomOrder = arr.sort(function () {
            return 0.5 - Math.random()
        }).join();
        $("#order").html(randomOrder);

        ringButtonsClickFunc.apply($($('.button').get(arrObj[arr[0]]))).then(function (data) {
            return ringButtonsClickFunc.apply($($('.button').get(arrObj[arr[1]])));
        }).then(function (data) {
            return ringButtonsClickFunc.apply($($('.button').get(arrObj[arr[2]])));
        }).then(function (data) {
            return ringButtonsClickFunc.apply($($('.button').get(arrObj[arr[3]])));
        }).then(function (data) {
            return ringButtonsClickFunc.apply($($('.button').get(arrObj[arr[4]])));
        }).then(function (data) {
            return $("#info-bar").click().promise();
        });
    });
}