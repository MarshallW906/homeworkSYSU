/**
 * Created by Marshall on 2016/10/14.
 */

$(function () {
    var score = 0, time = 0, gameStart = false, clockId = null;
    var statusBar = $("#status-bar");
    var timeBar = $("#time-bar");
    var scoreBar = $("#score-bar");

    function clock() {
        if (time != 0) {
            time--;
            timeBar.val(time.toString(10));
        } else if (gameStart) {
            gameStart = false;
            statusBar.val("Game Over");
            alert("Game Over\nYour score is:  " + score.toString(10));
            clearInterval(clockId);
        }
    }

    var singleMole = document.getElementsByClassName('single-mole')[0];
    _.times(59, function () {
        $(singleMole).after($(singleMole).clone(true));
    });

    var moles = $(".single-mole");
    _(moles).forEach(function (eachMole) {
        $(eachMole).click(function (event) {
            if (gameStart)
                if ($(this).hasClass('yes-dishu')) {
                    $(this).removeClass('yes-dishu');
                    score++;
                    scoreBar.val(score.toString(10));
                    $(moles[_.random(0, 60)]).addClass('yes-dishu');
                } else {
                    score--;
                    scoreBar.val(score.toString(10));
                }
        });
    }).value();

    $("#SE-button").click(function () {
        if (gameStart) pauseGame();
        else startGame();
        timeBar.val(time.toString(10));
        scoreBar.val(score.toString(10));
    });

    function pauseGame() {
        gameStart = false;
        clearInterval(clockId);
        statusBar.val("Game Paused");
    }

    function startGame() {
        gameStart = true;
        if (time == 0) {
            moles.removeClass('yes-dishu');
            $(moles[_.random(0, 60)]).addClass('yes-dishu');
            time = 30;
            score = 0;
        }
        statusBar.val("Playing");
        clockId = setInterval(clock, 1000);
    }
});