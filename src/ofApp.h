#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{
	public:
		void setup();

		void keyPressed(int key);
		
        ofxXmlSettings *settings;
        string settingsFilename = "settings.xml";
        void writeDefaultSettings();
        void writeSettings();
        void loadSettings();
    
        void debugPrint();
        int rate;
        float g;
        string name;
};
