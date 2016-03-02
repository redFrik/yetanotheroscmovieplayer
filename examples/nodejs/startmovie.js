var osc= require('node-osc');
var client = new osc.Client('127.0.0.1', 61000);
client.send('/start', 'yetanotherdemo.mov', 200, 1, function () {  //fade in movie over 200 frames
    //loop on (0= no loop, 1= normal loop, 2= palindrome)
    client.kill();
});
