/**
 * Created by Marshall on 2016/11/5.
 */

var InversePairsBlock = {
    InversePairs: function (array) {
        var temp = new Array(array.length);
        return this.InversePairsCore(array, 0, array.length - 1, temp);
    },
    /**
     * @param array
     * @param start
     * @param end
     * @param temp
     * @returns {number}
     * @constructor
     */
    InversePairsCore: function (array, start, end, temp) {
        var count = 0;
        if (start < end) {
            var mid = Math.floor((start + end) / 2);
            count += this.InversePairsCore(array, start, mid, temp);  //前半段逆序数
            count += this.InversePairsCore(array, mid + 1, end, temp);  //后半段逆序数
            count += this.MergeArray(array, start, mid, end, temp);  //归并后整段逆序数
        }
        return count;
    },
    /**
     * @param array
     * @param start
     * @param mid
     * @param end
     * @param temp
     * @returns {number}
     * @constructor
     */
    MergeArray: function (array, start, mid, end, temp) {
        var i = start, j = mid + 1, m = mid, n = end, k = 0, count = 0;
        while (i <= m && j <= n) {
            if (array[i] > array[j]) {
                temp[k++] = array[j++];
                count += mid - i + 1;
            } else {
                temp[k++] = array[i++];
            }
        }
        while (i <= m) temp[k++] = array[i++];
        while (j <= n) temp[k++] = array[j++];
        for (var ii = 0; ii < k; ii++) array[start + ii] = temp[ii];
        return count;
    }
};
function randomArrayWithEvenInversePairs(length) {
    var i, temp;
    length = typeof(length) === 'undefined' ? (16 - 1) : length;
    var arr = [], tempArr = [];
    for (i = 0; i < length; i++) {
        arr[i] = i;
    }
    arr.sort(function () {
        return 0.5 - Math.random()
    });
    for (i = 0; i < arr.length; i++) tempArr[i] = arr[i];
    if (InversePairsBlock.InversePairs(tempArr) % 2 == 1) {
        for (i = 0; i < arr.length; i++) {
            var flag = 0;
            for (var j = i + 1; j < arr.length; j++) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
    }
    return arr;
}

$(function () {
    var fragmentsList = $('.fragment');
    var blankDiv = $('#blank'), bgImageDiv = $('#bg-image'), statusDiv = $("#statusDiv > *").hide();
    var blankPosition = [3, 3], gameStart = false;
    var imageCounter = {
        counter: 0,
        getCounter: function () {
            return this.counter % 3;
        },
        count: function () {
            return ++this.counter % 3;
        }
    };

    /**
     * @param targetFrag
     * @returns {*}
     * @constructor
     */
    function BlankNeighborNo(targetFrag) {
        if (targetFrag.fragPosition[0] - 1 == blankPosition[0] && targetFrag.fragPosition[1] == blankPosition[1]) return [-1, 0];
        if (targetFrag.fragPosition[1] + 1 == blankPosition[1] && targetFrag.fragPosition[0] == blankPosition[0]) return [0, 1];
        if (targetFrag.fragPosition[0] + 1 == blankPosition[0] && targetFrag.fragPosition[1] == blankPosition[1]) return [1, 0];
        if (targetFrag.fragPosition[1] - 1 == blankPosition[1] && targetFrag.fragPosition[0] == blankPosition[0]) return [0, -1];
        return [0, 0];
    }
    function checkAndShowWin() {
        if (_.takeWhile(_.take(fragmentsList, 15), function (oneFrag) {
                return (oneFrag.fragPosition.toString() == oneFrag.expectedPosition.toString());
            }).length == 15) {
            gameStart = false;
            blankDiv.attr('id', 'frag-15');
            fragmentsList.removeClass('frag-border');
            statusDiv.fadeIn();
        }
    }
    function resetFrags() {
        _(fragmentsList).forEach(function (singleFrag) {
            $(singleFrag).removeClass("row-" + singleFrag.fragPosition[0].toString()).removeClass("col-" + singleFrag.fragPosition[1].toString());
            singleFrag.fragPosition = singleFrag.expectedPosition;
            $(singleFrag).addClass("row-" + singleFrag.fragPosition[0].toString()).addClass("col-" + singleFrag.fragPosition[1].toString());
        }).value();
    }
    function shuffleFrags() {
        var randomArr = randomArrayWithEvenInversePairs(15);
        _(_.take(fragmentsList, 15)).forEach(function (singleFrag) {
            $(singleFrag).removeClass("row-" + singleFrag.fragPosition[0].toString()).removeClass("col-" + singleFrag.fragPosition[1].toString());
            singleFrag.fragPosition = [Math.floor(randomArr[_.indexOf(fragmentsList, singleFrag)]/4), randomArr[_.indexOf(fragmentsList, singleFrag)]%4];
            $(singleFrag).addClass("row-" + singleFrag.fragPosition[0].toString()).addClass("col-" + singleFrag.fragPosition[1].toString());
        }).value();
        blankDiv.addClass('row-3').addClass('col-3');
    }

    bgImageDiv.addClass('frag-0');
    fragmentsList.addClass('frag-0');
    _.chain(fragmentsList).forEach(function (singleFrag) {
        var i = _.indexOf(fragmentsList, singleFrag);
        singleFrag.expectedPosition = [Math.floor(i / 4), (i % 4)];
        singleFrag.fragPosition = singleFrag.expectedPosition;
    }).value();
    resetFrags();

    fragmentsList.click(function () {
        if (!gameStart) return; // do nothing if game not start
        var moveAttempt = BlankNeighborNo(this);
        if (moveAttempt.toString() == [0, 0].toString()) return; // do nothing if there isn't a blank nearby
        $(this).removeClass("row-" + this.fragPosition[0].toString()).removeClass("col-" + this.fragPosition[1].toString());
        $(this).addClass("row-" + (this.fragPosition[0] += moveAttempt[0]).toString()).addClass("col-" + (this.fragPosition[1] += moveAttempt[1]).toString());
        blankPosition[0] -= moveAttempt[0];
        blankPosition[1] -= moveAttempt[1];
        checkAndShowWin();
    });

    $("#restart").click(function (event) {
        statusDiv.fadeOut();
        blankDiv.attr('id', 'blank');
        gameStart = true;
        fragmentsList.addClass('frag-border');
        shuffleFrags();
        blankPosition = [3, 3];
        if (event.target.innerHTML == "开始") event.target.innerHTML = "重新开始";
    });

    $("#changeImage").click(function () {
        if (!gameStart) {
            var tmpCounter = imageCounter.getCounter();
            var tmpNewCounter = imageCounter.count();
            fragmentsList.removeClass('frag-' + tmpCounter.toString()).addClass('frag-' + tmpNewCounter.toString());
            bgImageDiv.removeClass("frag-" + tmpCounter.toString()).addClass("frag-" + tmpNewCounter.toString());
        }
    });

    $("#revert").click(function () {
        if (gameStart) {
            resetFrags();
            gameStart = false;
            $("#restart").html("开始");
        }
    });
});
