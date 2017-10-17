/**
 * Created by Marshall on 2016/10/14.
 */

window.onload = function () {
    var SE_button = document.getElementById('SE-button');
    var timeBar = document.getElementById('time-bar');
    var scoreBar = document.getElementById('score-bar');
    var statusBar = document.getElementById('status-bar');
    var score = 0;
    var time = 0;
    var gameStart = false;
    var clockId;

    function clock() {
        if (time != 0) { // if (time)
            time--;
            timeBar.value = time.toString(10);
        } else if (gameStart) {
            gameStart = false;
            statusBar.value = "Game Over";
            alert("Game Over\nYour score is:  " + score.toString(10));
            clearInterval(clockId);
        }
    }

    timeBar.value = time.toString(10);

    // create the 60 moles
    var singleMole = document.getElementsByClassName('single-mole')[0];
    for (var i = 0; i < 59; i++) {
        var moleClone = singleMole.cloneNode(true);
        singleMole.parentNode.appendChild(moleClone);
    }

    var moles = document.getElementsByClassName('single-mole');
    for (var i = 0; i < moles.length; i++) moles[i].onclick = function (event) {
        if (gameStart)
            if (event.target.classList.contains('yes-dishu')) {
                event.target.classList.remove('yes-dishu');
                score++;
                scoreBar.value = score.toString(10);
                var randIndex = Math.floor(Math.random() * 60);
                if (randIndex == 60) randIndex--;
                moles[randIndex].classList.add('yes-dishu');
            } else {
                score--;
                scoreBar.value = score.toString(10);
            }
    };

    SE_button.onclick = function () {
        if (gameStart) { // pause
            gameStart = false;
            // clear the clock
            clearInterval(clockId);
            // text process & clean the dishu
            // for (var i = 0; i < moles.length; i++) moles[i].classList.remove('yes-dishu');
            timeBar.value = time.toString(10);
            scoreBar.value = score.toString(10);
            statusBar.value = "Game Paused";
        } else {
            gameStart = true;
            if (time == 0) {
                for (var i = 0; i < moles.length; i++) moles[i].classList.remove('yes-dishu');
                var randIndex = Math.floor(Math.random() * 60);
                if (randIndex == 60) randIndex--;
                moles[randIndex].classList.add('yes-dishu');
                time = 30;
                score = 0;
            } else { // resume
                // nothing explicit to do
            }
            // text process
            timeBar.value = time.toString(10);
            scoreBar.value = score.toString(10);
            statusBar.value = "Playing";

            // add the clock
            clockId = setInterval(clock, 1000);
        }
    }
};