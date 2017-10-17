function addTriangle($target) {
    if (!$target.find("triangleMark").length)
        $target.append('<span class="triangleMark"></span>');
}
function bindToTable($target) {
    $target.click(sortTable());
}

function sortTable() {
    var last_col = -1;
    var asc = -1;
    return function () {
        var $this = $(this);
        var col_num = $this.parent().children().index($this);
        var $table = $this.parents("table");
        var $trs = $table.find("tbody").find("tr");
        if ($table.find("thead").length == 0) Array.prototype.shift.call($trs);
        $trs = $trs.detach();

        Array.prototype.sort.call($trs, function (first, second) {
            var firstHTML = $(first).children().eq(col_num).html();
            var secondHTML = $(second).children().eq(col_num).html();
            if (firstHTML < secondHTML) {
                return (last_col == -1 || last_col !== col_num) ? asc : -asc;
            } else if (firstHTML > secondHTML) {
                return (last_col == -1 || last_col !== col_num) ? -asc : asc;
            } else {
                return 0;
            }
        });

        if (last_col == col_num) asc *= -1;
        last_col = col_num;
        $table.append($trs);

        $table.find(".triangleMark").removeClass("ascending").removeClass("descending");
        $this.parent().children('th').removeClass('th-sorted').addClass('th-normal');
        $this.addClass('th-sorted').find(".triangleMark").addClass((asc == -1) ? "ascending" : "descending");
    }
}

$(function () {
    var $ths = $("thead th").addClass('th-normal');
    addTriangle($ths);
    bindToTable($ths);
});
