
#include "ofApp.h"

void ofApp::setup(){
    receiver.setup(PORT);
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    ofHideCursor();
    message= "";
    fileName= "";
    frames= 0;
    speed= 1.0;
    volume= 1.0;
    mode= SCALE;
    alpha= 0.f;
    steps= 255.f;
    type= NOTSET;
    ow= 0;
    oh= 0;
    x= 0;
    y= 0;
    w= ofGetScreenWidth();
    h= ofGetScreenHeight();
    info= false;
    cout<<"listening on port: "<<PORT<<"\n";
    cout<<"screen resolution: "<<ofGetScreenWidth()<<"x"<<ofGetScreenHeight()<<"\n";
    cout<<"default framerate: "<<ofGetFrameRate()<<"\n";
}
void ofApp::update() {
    while(receiver.hasWaitingMessages()) {
        ofxOscMessage msg;
        receiver.getNextMessage(msg);
        int num= msg.getNumArgs();
        string adr= msg.getAddress();
        message= oscMsgToString(num, adr, msg);
        if(adr=="/start") {
            if(num>0) {
                fileName= msg.getArgAsString(0);
                if(ofFile::doesFileExist(fileName)) {
                    loopMode= 1;        //default loopmode
                    steps= 255.f;      //default no fade in (255 per frame)
                    if(num>1) {
                        steps= 255.f/fmax(msg.getArgAsInt(1), 1.f);
                    }
                    if(isImage(fileName)) {
                        type= IMAGE;
                        videoPlayer.stop();
                        videoPlayer.close();
                        stillImage.load(fileName);
                        frames= 1;
                        ow= stillImage.getWidth();
                        oh= stillImage.getHeight();
                    } else {
                        if(ofToLower(fileName.substr(fileName.find_last_of(".")+1))!="hpv") {
                            type= MOVIE;
                            if(videoPlayer.isPlaying()) {
                                videoPlayer.stop();
                            }
                            videoPlayer.close();
                            videoPlayer.load(fileName);
                            frames= videoPlayer.getTotalNumFrames();
                            if(num>2) {
                                loopMode= msg.getArgAsInt(2);
                            }
                            if(loopMode==1) {
                                videoPlayer.setLoopState(OF_LOOP_NORMAL);
                            } else if(loopMode==2) {
                                videoPlayer.setLoopState(OF_LOOP_PALINDROME);
                            } else {
                                videoPlayer.setLoopState(OF_LOOP_NONE);
                            }
                            videoPlayer.play();
                            ow= videoPlayer.getWidth();
                            oh= videoPlayer.getHeight();
                        } else {
                            cout<<"file "<<fileName<<" not compatible - do not use a .hpv\n";
                            type= NOTCOMPATIBLE;
                        }
                    }
                    state= FADEIN;
                } else {
                    cout<<"file "<<fileName<<" not found\n";
                    type= NOTFOUND;
                }
            }
        } else if(adr=="/stop") {
            steps= 255.f;
            if(num>0) {
                steps= 255.f/fmax(msg.getArgAsInt(0), 1.f);
            }
            state= FADEOUT;
        } else if(adr=="/speed") {
            if(num>0) {
                speed= msg.getArgAsFloat(0);
                videoPlayer.setSpeed(speed);
            }
        } else if(adr=="/frame") {
            if(num>0) {
                videoPlayer.setFrame(msg.getArgAsInt(0));
            }
        } else if(adr=="/position") {
            if(num>0) {
                videoPlayer.setPosition(msg.getArgAsFloat(0));
            }
        } else if(adr=="/volume") {
            if(num>0) {
                volume= msg.getArgAsFloat(0);
                videoPlayer.setVolume(volume);
            }
        } else if(adr=="/mode") {
            if(num>0) {
                modes m[4] = {SCALE, ORIGINAL, WIDTH, HEIGHT};
                mode= m[msg.getArgAsInt(0)];
                if(mode==SCALE) {
                    x= 0;
                    y= 0;
                    w= ofGetScreenWidth();
                    h= ofGetScreenHeight();
                } else if(mode==ORIGINAL) {
                    x= (ofGetScreenWidth()-ow)*0.5;
                    y= (ofGetScreenHeight()-oh)*0.5;
                    w= ow;
                    h= oh;
                } else if(mode==WIDTH) {
                    float factor= ofGetScreenWidth()/float(ow);
                    int nh= oh*factor;
                    x= 0;
                    y= (ofGetScreenHeight()-nh)*0.5;
                    w= ofGetScreenWidth();
                    h= nh;
                } else if(mode==HEIGHT) {
                    float factor= ofGetScreenHeight()/float(oh);
                    int nw= ow*factor;
                    x= (ofGetScreenWidth()-nw)*0.5;
                    y= 0;
                    w= nw;
                    h= ofGetScreenHeight();
                }
            }
        } else if(adr=="/fps") {
            if(num>0) {
                ofSetFrameRate(msg.getArgAsInt(0));
            }
        } else if(adr=="/info") {
            if(num>0) {
                info= msg.getArgAsInt(0)>0;
            } else {
                info= !info;
            }
        } else if(adr=="/exit") {
            ofExit();
        }
    }
    if((type==MOVIE)&&(state!=STOPPED)) {
        videoPlayer.update();
    }
    switch (state) {
        case STOPPED:
            break;
        case FADEIN:
            alpha= fmin(fmax(alpha+steps, 0.f), 255.f);
            if(alpha==255.f) {
                state= PLAYING;
            }
            break;
        case PLAYING:
            break;
        case FADEOUT:
            alpha= fmin(fmax(alpha-steps, 0.f), 255.f);
            if(alpha==0.f) {
                videoPlayer.stop();
                state= STOPPED;
            }
            break;
    }
}
void ofApp::draw(){
    ofSetColor(255, 255, 255, alpha);
    if((type==MOVIE)&&(state!=STOPPED)) {
        videoPlayer.draw(x, y, w, h);
    } else if((type==IMAGE)&&(state!=STOPPED)) {
        stillImage.draw(x, y, w, h);
    } else if(type==NOTFOUND) {
        ofSetHexColor(0xFFFFFF);
        ofDrawBitmapString("file '"+fileName+"' not found!", 300, 300);
    } else if(type==NOTCOMPATIBLE) {
        ofSetHexColor(0xFFFFFF);
        ofDrawBitmapString("file '"+fileName+"' not compatible - do not use a .hpv", 300, 300);
    }
    if(info) {
        ofSetHexColor(0xFFFFFF);
        ofDrawBitmapString("listening on port: "+ofToString(PORT), 30, 30);
        ofDrawBitmapString("last osc: "+message, 30, 50);
        ofDrawBitmapString("screen resolution: "+ofToString(ofGetScreenWidth())+"x"+ofToString(ofGetScreenHeight()), 30, 70);
        ofDrawBitmapString("framerate: "+ofToString(ofGetFrameRate()), 30, 90);
        ofDrawBitmapString("fileName: "+fileName, 30, 110);
        ofDrawBitmapString("media type: "+typeToString(type), 30, 130);
        ofDrawBitmapString("media resolution: "+ofToString(ow)+"x"+ofToString(oh), 30, 150);
        ofDrawBitmapString("mode: "+modeToString(mode), 30, 170);
        ofDrawBitmapString("loopMode: "+ofToString(loopMode), 30, 190);
        ofDrawBitmapString("frames: "+ofToString(frames), 30, 210);
        ofDrawBitmapString("speed: "+ofToString(speed), 30, 230);
        ofDrawBitmapString("volume: "+ofToString(volume), 30, 250);
        ofDrawBitmapString("alpha: "+ofToString(alpha), 30, 270);
        ofDrawBitmapString("state: "+stateToString(state), 30, 290);
    }
}
void ofApp::exit() {
}
void ofApp::keyReleased(int key) {
    if(key=='i') {
        info= !info;
    }
}
string ofApp::oscMsgToString(int num, string adr, ofxOscMessage msg) {
    string res= adr;
    for(int i= 0; i<num; i++) {
        res= res+" ";
        if(msg.getArgType(i)==OFXOSC_TYPE_INT32) {
            res= res+ofToString(msg.getArgAsInt32(i));
        } else if(msg.getArgType(i)==OFXOSC_TYPE_FLOAT) {
            res= res+ofToString(msg.getArgAsFloat(i));
        } else if(msg.getArgType(i)==OFXOSC_TYPE_STRING) {
            res= res+msg.getArgAsString(i);
        }
    }
    return res;
}
bool ofApp::isImage(string fileName) {
    ofFile file(ofToDataPath(fileName));
    string ext= file.getExtension();
    return (ext=="png")||(ext=="tif")||(ext=="tiff")||(ext=="jpg")||(ext=="jpeg")||(ext=="gif")||(ext=="bmp");
}
string ofApp::typeToString(media type) {
    switch (type) {
        case MOVIE: return "MOVIE";
        case IMAGE: return "IMAGE";
        case NOTFOUND: return "NOTFOUND";
        case NOTCOMPATIBLE: return "NOTCOMPATIBLE";
        case NOTSET: return "";
        default: return "unknown";
    }
}
string ofApp::stateToString(states state) {
    switch (state) {
        case FADEIN: return "FADEIN";
        case PLAYING: return "PLAYING";
        case FADEOUT: return "FADEOUT";
        case STOPPED: return "STOPPED";
        default: return "unknown";
    }
}
string ofApp::modeToString(modes mode) {
    switch (mode) {
        case SCALE: return "SCALE";
        case ORIGINAL: return "ORIGINAL";
        case WIDTH: return "WIDTH";
        case HEIGHT: return "HEIGHT";
        default: return "unknown";
    }
}
