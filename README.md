# yetanotheroscmovieplayer
play videofiles fullscreen via opensound control messages

written during my artist-in-residency at [Anglia Ruskin University](http://www.anglia.ac.uk/arts-law-and-social-sciences/department-of-music-and-performing-arts), cambridge spring 2016

built with [openFrameworks](http://openframeworks.cc) v0.9.2 and tested on osx 10.10.5.

`git clone http://github.com/redFrik/yetanotheroscmovieplayer`

copy your own image and/or movie files into the **data** directory.

osc protocol
--

send opensoundcontrol messages to port 61000

```
/start, moviefilename, fadeinframes, loopmode
/stop, fadeoutframes
/speed, playbackrate
/mode, scalingmode
/fps, framespersecond
/info, status
```

testcode
--

```
//--supercollider
n= NetAddr("127.0.0.1", 61000)
n.sendMsg(\start, "yetanotherdemo.mov")  //filename should match a movie or image file in bin/ directory
n.sendMsg(\stop)
n.sendMsg(\start, "yetanotherdemo.mov", 200)  //fade in over 200 frames
n.sendMsg(\stop, 400)  //fade out over 400 frames
n.sendMsg(\start, "kjhkjh.png", 10)  //fade in a still image
n.sendMsg(\stop, 10)
n.sendMsg(\start, "yetanotherdemo.mov", 100, 2)  //loop palindrome (0= no loop, 1= normal loop, 2= palindrome)
n.sendMsg(\info)  //toggle info (also key 'i')
n.sendMsg(\fps, 15)  //set framerate
n.sendMsg(\speed, 0.75)  //set playback rate
n.sendMsg(\mode, 0)  //fill screen (ignores aspect ratio)
n.sendMsg(\mode, 1)  //no scaling (original dimensions)
n.sendMsg(\mode, 2)  //width (crop or blank height)
n.sendMsg(\mode, 3)  //height (crop or blank height)
```
