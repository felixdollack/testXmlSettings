#include "ofApp.h"

void ofApp::debugPrint() {
    std::cout << "blinkRate: " << this->rate << std::endl;
    std::cout << "gravity: "   << this->g    << std::endl;
    std::cout << "scene: "     << this->name << std::endl;
    std::cout << "#positions: "<< this->n_pos<< std::endl;
    for (int kk=0; kk < this->pos.size(); kk++) {
        std::cout << "x: "  << this->pos[kk].x;
        std::cout << " y: " << this->pos[kk].y << std::endl;
    }
    cout << std::endl;
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
    this->settings->addTag("positions");
    this->settings->pushTag("positions");
    {
        this->settings->addTag("position");
        this->settings->pushTag("position", 0); // NOTE : requires 'which' parameter.
        this->settings->addValue("X", -1);
        this->settings->addValue("Y", 2);
        this->settings->popTag();
        this->settings->addTag("position");
        this->settings->pushTag("position", 1);
        this->settings->addValue("X", 2);
        this->settings->addValue("Y", 1);
        this->settings->popTag();
        this->settings->addTag("position");
        this->settings->pushTag("position", 2);
        this->settings->addValue("X", 1);
        this->settings->addValue("Y", -2);
        this->settings->popTag();
    }
    this->settings->popTag();
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
    this->settings->addTag("positions");
    this->settings->pushTag("positions");
    for(int i = 0; i < pos.size(); i++){
        this->settings->addTag("position");
        this->settings->pushTag("position", i); // NOTE : requires 'which' parameter.
        this->settings->addValue("X", pos[i].x);
        this->settings->addValue("Y", pos[i].y);
        this->settings->popTag();
    }
    this->settings->popTag();
    this->settings->popTag();
    this->settings->saveFile(this->settingsFilename); //puts settings.xml file in the bin/data folder
    ofLog(ofLogLevel::OF_LOG_NOTICE, "settings written");
}

void ofApp::loadSettings() {
    this->rate = this->settings->getValue("settings:blinkRate", -1);
    this->g    = this->settings->getValue("settings:gravity",   -1);
    this->name = this->settings->getValue("settings:sceneName", "");

    this->settings->pushTag("settings");
    this->n_pos = this->settings->getValue("number_of_positions", -1);
    this->settings->pushTag("positions");
    for(int i = 0; i < this->n_pos; i++){
        int x, y;
        this->settings->pushTag("position", i); // NOTE : requires 'which' parameter.
        x = this->settings->getValue("X", 0);
        y = this->settings->getValue("Y", 0);
        this->settings->popTag();
        pos.push_back(ofVec2f(x, y));
    }
    this->settings->popTag();
    this->settings->popTag();
    ofLog(ofLogLevel::OF_LOG_NOTICE, "settings loaded");
}
