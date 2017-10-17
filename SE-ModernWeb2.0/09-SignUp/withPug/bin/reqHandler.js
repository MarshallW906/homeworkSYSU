/**
 * Created by Marshall on 2016/11/10.
 */

var path = require('path');
var fs = require('fs');
var pug = require('pug');
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

    var reveal_pug = pug.compileFile(viewPath + 'pug/userInfo.pug', {});
    var revealHTML = reveal_pug(userToReveal);
    if (revealHTML.length !== 0) {
        response.writeHead(200, {"Content-Type": "text/html"});
        response.write(revealHTML);
        response.end();
    }
}

function revealRegisterPage(response) {
    var res_pug = pug.compileFile(viewPath + 'pug/index.pug', {});
    var res_html = res_pug({warnings : {hasWarning : false}});
    if (res_html.length !== 0) {
        response.writeHead(200, {"Content-Type": "text/html"});
        response.write(res_html);
        response.end();
    } else {
        response.writeHead(404);
    }
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
        var res_pug = pug.compileFile(viewPath + 'pug/index.pug', {});
        console.log(warnings);
        var res_html = res_pug({warningMsg: warnings});
        if (res_html.length !== 0) {
            response.writeHead(200, {"Content-Type": "text/html"});
            response.write(res_html);
            response.end();
        }

        // show warnings in the Register page
    }
    // revealUserInfo(response, postJSONData.username); should use 302 re-direct
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
    }
    if (ext === '.ico') {
        response.writeHead(404);
        response.end();
    } else if (ext !== '.html' && ext !== '') {
        fs.readFile(viewPath + pathname.slice(1).toString(), 'binary', function (err, data) {
            if (err) {
                response.writeHead(404, {'Content-Type': MIMEobj[ext]});
                response.end(err);
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