var fs = require('fs');
var swig = require('swig');
var http = require('http');
var lat = 51.475;
var lng = -0.1;

http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    var html = swig.renderFile('index.html', {lat: lat, lng: lng});
    res.end(html);
}).listen(80);