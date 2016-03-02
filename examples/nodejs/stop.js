var osc= require('node-osc');
var client = new osc.Client('127.0.0.1', 61000);
client.send('/stop', 100, function () {  //fade out and stop over 100 frames
    client.kill();
});
