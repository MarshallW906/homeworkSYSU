/**
 * Created by Marshall on 2016/10/22.
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
        var i = start;
        var j = mid + 1;
        var m = mid;
        var n = end;
        var k = 0;
        var count = 0;
        while (i <= m && j <= n) {
            if (array[i] > array[j]) {
                temp[k++] = array[j++];
                count += mid - i + 1;
            } else {
                temp[k++] = array[i++];
            }
        }
        while (i <= m) {
            temp[k++] = array[i++];
        }
        while (j <= n) {
            temp[k++] = array[j++];
        }
        for (var ii = 0; ii < k; ii++) {
            array[start + ii] = temp[ii];
        }
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

window.onload = function () {
    var fragmentsList = document.getElementsByClassName('fragment');
    var startButton = document.getElementById('restart');
    var revertButton = document.getElementById('revert');
    var imageButton = document.getElementById('changeImage');
    var blankDiv = document.getElementById('blank');
    var statusDiv = document.getElementById('statusDiv');
    var bgImageDiv = document.getElementById('bg-image');
    var blankPosition = [3, 3];
    var gameStart = false;

    var imageCounter = {
        counter: 0,
        getCounter: function () {
            return this.counter % 3;
        },
        count: function () {
            return ++this.counter % 3;
        }
    }

    /**
     * @return {number}
     */
    function BlankNeighborNo(targetFrag) {
        if (targetFrag.fragPosition[0] - 1 == blankPosition[0] && targetFrag.fragPosition[1] == blankPosition[1]) {
            // blank is upside : 1
            return 1;
        }
        if (targetFrag.fragPosition[1] + 1 == blankPosition[1] && targetFrag.fragPosition[0] == blankPosition[0]) {
            // blank is at the right : 2
            return 2;
        }
        if (targetFrag.fragPosition[0] + 1 == blankPosition[0] && targetFrag.fragPosition[1] == blankPosition[1]) {
            // blank is downside : 3
            return 3;
        }
        if (targetFrag.fragPosition[1] - 1 == blankPosition[1] && targetFrag.fragPosition[0] == blankPosition[0]) {
            // blank is at the left : 4
            return 4;
        }
        return 0;
    }

    /**
     * @returns {boolean}
     */
    function checkWin() {
        for (var i = 0; i < fragmentsList.length; i++) {
            if (fragmentsList[i].fragPosition.toString() != fragmentsList[i].expectedPosition.toString())
                return false;
        }
        return true;
    }

    bgImageDiv.classList.add('frag-0');
    for (var i = 0; i < fragmentsList.length; i++) {
        const rowStr = "row-";
        const colStr = "col-";
        fragmentsList[i].classList.add(rowStr + Math.floor(i / 4).toString());
        fragmentsList[i].classList.add(colStr + (i % 4).toString());
        fragmentsList[i].classList.add("frag-0");
        fragmentsList[i].expectedPosition = [Math.floor(i / 4), (i % 4)];
        fragmentsList[i].fragPosition = fragmentsList[i].expectedPosition;

        fragmentsList[i].onclick = function (event) {
            if (gameStart) {
                var tmpRow = "";
                var tmpCol = "";
                switch (BlankNeighborNo(event.target)) {
                    case 1:
                        // move up, blank move down
                        tmpRow = rowStr + event.target.fragPosition[0].toString();
                        event.target.classList.remove(tmpRow);
                        tmpRow = rowStr + (event.target.fragPosition[0] - 1).toString();
                        event.target.classList.add(tmpRow);
                        event.target.fragPosition[0] -= 1;
                        blankPosition[0] += 1;
                        break;
                    case 2:
                        // move right, blank move left
                        tmpCol = colStr + event.target.fragPosition[1].toString();
                        event.target.classList.remove(tmpCol);
                        tmpCol = colStr + (event.target.fragPosition[1] + 1).toString();
                        event.target.classList.add(tmpCol);
                        event.target.fragPosition[1] += 1;
                        blankPosition[1] -= 1;
                        break;
                    case 3:
                        // move down, blank move up
                        tmpRow = rowStr + event.target.fragPosition[0].toString();
                        event.target.classList.remove(tmpRow);
                        tmpRow = rowStr + (event.target.fragPosition[0] + 1).toString();
                        event.target.classList.add(tmpRow);
                        event.target.fragPosition[0] += 1;
                        blankPosition[0] -= 1;
                        break;
                    case 4:
                        // move left, blank move right
                        tmpCol = colStr + event.target.fragPosition[1].toString();
                        event.target.classList.remove(tmpCol);
                        tmpCol = colStr + (event.target.fragPosition[1] - 1).toString();
                        event.target.classList.add(tmpCol);
                        event.target.fragPosition[1] -= 1;
                        blankPosition[1] += 1;
                        break;
                    case 0:
                    default:
                        break;
                }

                if (checkWin()) {
                    gameStart = false;
                    // show the No.15 frag
                    blankDiv.id = "frag-15";
                    // remove the border
                    for (var i = 0; i < fragmentsList.length; i++)
                        fragmentsList[i].classList.remove("frag-border");
                    // show YouWin
                    statusDiv.classList.remove("invisible");
                    statusDiv.classList.add("visible");
                }
            }
        }
    }

    startButton.onclick = function (event) {
        statusDiv.classList.add("invisible");
        statusDiv.classList.remove("visible");

        blankDiv.id = "blank";
        gameStart = true;

        var randomArr = randomArrayWithEvenInversePairs(15);
        for (var i = 0; i < fragmentsList.length; i++) {
            fragmentsList[i].classList.add("frag-border");
            var tmpRow, tmpCol;
            tmpRow = "row-" + fragmentsList[i].fragPosition[0].toString();
            tmpCol = "col-" + fragmentsList[i].fragPosition[1].toString();
            fragmentsList[i].classList.remove(tmpRow);
            fragmentsList[i].classList.remove(tmpCol);

            fragmentsList[i].fragPosition = [Math.floor(randomArr[i] / 4), randomArr[i] % 4];
            tmpRow = "row-" + fragmentsList[i].fragPosition[0].toString();
            tmpCol = "col-" + fragmentsList[i].fragPosition[1].toString();
            fragmentsList[i].classList.add(tmpRow);
            fragmentsList[i].classList.add(tmpCol);
        }
        blankPosition = [3, 3];
        if (event.target.innerHTML == "开始") event.target.innerHTML = "重新开始";
    };
    imageButton.onclick = function (event) {
        if (!gameStart) {
            var tmpCounter = imageCounter.getCounter();
            var tmpNewCounter = imageCounter.count();
            for (var i = 0; i < fragmentsList.length; i++) {
                fragmentsList[i].classList.remove("frag-" + tmpCounter.toString());
                fragmentsList[i].classList.add("frag-" + tmpNewCounter.toString());
            }
            bgImageDiv.classList.remove("frag-" + tmpCounter.toString());
            bgImageDiv.classList.add("frag-" + tmpNewCounter.toString());
        }
    };
    revertButton.onclick = function (event) {
        if (gameStart) {
            for (var i = 0; i < fragmentsList.length; i++) {
                var tmpRow, tmpCol;
                tmpRow = "row-" + fragmentsList[i].fragPosition[0].toString();
                tmpCol = "col-" + fragmentsList[i].fragPosition[1].toString();
                fragmentsList[i].classList.remove(tmpRow);
                fragmentsList[i].classList.remove(tmpCol);

                fragmentsList[i].fragPosition = fragmentsList[i].expectedPosition;
                tmpRow = "row-" + fragmentsList[i].fragPosition[0].toString();
                tmpCol = "col-" + fragmentsList[i].fragPosition[1].toString();
                fragmentsList[i].classList.add(tmpRow);
                fragmentsList[i].classList.add(tmpCol);
            }
            gameStart = false;
            startButton.innerHTML = "开始";
        }
    };
};

