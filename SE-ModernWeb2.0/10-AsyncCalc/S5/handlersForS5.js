function AHandler(previousSum) {
    var theDefer = new $.Deferred();
    previousSum = (parseInt(previousSum).toString() === "NaN") ? -1 : previousSum;

    var $Button = $("#A-button");
    var $Balloon = $Button.find('.unread');
    var $ringButtons = $('.button');
    var thisIndex = $Button.index();

    var isClicked = _.findIndex(window.clickedButton, function (index) {
        return index === thisIndex;
    });
    if (isClicked !== -1)
        theDefer.resolve("has beem clicked OR other");

    $Balloon.show().text("...");
    $ringButtons.removeClass('button-unclicked').addClass('button-clicked');
    $.post("/", function (data) {
        // throw Error randomly
        if (_.random(0, 1000) % 2 == 1) {
            $('#tucao').html("这根本不是什么秘密");
            $Balloon.html("N/A");
            theDefer.resolve(previousSum);
        } else {
            $Balloon.html(data.toString());
            $('#tucao').html("这是个天大的秘密");
            var balloonValue = parseInt(data.toString());

            window.clickedButton.push($Button.index());
            // console.log("A", data.toString());
            $ringButtons.addClass('button-unclicked').removeClass('button-clicked');
            _.chain(window.clickedButton).forEach(function (singleIndex) {
                $($ringButtons[singleIndex]).removeClass('button-unclicked').addClass('button-clicked');
            }).value();
            theDefer.resolve(previousSum + balloonValue);
        }
    });
    return theDefer.promise();
};

function BHandler(previousSum) {
    var theDefer = new $.Deferred();
    previousSum = (parseInt(previousSum).toString() === "NaN") ? -1 : previousSum;

    var $Button = $("#B-button");
    var $Balloon = $Button.find('.unread');
    var $ringButtons = $('.button');
    var thisIndex = $Button.index();

    var isClicked = _.findIndex(window.clickedButton, function (index) {
        return index === thisIndex;
    });
    if (isClicked !== -1)
        theDefer.resolve("has beem clicked OR other");

    $Balloon.show().text("...");
    $ringButtons.removeClass('button-unclicked').addClass('button-clicked');
    $.post("/", function (data) {
        // throw Error randomly
        if (_.random(0, 1000) % 2 == 1) {
            $('#tucao').html("我知道");
            $Balloon.html("N/A");
            theDefer.resolve(previousSum);
        } else {
            $Balloon.html(data.toString());
            $('#tucao').html("我不知道");
            var balloonValue = parseInt(data.toString());

            window.clickedButton.push($Button.index());
            // console.log("B", data.toString());
            $ringButtons.addClass('button-unclicked').removeClass('button-clicked');
            _.chain(window.clickedButton).forEach(function (singleIndex) {
                $($ringButtons[singleIndex]).removeClass('button-unclicked').addClass('button-clicked');
            }).value();
            theDefer.resolve(previousSum + balloonValue);
        }
    });
    return theDefer.promise();
};

function CHandler(previousSum) {
    var theDefer = new $.Deferred();
    previousSum = (parseInt(previousSum).toString() === "NaN") ? -1 : previousSum;

    var $Button = $("#C-button");
    var $Balloon = $Button.find('.unread');
    var $ringButtons = $('.button');
    var thisIndex = $Button.index();

    var isClicked = _.findIndex(window.clickedButton, function (index) {
        return index === thisIndex;
    });
    if (isClicked !== -1)
        theDefer.resolve("has beem clicked OR other");

    $Balloon.show().text("...");
    $ringButtons.removeClass('button-unclicked').addClass('button-clicked');
    $.post("/", function (data) {
        // throw Error randomly
        if (_.random(0, 1000) % 2 == 1) {
            $('#tucao').html("你知道");
            $Balloon.html("N/A");
            theDefer.resolve(previousSum);
        } else {
            $Balloon.html(data.toString());
            $('#tucao').html("你不知道");
            var balloonValue = parseInt(data.toString());

            window.clickedButton.push($Button.index());
            // console.log("C", data.toString());
            $ringButtons.addClass('button-unclicked').removeClass('button-clicked');
            _.chain(window.clickedButton).forEach(function (singleIndex) {
                $($ringButtons[singleIndex]).removeClass('button-unclicked').addClass('button-clicked');
            }).value();
            theDefer.resolve(previousSum + balloonValue);
        }
    });
    return theDefer.promise();
};

function DHandler(previousSum) {
    var theDefer = new $.Deferred();
    previousSum = (parseInt(previousSum).toString() === "NaN") ? -1 : previousSum;

    var $Button = $("#D-button");
    var $Balloon = $Button.find('.unread');
    var $ringButtons = $('.button');
    var thisIndex = $Button.index();

    var isClicked = _.findIndex(window.clickedButton, function (index) {
        return index === thisIndex;
    });
    if (isClicked !== -1)
        theDefer.resolve("has beem clicked OR other");

    $Balloon.show().text("...");
    $ringButtons.removeClass('button-unclicked').addClass('button-clicked');
    $.post("/", function (data) {
        // throw Error randomly
        if (_.random(0, 1000) % 2 == 1) {
            $('#tucao').html("他知道");
            $Balloon.html("N/A");
            theDefer.resolve(previousSum);
        } else {
            $Balloon.html(data.toString());
            $('#tucao').html("他不知道");
            var balloonValue = parseInt(data.toString());

            window.clickedButton.push($Button.index());
            // console.log("D", data.toString());
            $ringButtons.addClass('button-unclicked').removeClass('button-clicked');
            _.chain(window.clickedButton).forEach(function (singleIndex) {
                $($ringButtons[singleIndex]).removeClass('button-unclicked').addClass('button-clicked');
            }).value();
            theDefer.resolve(previousSum + balloonValue);
        }
    });
    return theDefer.promise();
};

function EHandler(previousSum) {
    var theDefer = new $.Deferred();
    previousSum = (parseInt(previousSum).toString() === "NaN") ? -1 : previousSum;

    var $Button = $("#E-button");
    var $Balloon = $Button.find('.unread');
    var $ringButtons = $('.button');
    var thisIndex = $Button.index();

    var isClicked = _.findIndex(window.clickedButton, function (index) {
        return index === thisIndex;
    });
    if (isClicked !== -1)
        theDefer.resolve("has beem clicked OR other");

    $Balloon.show().text("...");
    $ringButtons.removeClass('button-unclicked').addClass('button-clicked');
    $.post("/", function (data) {
        // throw Error randomly
        if (_.random(0, 1000) % 2 == 1) {
            $('#tucao').html("!(才怪)");
            $Balloon.html("N/A");
            theDefer.resolve(previousSum);
        } else {
            $Balloon.html(data.toString());
            $('#tucao').html("才怪");
            var balloonValue = parseInt(data.toString());

            window.clickedButton.push($Button.index());
            // console.log("E", data.toString());
            $ringButtons.addClass('button-unclicked').removeClass('button-clicked');
            _.chain(window.clickedButton).forEach(function (singleIndex) {
                $($ringButtons[singleIndex]).removeClass('button-unclicked').addClass('button-clicked');
            }).value();
            theDefer.resolve(previousSum + balloonValue);
        }
    });
    return theDefer.promise();
};

function BubbleHandler(sum) {
    var theDefer = new $.Deferred();

    sum = (parseInt(sum).toString() === "NaN") ? -1 : sum;
    $('#result-li').html(sum.toString());
    $('#tucao').html("楼主异步调用战斗力感人，目测不超过" + sum.toString());
    theDefer.resolve(sum);
    return theDefer.promise();
};