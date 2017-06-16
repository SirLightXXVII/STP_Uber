var fs = require('fs'); 
var http = require('http'); 

http.createServer(function (req, res) { 
res.writeHead(200, {'Content-Type': 'text/html'}); 
fs.createReadStream('index.html').pipe(res); 
}).listen(80);