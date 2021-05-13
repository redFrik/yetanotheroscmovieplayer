//first cd to this directory and
npm install

//if you don’t have npm first install that with sudo apt-get install npm

//then start the yetanotheroscmovieplayer application
//here we assume the app is running locally (127.0.0.1)


//quick tests (from the terminal - assumes the app is running on 127.0.0.1)
node startmovie.js
node stop.js



//interactive examples (start by typing 'node' in terminal)
udp= require('dgram')
osc= require('osc-min')
sck= udp.createSocket('udp4')

buf= osc.toBuffer({address:'/start', args:['kjhkjh.png', 10]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //fade in a still image

buf= osc.toBuffer({address:'/stop', args:[10]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')

buf= osc.toBuffer({address:'/start', args:['yetanotherdemo.mov', 100, 0]})  //loop off (0= no loop, 1= normal loop, 2= palindrome)
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')

buf= osc.toBuffer({address:'/info'})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //toggle info (also key 'i')

buf= osc.toBuffer({address:'/fps', args:[15]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //set framerate

buf= osc.toBuffer({address:'/speed', args:[0.5]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //set playback rate

buf= osc.toBuffer({address:'/volume', args:[0.25]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //set volume (0.0-1.0)

buf= osc.toBuffer({address:'/frame', args:[150]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //jump to frame in movie

buf= osc.toBuffer({address:'/position', args:[0.5]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //jump to position in movie (0.0-1.0)

buf= osc.toBuffer({address:'/mode', args:[0]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //fill screen (ignore original aspect ratio)
buf= osc.toBuffer({address:'/mode', args:[1]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //no scaling (original dimensions)
buf= osc.toBuffer({address:'/mode', args:[2]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //scale to fit width (crop height)
buf= osc.toBuffer({address:'/mode', args:[3]})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //scale to fit height (crop width)

buf= osc.toBuffer({address:'/exit'})
sck.send(buf, 0, buf.length, 61000, '127.0.0.1')  //quit app

sck.close()
