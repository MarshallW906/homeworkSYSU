$(function () {
    let $message = $('#message');
    $("#registHrefBtn").click(function () {
        location.href = 'regist';
    });
    let username = $("#username").focus();
    $("#login-form").submit(function () {
        let username = $("#username").val();
        if (username === "") {
            $message.text("请输入用户名");
            return false;
        }
        let password = $("#password").val();
        let sha1_password = sha1(password);
        if (password === "") {
            $message.text("请输入密码");
            return false;
        }
        let data = {
            "uname": username,
            "upwd": sha1_password
        };
        $.ajax({
            url: '/login',
            type: 'post',
            data: data,
            timeout: 1000,
            success: function (data, status) {
                if (status === 'success' && data.code !== 200) {
                    $message.text(data.msg);
                } else if (status === 'success' && data.code === 200) {
                    location.href = 'home';
                    $message.text("");
                }
            },
            error: function (data, status) {
                if (status == 'error') {
                    alert(status);
                }
            }
        });
        return false;
    });
    /*
    $("#loginBtn").click(function () {
        let username = $("#username").val();
        if (username === "") {
            $message.text("请输入用户名");
            return false;
        }
        let password = $("#password").val();
        let sha1_password = sha1(password);
        if (password === "") {
            $message.text("请输入密码");
            return false;
        }
        let data = {
            "uname": username,
            "upwd": sha1_password
        };
        $.ajax({
            url: '/login',
            type: 'post',
            data: data,
            timeout: 1000,
            success: function (data, status) {
                if (status === 'success' && data.code !== 200) {
                    $message.text(data.msg);
                } else if (status === 'success' && data.code === 200) {
                    location.href = 'home';
                    $message.text("");
                }
            },
            error: function (data, status) {
                if (status == 'error') {
                    alert(status);
                }
            }
        });
    });
    */

});