# yetanotheroscmovieplayer
Fade in and out video and images fullscreen via OpenSound Control messages.

Precompiled for **macOS** and **Raspberry Pi OS**.

Written during my artist-in-residency at [Anglia Ruskin University](https://www.anglia.ac.uk/arts-law-and-social-sciences/department-of-music-and-performing-arts), Cambridge spring 2016.

Built with [openFrameworks](https://openframeworks.cc) v0.11.2 under macOS (64bit 10.14.6) and under RPi OS (32-bit Buster).
Should also work under **Linux** and **Windows** but you will need to compile it yourself using openFrameworks.

For older operating system, download builds from the [releases](https://github.com/redFrik/yetanotheroscmovieplayer/releases) page.

# macOS

* Download and extract the zip archive from <https://github.com/redFrik/yetanotheroscmovieplayer>
* Double click `yetanotheroscmovieplayer_osx.app`

and a black window should fill the screen. Type '`i`' to see the status and '`ESC`' to exit.

Now copy your own images and/or movie files into the **data** directory and start sending OSC commands from Python, JavaScript, PureData, SuperCollider or whatever - see [protocol](#protocol) and [testcode](#testcode) below.

macOS Notes
--

* Jumping backwards in time in a movie can be slow. Try encoding your video as PhotoJPEG or other similar non Motion JPEG format _or_ use the HPV version.
* To enable loading media files from the **data** directory you probably need to _un-quarantine_ the .app and remove translocation. You can do this either manually - by moving the application outside of the folder and back again - or with the following terminal command...
  ```bash
  xattr -cr yetanotheroscmovieplayer_osx.app
  xattr -cr yetanotheroscmovieplayer_hpv.app
  ```

macOS HPV
--

There is also a version for the [High Performance Video](https://github.com/vjacob/ofxHPVPlayer) Eco-system. This one is optimised for scrubbing and playing back high resolution video.

A .hpv file can be created by first using ffmpeg to convert a video into a folder of png files, and then give that folder as input to [HPVCreator](https://github.com/HasseltVR/Holo_Toolset/releases). The first step, .mov to .png conversion, could look like...
```bash
ffmpeg -i input/yetanotherdemo.mov -vsync 0 dest/out%05d.png
```

# RPi OS

Installation & startup
--

First open a terminal window and type...

```bash
sudo raspi-config
```

Increase the RPi's GPU memory to >= 128 and select GL (Fake KMS) under Advanced Options / GL Driver.

Next install this software by typing...

```bash
git clone git://github.com/redFrik/yetanotheroscmovieplayer --depth 1
```

To start type...

```bash
cd yetanotheroscmovieplayer
./yetanotheroscmovieplayer_rpi
```

and a black window should fill the screen. Type '`i`' to see the status and '`ctrl+c`' to exit.

Now copy your own images and/or movie files into the **data** directory and start sending OSC commands from Python, JavaScript, PureData, SuperCollider or whatever - see [protocol](#protocol) and [testcode](#testcode) below.

Autostart
--

On Raspberry Pi type `crontab -e` and add the following line to the end...

`@reboot /home/pi/yetanotheroscmovieplayer/yetanotheroscmovieplayer_rpi`

RPi Notes
--

* Jumping backwards in time in a movie can be slow. Try encoding your video as PhotoJPEG or other similar non Motion JPEG format.
* Because the files are loaded from disk (SD card) when started there might be a small delay. A preload command that enables fast triggering is on my TODO.
* There is also a special RPi build for [Adafruit's PiTFT display](https://learn.adafruit.com/adafruit-pitft-3-dot-5-touch-screen-for-raspberry-pi?view=all). Start it with `./yetanotheroscmovieplayer_rpitft`.
* Palindrome looping does not yet work in the Raspberry Pi version.
* Negative speed (backwards) does not yet work in the Raspberry Pi version.
* Also, for the rpitft version to avoid flicker you will want to log out and exit the desktop before starting this app (via SSH or startup script).
* On RPi to automatically start at boot type `sudo crontab -e` and add `@reboot /home/pi/yetanotheroscmovieplayer/yetanotheroscmovieplayer_rpi` to the end.
* To hide the blinking login cursor when automatically string type `sudo nano /boot/cmdline.txt` and add `vt.global_cursor_default=0` to the line.
* If playing video files fail on RPi make sure you have memory split in raspi-config set to something => 128.
* The error `[ error ] ofAppGLFWWindow: 65544: X11: The DISPLAY environment variable is missing` might appear if running via SSH. The command `export DISPLAY=:0.0` should make the error go away. Or log in via VNC and try.
* This is not working under Raspberry Pi OS Lite at the moment (tried with `sudo apt-get install xorg libgstreamer-plugins-base1.0-0 libglfw3 libfreeimage3 libfreeimage3 libboost-filesystem1.67.0 liburiparser1`).

# Protocol

Send open sound control (OSC) messages to **port 61000**

```
/start, filename, fadeinframes, loopmode
/stop, fadeoutframes
/speed, playbackrate
/volume, amplitude
/frame, movieframe
/position, percentage
/mode, scalingmode
/fps, framespersecond
/info, status
/exit
```

# Testcode

(also see the `examples` folder)

```supercollider
//--supercollider
n= NetAddr("raspberrypi.local", 61000)  //if app is running on a RPi
n= NetAddr("127.0.0.1", 61000)  //if app is running locally on this mac
n.sendMsg(\start, "yetanotherdemo.mov")  //filename should match a movie or image file in the data/ directory
n.sendMsg(\start, "/some/place/video.mov")  //or use an absolute path
n.sendMsg(\stop)
n.sendMsg(\start, "yetanotherdemo.mov", 200)  //fade in over 200 frames
n.sendMsg(\stop, 300)  //fade out over 300 frames
n.sendMsg(\start, "kjhkjh.png", 10)  //fade in a still image
n.sendMsg(\stop, 10)
n.sendMsg(\start, "yetanotherdemo.mov", 100, 0)  //loop off (0= no loop, 1= normal loop (default), 2= palindrome)
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
n.sendMsg(\exit)  //quit app
```

(Advanced) Build instructions
--

This simple application was built using openFrameworks and you can easily modify it and/or build it for other operating systems that oF supports.

* Download and install [openFrameworks](https://openframeworks.cc/download/) for your platform.
* Follow the oF setup guide and make sure you can compile example projects.
* On macOS:
  * Copy the folder `sourcecode/yetanotheroscmovieplayer_osx` into `of_v0.11.2_osx_release/apps/myApps/`
  * Open the file `yetanotheroscmovieplayer_osx.xcodeproj` in Xcode or `yetanotheroscmovieplayer_osx.code-workspace` in VSCodium or VSCode.
  * Make sure the target is `yetanotheroscmovieplayer_osx Release`
  * Build (Cmd+b in Xcode, Cmd+Shift+P - run build task in VSC)
  * The resulting application will be in the `bin` folder.
  * Use `yetanotheroscmovieplayer_hpv` to build for HPV support. Also install the [ofxHPVPlayer](https://github.com/vjacob/ofxHPVPlayer) addon.
* On RPi:
  * Copy the folder `sourcecode/yetanotheroscmovieplayer_rpi` into `openFrameworks/apps/myApps/`
  * Change directory to that folder with `cd` and type `make -j 3`
  * The resulting application will be in the `bin` folder.
  * Use `yetanotheroscmovieplayer_rpitft` to build for TFT screens. Also install the [ofxPiTFT](https://github.com/patriciogonzalezvivo/ofxPiTFT) addon.

Todo:
--
* Preload command
