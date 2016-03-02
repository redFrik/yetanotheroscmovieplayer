var udp= require('dgram');
var osc= require('osc-min');
var sendOsc= function(ip, port, msg) {
    var sck= udp.createSocket('udp4');
    var buf= osc.toBuffer(msg);
    sck.send(buf, 0, buf.length, port, ip, function() {
        sck.close();
    });
}

sendOsc('127.0.0.1', 61000, {
    address: '/stop',
    args: [100]  //fade out and stop over 100 frames
});
