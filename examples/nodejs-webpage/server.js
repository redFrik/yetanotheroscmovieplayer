var ip= '127.0.0.1';
var port= 61000;
var http= require('http');
var socketio= require('socket.io');
var fs= require('fs');
var udp= require('dgram');
var osc= require('osc-min');
var http_server= http.createServer(function(req, res) {
    console.log('------------------');
    console.log(req.headers);
    fs.readFile(__dirname+'/index.html', function(err, data) {
        if(err) {
            res.writeHead(500);
            return res.end('Error loading index.html');
        }
        res.writeHead(200);
        res.end(data);
    });
});
var io= socketio(http_server);
var sck= udp.createSocket('udp4');
var sendOsc= function(adr, args) {
    var msg= {address: adr, args: args};
    var buf= osc.toBuffer(msg);
    sck.send(buf, 0, buf.length, port, ip);
}
io.on('connection', function(socket) {
    socket.on('start', function(data) {
        sendOsc('/start', [data.fileName, parseInt(data.fadeIn.trim()||0), parseInt(data.loopMode.trim()||0)]);
    });
    socket.on('stop', function(data) {
        sendOsc('/stop', [parseInt(data.fadeOut.trim()||0)]);
    });
    socket.on('info', function(data) {
        sendOsc('/info', []);
    });
    socket.on('fps', function(data) {
        sendOsc('/fps', [parseFloat(data.fps.trim()||60)]);
    });
    socket.on('speed', function(data) {
        sendOsc('/speed', [parseFloat(data.speed.trim()||1)]);
    });
    socket.on('mode', function(data) {
        sendOsc('/mode', [parseInt(data.mode.trim()||0)]);
    });
    socket.on('exit', function(data) {
        sendOsc('/exit', []);
    });
});
http_server.listen(8080);
console.log('open a webbrowser and go to 127.0.0.1:8080');
