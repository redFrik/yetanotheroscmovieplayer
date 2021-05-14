#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLWindowSettings msettings;
	msettings.setSize(1024, 768);
	msettings.windowMode = OF_FULLSCREEN;
	msettings.setGLVersion(4, 1);

	ofCreateWindow(msettings);

	ofRunApp(new ofApp());

}
