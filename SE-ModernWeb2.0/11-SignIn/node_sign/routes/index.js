let express = require('express');
let router = express.Router();

router.get('/', function (req, res, next) {
    if (!req.session.user) {
        res.redirect("/login");
    } else if (req.query.username == null) {
        res.render('home', {title: '用户首页', warning: '您已登录'});
    } else if (req.query.username !== req.session.user.name) {
        res.render('home', {title: '用户首页', warning: '只能访问自己的数据'});
    } else {
        res.render('home', {title: '用户首页', warning: '登录成功'});
    }
});

router.route("/login").get(function (req, res) {
    res.render("login", {title: '用户登录'});
}).post(function (req, res) {
    let User = global.dbHandle.getModel('user');
    let uname = req.body.uname;
    User.findOne({name: uname}, function (err, doc) {
        if (err) {
            res.send({
                code: 500,
                msg: '系统错误'
            });
        } else if (!doc) {
            res.send({
                code: 404,
                msg: '用户名不存在'
            });
        } else {
            if (req.body.upwd != doc.password) {
                res.send({
                    code: 404,
                    msg: '密码错误'
                });
            } else {
                req.session.user = doc;
                res.send({
                    code: 200,
                    msg: '成功'
                });
            }
        }
    });
});

router.route("/regist").get(function (req, res) {
    res.render("regist", {title: 'User register'});
}).post(function (req, res) {
    let User = global.dbHandle.getModel('user');
    let newUserEntry = {
        name: req.body.uname,
        password: req.body.upwd,
        number: req.body.unum,
        tel: req.body.utel,
        email: req.body.uemail
    };

    let errMsg = "Duplicated : ";
    User.findOne({$or: [{name: newUserEntry.name}, {number: newUserEntry.number}, {tel: newUserEntry.tel}, {email: newUserEntry.email}]}, (err, doc) => {
        if (err) {
            res.send({
                code: 500,
                msg: err.message
            });
        }
        if (doc) {
            // Something Duplicated
            for (let entry in newUserEntry) {
                if (entry !== "password" && entry !== null && doc[entry] === newUserEntry[entry]) {
                    errMsg += entry.toString() + " ";
                }
            }
            res.send({
                code: 500,
                msg: errMsg
            });
        } else {
            User.create(newUserEntry, function (err, doc) {
                if (err) {
                    res.send({
                        code: 500,
                        msg: '用户创建失败, 系统错误, 请稍后再试'
                    });
                } else {
                    // User Create Succeeded
                    req.session.user = doc;
                    res.send({
                        code: 200,
                        msg: '用户创建成功'
                    });
                }
            });
        }
    });
});

router.get("/home", function (req, res) {
    if (!req.session.user) {
        res.redirect("/login");
    } else {
        res.render("home", {title: 'Home', warning: '登录成功'});
    }

});

router.get("/logout", function (req, res) {
    req.session.user = null;
    req.session.error = null;
    res.redirect("/");
});

module.exports = router;
