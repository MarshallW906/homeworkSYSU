/**
 * Created by Marshall on 2016/11/5.
 */

$(function () {
    var gameStart = false, lose = false, cheat = false;
    var statusBar = $("#status-bar");
    var wallList = $(".wall");
    $("#S-button").mouseover(function () {
        gameStart = true;
        cheat = false;
        lose = false;
        statusBar.text("");
        statusBar.fadeOut();
        _(wallList).forEach(function (singleWall) {
            $(singleWall).removeClass('youLoseRed');
        }).value();
    });
    $("#E-button").mouseover(function () {
        if (gameStart) {
            if (cheat) {
                statusBar.text("Don't cheat, you should start from the 'S' and move to the 'E' inside the maze!");
                statusBar.fadeIn();
            } else {
                statusBar.text("you Win!");
                statusBar.fadeIn();
            }
            gameStart = false;
        }
    });
    $("#maze").mouseleave(function () {
        if (gameStart) cheat = true;
    });
    _(wallList).forEach(function (singleWall) {
        $(singleWall).mouseover(function () {
            if (gameStart) {
                lose = true;
                $(this).addClass('youLoseRed');
                statusBar.text("you Lose!");
                statusBar.fadeIn();
                gameStart = false;
            }
        });
    }).value();
});