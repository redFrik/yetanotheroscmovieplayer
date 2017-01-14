# yetanotheroscmovieplayer
play videofiles fullscreen via opensound control messages

precompiled for **mac osx** and **raspberry pi**.

written during my artist-in-residency at [Anglia Ruskin University](http://www.anglia.ac.uk/arts-law-and-social-sciences/department-of-music-and-performing-arts), cambridge spring 2016.

built with [openFrameworks](http://openframeworks.cc) v0.9.3. tested on mac (osx 64bit 10.10.5), rpi1, rpi2 and rpi3 (raspbian-jessie).

installation & startup - osx
--

* download and extract the zip archive from <http://github.com/redFrik/yetanotheroscmovieplayer>
* double click `yetanotheroscmovieplayer_osx.app` (and a black window should fill the screen)

now copy your own images and/or movie files into the **data** directory and start sending osc commands from python, javascript, puredata, supercollider or whatever - see testcode below.

installation & startup - rpi
--

open a terminal window and type:

* `git clone git://github.com/redFrik/yetanotheroscmovieplayer --depth 1`
* `cd yetanotheroscmovieplayer`
* `sudo apt-get install libfreeimage-dev`
* `./yetanotheroscmovieplayer_rpi` (and a black window should fill the screen)

now copy your own images and/or movie files into the **data** directory and start sending osc commands from python, javascript, puredata, supercollider or whatever - see testcode below.

it is also recommended to increase the rpi's gpu memory to >= 128. do that by typing `sudo raspi-config` and select memory split under advanced options.

protocol
--

send opensoundcontrol (osc) messages to **port 61000**

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

* because the files are loaded from disk (sd-card) when started there might be a small delay.  a preload command that enables fast triggering is on my TODO.
* there is also a special rpi build for [Adafruit's PiTFT display](https://learn.adafruit.com/adafruit-pitft-3-dot-5-touch-screen-for-raspberry-pi?view=all). start it with `./yetanotheroscmovieplayer_rpitft`.
* palindrome looping does not yet work in the raspberry pi version.
* negative speed (backwards) does not yet work in the raspberry pi version.
* also for the rpitft version to avoid flicker you will want to log out and exit the raspbian desktop before starting this app (via ssh or startup script).
* on rpi to automatically start at boot type `sudo crontab -e` and add `@reboot /home/pi/yetanotheroscmovieplayer/yetanotheroscmovieplayer_rpi` to the end.
* and to hide the blinking login cursor when automatically string type `sudo nano /boot/cmdline.txt` and add `vt.global_cursor_default=0` to the line.
* if playing video files fail on rpi make sure you have memory split in raspi-config set to something => 128.

testcode
--

(also see `examples` folder)

```supercollider
//--supercollider
n= NetAddr("raspberrypi.local", 61000)  //if app is running on a rpi
n= NetAddr("127.0.0.1", 61000)  //if app is running locally on this mac
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
  * copy the folder `yetanotheroscmovieplayer_osx` into `of_v0.9.3_osx_release/apps/myApps/`
  * open the file `yetanotheroscmovieplayer_osx.xcodeproj` in xcode
  * make sure the target is `yetanotheroscmovieplayer_osx Release`
  * build (cmd+b)
  * the resulting application will be in the `bin` folder
* on rpi:
  * copy the folder `yetanotheroscmovieplayer_rpi` into `openFrameworks/apps/myApps/`
  * cd to that folder and type `make -j 4`
  * the resulting application will be in the `bin` folder
  * use `yetanotheroscmovieplayer_rpitft` to build for tft screens. also install the [ofxPiTFT](http://github.com/patriciogonzalezvivo/ofxPiTFT) addon.

jessie-lite
--

The standalone also works under jessie-lite if the following additional packages are installed...

* `sudo apt-get install git gstreamer1.0 libboost-filesystem1.55.0`

then follow the [installation & startup - rpi](#installation--startup---rpi) above.

autostart
--

type `crontab -e` and add the following line to the end...

`@reboot yetanotheroscmovieplayer/yetanotheroscmovieplayer_rpi`

todo:
--
* volume command and try with sound
* preload command
