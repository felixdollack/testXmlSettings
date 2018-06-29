#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    this->settings = new ofxXmlSettings();
    bool success = this->settings->loadFile(this->settingsFilename);
    if (success == true) {
        ofLog(ofLogLevel::OF_LOG_NOTICE, "file loaded");
        loadSettings();
    } else {
        ofLog(ofLogLevel::OF_LOG_WARNING, "file not loaded or not existent");
        writeDefaultSettings();
    }

    // debug print
    std::cout << "blinkRate: " << rate << std::endl;
    std::cout << "gravity: "   << g    << std::endl;
    std::cout << "scene: "     << name << std::endl << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r') {
        // reload
        this->loadSettings();
    }
    if (key == 's') {
        // save
        this->writeSettings();
    }
}

void ofApp::writeDefaultSettings() {
    //put some settings into a file
    this->settings->setValue("settings:blinkRate", 10);
    this->settings->setValue("settings:gravity", 9.8);
    this->settings->setValue("settings:sceneName", "field");
    this->settings->saveFile(this->settingsFilename); //puts settings.xml file in the bin/data folder
    ofLog(ofLogLevel::OF_LOG_NOTICE, "new settings written");
}

void ofApp::writeSettings() {
    //put some settings into a file
    this->settings->setValue("settings:blinkRate", this->rate);
    this->settings->setValue("settings:gravity",   this->g   );
    this->settings->setValue("settings:sceneName", this->name);
    this->settings->saveFile(this->settingsFilename); //puts settings.xml file in the bin/data folder
    ofLog(ofLogLevel::OF_LOG_NOTICE, "settings written");
}

void ofApp::loadSettings() {
    this->rate = this->settings->getValue("settings:blinkRate", -1);
    this->g    = this->settings->getValue("settings:gravity",   -1);
    this->name = this->settings->getValue("settings:sceneName", "");
    ofLog(ofLogLevel::OF_LOG_NOTICE, "settings loaded");
}
