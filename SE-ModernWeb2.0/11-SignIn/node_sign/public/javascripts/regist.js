/**
 * Created by Marshall on 2016/12/12.
 */

(function () {
    $(function () {
        let $message = $('#message');

        $(":input[name='username']").blur(chksynUsername);
        $(":input[name='number']").blur(chksynNumber);
        $(":input[name='tel']").blur(chksynTel);
        $(":input[name='email']").blur(chksynEmail);
        $("#password").blur(chkPassword);
        $("#password-again").blur(chkSamePassword);

        $(":input[type='reset']").click(resetEvents);
        let username = $("#username").focus();

        $("#loginBtn").click(function () {
            location.href = 'login';
        });

        $("#regist-form").submit(function () {
            if (!checkAll()) return false;

            let username = $(":input[name='username']").val();
            let password = $("#password").val();
            let number = $(":input[name='number']").val();
            let tel = $(":input[name='tel']").val();
            let email = $(":input[name='email']").val();

            let sha1_password = sha1(password);

            let data = {
                "uname": username,
                "upwd": sha1_password,
                "unum": number,
                "utel": tel,
                "uemail": email,
            };
            $.ajax({
                url: '/regist',
                type: 'post',
                data: data,
                timeout: 5000,
                success: function (data, status) {
                    if (status === 'success' && data.code !== 200) {
                        $message.text(data.msg);
                    } else if (status === 'success' && data.code === 200) {
                        $message.text(data.msg + '页面将在3秒后跳转');
                        let timer = setTimeout(function () {
                            location.href = 'home';
                        }, 3000);
                    }
                },
                error: function (data, err) {
                    alert(err);
                }
            });
            return false;
        });
    });
})();

function chksynUsername() {
    let $this = $(this);
    let regex = /^[a-zA-Z][0-9a-zA-Z_]{5,17}$/;
    let text = $this.val();
    if (regex.test(text)) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
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
    let $this = $(this);
    let regex = /^[1-9]\d{7}$/;
    let text = $this.val();
    if (regex.test(text)) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        if (text === "") {
            $this.parent().find('.warning').addClass('has-warning').html("请输入学号");
        } else {
            $this.parent().find('.warning').addClass('has-warning').html("学号只可为8位数字");
        }
    }
}
function chksynTel() {
    let $this = $(this);
    let regex = /^[1-9]\d{10}$/;
    let text = $this.val();
    if (regex.test(text)) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        if (text === "")
            $this.parent().find('.warning').addClass('has-warning').html("请输入电话号码");
        else
            $this.parent().find('.warning').addClass('has-warning').html("电话只可为11位数字");
    }
}
function chksynEmail() {
    let $this = $(this);
    let regex = /^(\w)+(\.\w+)*@(\w)+((\.\w{2,4}){1,3})$/;
    let text = $this.val();
    if (regex.test(text)) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        if (text === "")
            $this.parent().find('.warning').addClass('has-warning').html("请输入邮箱地址");
        else
            $this.parent().find('.warning').addClass('has-warning').html("请输入正确格式的邮箱地址");
    }
}

function resetEvents() {
    $('.warning').html("").removeClass('has-warning');
}

function checkAll() {
    $(":input[type='text']").blur();
    $(":input[type='password']").blur();
    if (_.compact(_.chain($('.warning')).map(function (singleWarn) {
            return !!$(singleWarn).hasClass('has-warning');
        }).value()).length !== 0)
        return false;
    else return true;
}
function chkPassword() {
    let $this = $(this);
    let regex = /^[0-9a-zA-Z_-]{6,12}$/;
    let text = $this.val();
    if (regex.test(text)) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        if (text === "")
            $this.parent().find('.warning').addClass('has-warning').html("请设置密码");
        else
            $this.parent().find('.warning').addClass('has-warning').html("密码为6~12位数字、大小写字母、中划线、下划线");
    }
}
function chkSamePassword() {
    let $this = $(this);
    if ($this.val() == $('#password').val()) {
        $this.parent().find('.warning').removeClass('has-warning').html("");
    } else {
        if ($this.val() === "")
            $this.parent().find('.warning').addClass('has-warning').html("请再次输入密码");
        else
            $this.parent().find('.warning').addClass('has-warning').html("两次请输入相同的密码");
    }
}