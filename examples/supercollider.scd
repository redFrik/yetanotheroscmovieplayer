//--supercollider
n= NetAddr("raspberrypi.local", 61000)  //if app is running on a rpi
n= NetAddr("127.0.0.1", 61000)  //if app is running locally on this mac
n.sendMsg(\start, "yetanotherdemo.mov")  //filename should match a movie or image file in the data/ directory
n.sendMsg(\stop)
n.sendMsg(\start, "yetanotherdemo.mov", 200)  //fade in over 200 frames
n.sendMsg(\start, "/some/place/video.mov")  //or use an absolute path
n.sendMsg(\stop, 300)  //fade out over 300 frames
n.sendMsg(\start, "kjhkjh.png", 10)  //fade in a still image
n.sendMsg(\stop, 10)
n.sendMsg(\start, "yetanotherdemo.mov", 100, 1)  //loop off (0= no loop, 1= normal loop (default), 2= palindrome)
n.sendMsg(\info)  //toggle info (also key 'i')
n.sendMsg(\fps, 15)  //set framerate
n.sendMsg(\speed, 0.5)  //set playback rate
n.sendMsg(\volume, 0.25)  //set volume (0.0-1.0)
n.sendMsg(\frame, 150)  //jump to frame in movie
n.sendMsg(\position, 0.5)  //jump to position in movie (0.0-1.0)
n.sendMsg(\mode, 0)  //fill screen (ignore original aspect ratio)
n.sendMsg(\mode, 1)  //no scaling (original dimensions)
n.sendMsg(\mode, 2)  //scale to fit width (crop height)
n.sendMsg(\mode, 3)  //scale to fit height (crop width)

n.sendMsg(\stop);

//start halfway
(
n.sendMsg(\start, "yetanotherdemo.mov");
n.sendMsg(\position, 0.5);
)

n.sendMsg(\exit)  //quit app