/**
 * Created by Marshall on 2016/11/10.
 */
var http = require('http');
var url = require('url');
var router = require('./router.js');

function startServer(port) {
    function onRequest(request, response) {
        var upData = "", requestUrlJSON = {}, pathname = "";
        requestUrlJSON = url.parse(request.url, true);
        // console.log(requestUrlJSON);
        request.on('data', function (dataChunk) {
            upData += dataChunk;
        });
        request.on('end', function () {
            require('./router.js').router(request.method, response, requestUrlJSON, upData);
        });

    }
    http.createServer(onRequest).listen(port);
    console.log("Server Listening at http://127.0.0.1:" + port.toString());
}

exports.startServer = startServer;