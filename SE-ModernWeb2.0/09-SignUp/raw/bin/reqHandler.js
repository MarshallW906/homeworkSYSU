/**
 * Created by Marshall on 2016/11/10.
 */

var path = require('path');
var fs = require('fs');
var query = require('querystring');

var _ = require('../view/css_js/lodash.3.10.1.js');

var viewPath = './view/';
var jsonDataDb = require('./data.js');

function generateWarning(duplicatedInfo) {
    var warnings = "Duplicated : ";
    if (duplicatedInfo == undefined) return warnings;
    for (var key in duplicatedInfo) {
        warnings += key.toString() + " : " + duplicatedInfo[key].toString() + " ";
    }
    return warnings;
}

function revealUserInfo(response, usernameToQuery) {
    var userToReveal = jsonDataDb.queryUsername(usernameToQuery);
    console.log("userToReveal : ");
    console.log(userToReveal);
    if (userToReveal == undefined)
        return revealRegisterPage(response);

    var scriptToWrite = "<script>$(function() {" +
            "$('#username').html(\"" + userToReveal.username.toString() + "\");" +
            "$('#stuNo').html(\"" + userToReveal.number.toString() + "\");" +
            "$('#tel').html(\"" + userToReveal.tel.toString() + "\");" +
            "$('#email').html(\"" + userToReveal.email.toString() + "\");" +
            "});</script>";
    var revealHTML = fs.readFileSync(viewPath + 'html_x/userInfo.html', 'utf-8');
    if (revealHTML.length !== 0) {
        response.writeHead(200, {"Content-Type": "text/html"});
        response.write(revealHTML);
        response.write(scriptToWrite);
        response.end();
    } else {
        response.writeHead(404);
        response.end();
    }
}

function revealRegisterPage(response) {
    fs.readFile(viewPath + 'html_x/index.html', 'utf-8', function (err, data) {
        if (err) {
            response.writeHead(404, {"Content-Type": "text/html"});
            response.end(err.toString());
        } else {
            response.writeHead(200, {"Content-Type": "text/html"});
            response.end(data);
        }
    });
}

function register(response, newUserInfoData) {
    // newUserInfoData needs parse to JSON
    // store JSON-data to file
    var postJSONData = query.parse(newUserInfoData);
    // Duplicated check
    var dupJSONObj = jsonDataDb.insertNewUserInfo(postJSONData);
    if (dupJSONObj == null) {
        console.log("insert succeeded");
        response.writeHead(302, {'Location': ('http://127.0.0.1:8000/?username=' + postJSONData.username)});
        response.end();
    } else {
        console.log("not succeeded, maybe duplicated");
        console.log(dupJSONObj);
        var warnings = generateWarning(dupJSONObj);
        console.log(warnings);

        var scriptsToWrite = "<script>" +
                "$('#warnings').html(\"" + warnings + "\")" +
                "</script>";
        var revealHTML = fs.readFileSync(viewPath + 'html_x/index.html', 'utf-8');
        if (revealHTML.length !== 0) {
            response.writeHead(200, {"Content-Type": "text/html"});
            response.write(revealHTML);
            response.write(scriptsToWrite);
            response.end();
        }
    }
}

function mimeData(response, pathname) {
    // readFile and response.write(data);
    var ext = path.extname(pathname);
    console.log("MIME : GET " + pathname);
    var MIMEobj = {
        '.html': 'text/html',
        '.css': 'text/css',
        '.js': 'application/javascript',
        '.png': 'image/png',
        '.gif': 'image/gif'
    };
    if (ext === '.ico') {
        response.writeHead(404);
        response.end();
    } else if (ext !== '.html' && ext !== '') {
        console.log("path : " + pathname.slice(1).toString());
        fs.readFile(pathname.slice(1).toString(), 'binary', function (err, data) {
            if (err) {
                response.writeHead(404, {'Content-Type': MIMEobj[ext]});
                response.end(err.toString());
            } else {
                response.writeHead(200, {'Content-Type': MIMEobj[ext]});
                response.write(data, 'binary');
            }
            response.end();
        });
    } else {
        revealRegisterPage(response);
    }
}

exports.revealUserInfo = revealUserInfo;
exports.revealRegisterPage = revealRegisterPage;
exports.register = register;
exports.mimeData = mimeData;