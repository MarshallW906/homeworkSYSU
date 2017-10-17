/**
 * Created by Marshall on 2016/11/11.
 */

(function () {
    $(function () {
        $(":input[name='username']").blur(chksynUsername);
        $(":input[name='number']").blur(chksynNumber);
        $(":input[name='tel']").blur(chksynTel);
        $(":input[name='email']").blur(chksynEmail);

        $(":input[type='reset']").click(resetEvents);
        $(":input[type='submit']").click(checkAll); // return false to block the submit, true to pass
    });
})();

function chksynUsername() {
    var $this = $(this);
    var regex = /^[a-zA-Z][0-9a-zA-Z_]{5,17}$/;
    var isGood = regex.test($this.val());
    if (isGood) {
        $this.removeClass('warning');
    } else {
        $this.addClass('warning');
    }
}
function chksynNumber() {
    var $this = $(this);
    var regex = /^[1-9]\d{7}$/;
    var isGood = regex.test($this.val());
    if (isGood) {
        $this.removeClass('warning');
    } else {
        $this.addClass('warning');
    }
}
function chksynTel() {
    var $this = $(this);
    var regex = /^[1-9]\d{10}$/;
    var isGood = regex.test($this.val());
    if (isGood) {
        $this.removeClass('warning');
    } else {
        $this.addClass('warning');
    }
}
function chksynEmail() {
    var $this = $(this);
    var regex = /^(\w)+(\.\w+)*@(\w)+((\.\w{2,4}){1,3})$/;
    var isGood = regex.test($this.val());
    if (isGood) {
        $this.removeClass('warning');
    } else {
        $this.addClass('warning');
    }
}

function resetEvents() {
    $(':input').removeClass('warning');
}

function checkAll() {
    var $inputText = $(":input[type='text']").blur();
    if (_.compact(_.chain($inputText).map(function (singleInput) {
            return $(singleInput).hasClass('warning') ? true : false;
        }).value()).length !== 0)
        return false;
    else return true;
}