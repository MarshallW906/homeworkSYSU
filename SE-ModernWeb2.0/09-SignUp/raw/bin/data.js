var fs = require("fs");
var _ = require("../view/css_js/lodash.3.10.1.js");

function readFileData(fileName) {
    fileName = (fileName == undefined) ? 'db.json' : ((typeof fileName) == 'string' ? fileName : 'db.json');
    var retJSONData;
    try {
        retJSONData = fs.readFileSync(fileName, 'utf-8');
        return JSON.parse(retJSONData);
    } catch (e) {
        console.log(e.message);
        fs.writeFileSync(fileName, "[]", 'utf-8');
        return [];
    }
    // return a Array of JSON objects
}
function storeDataToFile(fileName, dataJSON) {
    // receive a Object of JSON obj Array and write to File
    fileName = (fileName == undefined) ? 'db.json' : ((typeof fileName) == 'string' ? fileName : 'db.json');
    fs.writeFileSync(fileName, JSON.stringify(dataJSON), 'utf-8');
}
function insertNewSingleInfo(dataArr, newEntry) {
    //receive an Array of JSON Object, and a single JSON Object
    return dataArr.push(newEntry);
    // return dataArr.NewLength
}
function isDuplicated(dataArr, newEntry, duplicatedKeys) {
    var duplicatedEntry = null;
    _.chain(dataArr).forEach(function (eachObj) {
        if (duplicatedEntry != null) return;
        for (var key in eachObj) {
            if (eachObj[key] == newEntry[key]) {
                duplicatedEntry = eachObj;
                duplicatedKeys.push(key.toString());
            }
        }
    }).value();
    return duplicatedEntry;
}

// for exports
function insertNewUser(newUserEntry) {
    var dbName = 'db.json';
    var dataJSONArr = readFileData(dbName);
    // console.log(dataJSONArr);
    var dupKey = [];
    var dupJSONObj = isDuplicated(dataJSONArr, newUserEntry, dupKey), duplicated = {};

    if (dupJSONObj == null) {
        insertNewSingleInfo(dataJSONArr, newUserEntry);
        storeDataToFile(dbName, dataJSONArr);
        return null;
    } else {
        _.chain(dupKey).forEach(function (singleKey) {
            duplicated[singleKey] = dupJSONObj[singleKey];
        }).value();
        return duplicated;
    }
}
function queryUsername(usernameToSearch) {
    var dbName = 'db.json';
    var dataJSONArr = readFileData(dbName);
    var ret = _.compact(_.chain(dataJSONArr).map(function (singleObj) {
        if (singleObj['username'] == usernameToSearch) return singleObj;
        else return undefined;
    }).value());
    return ret[0];
}

function test() {
    var newJSONEntry = {
        username: "12d345",
        number: "434fdsafwde3",
        tel: "76fawesf54",
        email: " fwefwaeklfwe@fdsafwde"
    };

    var b = readFileData('db.json');
    console.log("b: " + b);

    console.log(typeof b);
    if (b instanceof Array) console.log("b is an Array");
    storeDataToFile('db.json', JSON.stringify(b));

    insertNewSingleInfo(b, newJSONEntry);

    if (isDuplicated(b, newJSONEntry)) console.log("Duplicated test good");
    else console.log("not Duplicated");
    if (insertNewUser(newJSONEntry)) console.log("insert success");
    else console.log("not success");
    queryUsername("12345");

}

exports.insertNewUserInfo = insertNewUser;
exports.queryUsername = queryUsername;
