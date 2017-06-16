var http = require('http'); 
var MongoClient = require('mongodb').MongoClient; 
var url = "mongodb://localhost:27017/mydb";
var swig = require('swig');

MongoClient.connect(url, function(err, db) {
    if (err) throw err;

    http.createServer(function (req, res) {                 
        db.collection("things").find({}).toArray(function(err, result) { 
            if (err) throw err; 
            var markers = [];
	     for (var i = 0; i < 10; i++)
	     {
	     markers.push({
		  latA:   result[i].PointA_Lat,
		  lngA:   result[i].PointA_Lon,
		  latB:   result[i].PointB_Lat,
		  lngB:   result[i].PointB_Lon
	     });
	     }
	     res.writeHead(200, {'Content-Type': 'text/html'});

            var html = swig.renderFile('way.html', {markers: markers});

            res.end(html);
        });                
    }).listen(80);
    
});