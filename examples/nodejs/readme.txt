//first cd to this directory and
npm install

//then start the yetanotheroscmovieplayer application
//here we assume the app is running locally (127.0.0.1)


//quick tests (from the terminal - assumes the app is running on 127.0.0.1)
node startmovie.js
node stop.js



//interactive examples (start by typing 'node' in terminal)
osc= require('node-osc')
client= new osc.Client('127.0.0.1', 61000)
client.send('/start', 'kjhkjh.png', 10)  //fade in a still image
client.send('/stop', 10)
client.send('/start', 'yetanotherdemo.mov', 100, 0)  //loop off (0= no loop, 1= normal loop, 2= palindrome)
client.send('/info')  //toggle info (also key 'i')
client.send('/fps', 15)  //set framerate
client.send('/speed', 0.5)  //set playback rate
client.send('/mode', 0)  //fill screen (ignore original aspect ratio)
client.send('/mode', 1)  //no scaling (original dimensions)
client.send('/mode', 2)  //scale to fit width (crop height)
client.send('/mode', 3)  //scale to fit height (crop width)
