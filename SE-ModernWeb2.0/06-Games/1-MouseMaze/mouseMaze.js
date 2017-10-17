/**
 * Created by Marshall on 2016/10/12.
 */

window.onload = function () {
    var S_button = document.getElementById('S-button');
    var E_button = document.getElementById('E-button');
    var wallList = document.getElementsByClassName('wall');
    var mazePane = document.getElementById('maze');
    var statusBar = document.getElementById('status-bar');
    var gameStart = false;
    var lose = false;
    var cheat = false;
    var timer = null;
    var alpha = 0;

    function changeStatusOpacity(opaTarget) {
        timer = setInterval(function () {
            if (opaTarget == alpha) {
                clearInterval(timer);
            } else {
                var speed = 10;
                if (alpha > opaTarget) {
                    speed *= -1;
                }
                alpha += speed;
                statusBar.style.opacity = alpha / 100;
            }
        }, 40);
    }

    S_button.onmouseover = function (event) {
        if (!gameStart) {
            gameStart = true;
            cheat = false;
            lose = false;
            statusBar.innerText = "";
            statusBar.style.opacity = "0";
            alpha = 0;
            for (var i = 0; i < wallList.length; i++)
                wallList[i].classList.remove('youLoseRed');
        }
    };
    E_button.onmouseover = function (event) {
        if (gameStart) {
            if (cheat) {
                // show don't cheat
                statusBar.innerText = "Don't cheat, you should start from the 'S' and move to the 'E' inside the maze!";
                changeStatusOpacity(100);
            } else {
                // show you win
                statusBar.innerText = "you Win!";
                changeStatusOpacity(100);
            }
            gameStart = false;
        }

    };

    mazePane.onmouseleave = function (event) {
        if (gameStart) {
            cheat = true;
        }
    }

    for (var i = 0; i < wallList.length; i++) wallList[i].onmouseover = function (event) {
        if (gameStart) {
            lose = true;
            event.target.classList.add('youLoseRed');
            statusBar.innerText = "you Lose!";
            changeStatusOpacity(100);
            gameStart = false;
        }
    }
}