# yetanotheroscmovieplayer
Play videofiles fullscreen via OpenSound Control messages.

Precompiled for **macOS** and **Raspberry Pi OS**.

Written during my artist-in-residency at [Anglia Ruskin University](https://www.anglia.ac.uk/arts-law-and-social-sciences/department-of-music-and-performing-arts), Cambridge spring 2016.

Built with [openFrameworks](https://openframeworks.cc) v0.11.0 under macOS (64bit 10.12.6) and under RPi OS (32-bit Buster).

For older operating system, download builds from the [releases](https://github.com/redFrik/yetanotheroscmovieplayer/releases) page.

Installation & startup - macOS
--

* Download and extract the zip archive from <https://github.com/redFrik/yetanotheroscmovieplayer>
* Double click `yetanotheroscmovieplayer_osx.app`

and a black window should fill the screen. Press '`i`' to see the status and `ESC` to exit.

Now copy your own images and/or movie files into the **data** directory and start sending OSC commands from Python, JavaScript, PureData, SuperCollider or whatever - see testcode below.

Installation & startup - RPi OS
--

First open a terminal window and type...

```bash
sudo raspi-config
```

Increase the RPi's GPU memory to >= 128 and select GL (Fake KMS) under Advanced Options / GL Driver.

Next install this software and additional libraries by typing...

```bash
sudo apt-get update
sudo apt-get install libglfw3 libfreeimage3 libboost-filesystem1.67.0 liburiparser1
git clone git://github.com/redFrik/yetanotheroscmovieplayer --depth 1
```

To start type...

```bash
cd yetanotheroscmovieplayer
./yetanotheroscmovieplayer_rpi
```

and a black window should fill the screen. Press '`i`' to see the status and `ctrl+c` to exit.

Now copy your own images and/or movie files into the **data** directory and start sending OSC commands from Python, JavaScript, PureData, SuperCollider or whatever - see testcode below.

Protocol
--

Send open sound control (OSC) messages to **port 61000**

```
/start, filename, fadeinframes, loopmode
/stop, fadeoutframes
/speed, playbackrate
/mode, scalingmode
/fps, framespersecond
/info, status
```

Notes
--

* Because the files are loaded from disk (SD card) when started there might be a small delay. A preload command that enables fast triggering is on my TODO.
* There is also a special RPi build for [Adafruit's PiTFT display](https://learn.adafruit.com/adafruit-pitft-3-dot-5-touch-screen-for-raspberry-pi?view=all). Start it with `./yetanotheroscmovieplayer_rpitft`.
* Palindrome looping does not yet work in the Raspberry Pi version.
* Negative speed (backwards) does not yet work in the Raspberry Pi version.
* Also, for the rpitft version to avoid flicker you will want to log out and exit the desktop before starting this app (via SSH or startup script).
* On RPi to automatically start at boot type `sudo crontab -e` and add `@reboot /home/pi/yetanotheroscmovieplayer/yetanotheroscmovieplayer_rpi` to the end.
* To hide the blinking login cursor when automatically string type `sudo nano /boot/cmdline.txt` and add `vt.global_cursor_default=0` to the line.
* If playing video files fail on RPi make sure you have memory split in raspi-config set to something => 128.
* The error `[ error ] ofAppGLFWWindow: 65544: X11: The DISPLAY environment variable is missing` might appear if running via SSH. The command `export DISPLAY=:0.0` should make the error go away. Or log in via VNC and try.
* This is not working under Raspberry Pi OS Lite at the moment (tried with `sudo apt-get install xorg libgstreamer-plugins-base1.0-0`).

Testcode
--

(also see `examples` folder)

```supercollider
//--supercollider
n= NetAddr("raspberrypi.local", 61000)  //if app is running on a RPi
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

(Advanced) Build instructions
--

This simple application was built using openFrameworks and you can easily modify it and/or build it for other operating systems that oF supports.

* Download and install [openFrameworks](https://openframeworks.cc/download/) for your platform.
* Follow the oF setup guide and make sure you can compile example projects.
* On macOS:
  * Copy the folder `sourcecode/yetanotheroscmovieplayer_osx` into `of_v0.11.0_osx_release/apps/myApps/`
  * Open the file `yetanotheroscmovieplayer_osx.xcodeproj` in Xcode.
  * Make sure the target is `yetanotheroscmovieplayer_osx Release`
  * Build (Cmd+b)
  * The resulting application will be in the `bin` folder.
* On RPi:
  * Copy the folder `sourcecode/yetanotheroscmovieplayer_rpi` into `openFrameworks/apps/myApps/`
  * Change directory to that folder with `cd` and type `make -j 4`
  * The resulting application will be in the `bin` folder.
  * Use `yetanotheroscmovieplayer_rpitft` to build for TFT screens. Also install the [ofxPiTFT](https://github.com/patriciogonzalezvivo/ofxPiTFT) addon.

Autostart
--

On Raspberry Pi type `crontab -e` and add the following line to the end...

`@reboot yetanotheroscmovieplayer/yetanotheroscmovieplayer_rpi`

Todo:
--
* Volume command and try with sound
* Preload command
* Quit command
