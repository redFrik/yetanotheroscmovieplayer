# yetanotheroscmovieplayer
play videofiles fullscreen via opensound control messages

precompiled for **mac osx** (64bit) and **raspberry pi** (jessie).

written during my artist-in-residency at [Anglia Ruskin University](http://www.anglia.ac.uk/arts-law-and-social-sciences/department-of-music-and-performing-arts), cambridge spring 2016. built with [openFrameworks](http://openframeworks.cc) v0.9.2. tested on osx 10.10.5 and rpi2 raspbian-jessie.

how to
--

* download and extract the zip from http://github.com/redFrik/yetanotheroscmovieplayer
* copy your own images and/or movie files into the **data** directory
* double click the file application file and a black window should fill the screen
  * on osx: the application is called **yetanotheroscmovieplayer_osx.app**
  * on rpi: the application is called **yetanotheroscmovieplayer_rpi**
  * on rpi you can also start it from terminal with: `./yetanotheroscmovieplayer_rpi`
  * there is also a special rpitft version for using with small TFT displays
* start sending osc commands from python, javascript, puredata, supercollider or whatever - see testcode below

osc protocol
--

send opensoundcontrol messages to **port 61000**

```
/start, filename, fadeinframes, loopmode
/stop, fadeoutframes
/speed, playbackrate
/mode, scalingmode
/fps, framespersecond
/info, status
```

notes
--

* palindrome looping does not yet work in the raspberry pi version.
* negative speed (backwards) does not yet work in the raspberry pi version.
* use the rpitft version if you have a tft display like Adafruit's [PiTFT Plus](https://www.adafruit.com/products/2441)

testcode
--

(also see `examples` folder)

```
//--supercollider
n= NetAddr("127.0.0.1", 61000)
n.sendMsg(\start, "yetanotherdemo.mov")  //filename should match a movie or image file in the data/ directory
n.sendMsg(\stop)
n.sendMsg(\start, "yetanotherdemo.mov", 200)  //fade in over 200 frames
n.sendMsg(\stop, 300)  //fade out over 300 frames
n.sendMsg(\start, "kjhkjh.png", 10)  //fade in a still image
n.sendMsg(\stop, 10)
n.sendMsg(\start, "yetanotherdemo.mov", 100, 0)  //loop off (0= no loop, 1= normal loop, 2= palindrome)
n.sendMsg(\info)  //toggle info (also key 'i')
n.sendMsg(\fps, 15)  //set framerate
n.sendMsg(\speed, 0.5)  //set playback rate
n.sendMsg(\mode, 0)  //fill screen (ignore original aspect ratio)
n.sendMsg(\mode, 1)  //no scaling (original dimensions)
n.sendMsg(\mode, 2)  //scale to fit width (crop height)
n.sendMsg(\mode, 3)  //scale to fit height (crop width)
```

(advanced) build instructions
--
this simple application was built using openFrameworks and you can easily modify it and/or build it for other operating systems that oF supports.

* download and install [openFrameworks](http://openframeworks.cc/download/) for your platform.
* follow the oF setup guide and make sure you can compile example projects.
* on osx:
  * copy the folder `yetanotheroscmovieplayer_osx` into `of_v0.9.2_osx_release/apps/myApps/`
  * open the file `yetanotheroscmovieplayer_osx.xcodeproj` in xcode
  * make sure the target is `yetanotheroscmovieplayer_osx Release`
  * build (cmd+b)
  * the resulting application will be in the `bin` folder
* on rpi:
  * copy the folder `yetanotheroscmovieplayer_rpi` into `openFrameworks/apps/myApps/`
  * cd to this folder and type `make -j4`
  * the resulting application will be in the `bin` folder
  * use the `yetanotheroscmovieplayer_rpitft` for tft screens. also install the [ofxPiTFT](http://github.com/patriciogonzalezvivo/ofxPiTFT) addon.
