var http = require('http'); 
var MongoClient = require('mongodb').MongoClient; 
var url = "mongodb://localhost:27017/mydb"; 

MongoClient.connect(url, function(err, db) {
    if (err) throw err;

    http.createServer(function (req, res) {                      
        db.collection("mydb").find({}).toArray(function(err, result) { 
            if (err) throw err; 
            
            res.writeHead(200, {'Content-Type': 'text/plain'}); 
            res.end(JSON.stringify(result)); 
        });

        db.close();        
    }).listen(80);
    
});