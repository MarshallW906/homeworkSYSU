/**
 * Created by Marshall on 2016/11/10.
 */

var reqHandler = require('./reqHandler.js');

function router(method, response, requestUrlJSON, upData) {
    if (method === "GET") {
        console.log("router : GET");
        var usernameToQuery = requestUrlJSON.query.username;
        if (requestUrlJSON.pathname == "/") {
            if (usernameToQuery != null) {
                // reveal the InfoPage of username
                // reveal the register page if not exist
                console.log("router : reveal the InfoPage of username");
                reqHandler.revealUserInfo(response, usernameToQuery);
            } else {
                // reveal the register page
                console.log("router : reveal the register page")
                reqHandler.revealRegisterPage(response);
            }
        } else {
            // get the MIME data
            console.log("router : get MIME data");
            reqHandler.mimeData(response, requestUrlJSON.pathname);
        }

    } else {
        console.log("router : POST");
        // method === "POST"
        reqHandler.register(response, upData);
    }
}

exports.router = router;