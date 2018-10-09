#include "ofApp.h"

void ofApp::debugPrint() {
    std::cout << "blinkRate: " << this->rate << std::endl;
    std::cout << "gravity: "   << this->g    << std::endl;
    std::cout << "scene: "     << this->name << std::endl;
    std::cout << "#positions: "<< this->n_pos<< std::endl << std::endl;
}

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

    debugPrint();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r') {
        // reload
        this->loadSettings();
        debugPrint();
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

    // put an array into a file
    this->settings->pushTag("settings");
    this->settings->addValue("number_of_positions", 3);
    this->settings->popTag();

    this->settings->saveFile(this->settingsFilename); //puts settings.xml file in the bin/data folder
    ofLog(ofLogLevel::OF_LOG_NOTICE, "new settings written");
}

void ofApp::writeSettings() {
    //put some settings into a file
    this->settings->setValue("settings:blinkRate", this->rate);
    this->settings->setValue("settings:gravity",   this->g   );
    this->settings->setValue("settings:sceneName", this->name);

    // write an array
    this->settings->pushTag("settings");
    this->settings->setValue("number_of_positions", this->n_pos);
    this->settings->popTag();
    this->settings->saveFile(this->settingsFilename); //puts settings.xml file in the bin/data folder
    ofLog(ofLogLevel::OF_LOG_NOTICE, "settings written");
}

void ofApp::loadSettings() {
    this->rate = this->settings->getValue("settings:blinkRate", -1);
    this->g    = this->settings->getValue("settings:gravity",   -1);
    this->name = this->settings->getValue("settings:sceneName", "");
    ofLog(ofLogLevel::OF_LOG_NOTICE, "settings loaded");
}
