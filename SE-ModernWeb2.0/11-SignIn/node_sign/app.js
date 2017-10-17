let express = require('express');
let path = require('path');
let favicon = require('serve-favicon');
let logger = require('morgan');
let cookieParser = require('cookie-parser');
let bodyParser = require('body-parser');

let multer = require('multer');
let mongoose = require('mongoose');
let session = require('express-session');


let routes = require('./routes/index');

let app = express();

// MongoDB : Mongoose
global.dbHandle = require('./database/dbHandle');
global.db = mongoose.connect("mongodb://localhost:27017/nodedb");

app.use(session({
    secret: 'secret',
    cookie: {
        maxAge: 1000 * 60 * 30
    },
    resave: true,
    saveUninitialized: true
}));


// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.engine("html", require("ejs").__express);
app.set('view engine', 'html');

app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));


app.use(function (req, res, next) {
    res.locals.user = req.session.user;
    let err = req.session.error;
    delete req.session.error;
    res.locals.message = "";
    if (err) {
        res.locals.message = '<div class="alert alert-danger" style="margin-bottom:20px;color:red;">' + err + '</div>';
    }
    next();
});

// set routes
app.use('/', routes);
app.use('/login', routes);
app.use('/register', routes);
app.use('/home', routes);
app.use("/logout", routes);


// catch 404 and forward to error handler
app.use(function (req, res, next) {
    let err = new Error('Not Found');
    err.status = 404;
    next(err);
});

// error handlers

// development error handler
// will print stacktrace

if (app.get('env') === 'development') {
    app.use(function (err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}


// production error handler
// no stacktraces leaked to user
app.use(function (err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});


module.exports = app;
