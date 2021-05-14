#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 61000

enum states {
    STOPPED= 0,
    FADEIN,
    PLAYING,
    FADEOUT
};

enum media {
    NOTSET= 0,
    NOTFOUND,
    NOTCOMPATIBLE,
    MOVIE,
    IMAGE
};

enum modes {
    SCALE= 0,
    ORIGINAL,
    WIDTH,
    HEIGHT
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyReleased(int key);

    ofxOscReceiver receiver;
    ofVideoPlayer videoPlayer;
    ofImage stillImage;
    string oscMsgToString(int num, string adr, ofxOscMessage msg);
    bool isImage(string fileName);
    string typeToString(media type);
    string stateToString(states state);
    string modeToString(modes mode);
    string message;
    string fileName;    //current file
    int loopMode;       //current type of looping
    int frames;         //number of frames in file
    float speed;        //current playback rate
    float volume;       //current volume
    float alpha;        //current alphachannel for fading
    float steps;        //number of alpha steps per frame for fading in/out
    int ow, oh;         //original media dimensions
    int x, y, w, h;     //drawing dimensions
    bool info;          //display info flag
    states state;       //program state
    media type;         //which file type - movie, still image or not found
    modes mode;         //how to crop or scale the image
};
