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
    var text = $this.val();
    var isGood = regex.test(text);
    if (isGood) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        // $this.parent().find('.warning').addClass('has-warning').html("Username只允许6-18位字母数字，且必须以字母开头");
        if (/^[0-9]/.test(text)) {
            $this.parent().find('.warning').addClass('has-warning').html("开头必须为大小写字母");
        } else if (text.length < 6 || text.length > 18) {
            $this.parent().find('.warning').addClass('has-warning').html("长度为6-18字符");
        } else {
            $this.parent().find('.warning').addClass('has-warning').html("只能包含大小写字母及数字");
        }

    }
}
function chksynNumber() {
    var $this = $(this);
    var regex = /^[1-9]\d{7}$/;
    var text = $this.val();
    var isGood = regex.test(text);
    if (isGood) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        $this.parent().find('.warning').addClass('has-warning').html("学号只可为8位数字");
    }
}
function chksynTel() {
    var $this = $(this);
    var regex = /^[1-9]\d{10}$/;
    var text = $this.val();
    var isGood = regex.test(text);
    if (isGood) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        $this.parent().find('.warning').addClass('has-warning').html("电话只可为11位数字");
    }
}
function chksynEmail() {
    var $this = $(this);
    var regex = /^(\w)+(\.\w+)*@(\w)+((\.\w{2,4}){1,3})$/;
    var text = $this.val();
    var isGood = regex.test(text);
    if (isGood) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        $this.parent().find('.warning').addClass('has-warning').html("请输入正确格式的邮箱地址");
    }
}

function resetEvents() {
    $('.warning').html("").removeClass('has-warning');
}

function checkAll() {
    var $inputText = $(":input[type='text']").blur();
    if (_.compact(_.chain($('.warning')).map(function (singleWarn) {
            return $(singleWarn).hasClass('has-warning') ? true : false;
        }).value()).length !== 0)
        return false;
    else return true;
}