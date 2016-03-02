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
    address: '/start',
    args: ['yetanotherdemo.mov', 200, 1]  //fade in movie over 200 frames
      //loop on (0= no loop, 1= normal loop, 2= palindrome)
});
