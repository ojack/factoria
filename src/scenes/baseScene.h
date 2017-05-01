#pragma once

#include "ofMain.h"
#include "kinectInputV1.h"
#include "ofxGui.h"

class baseScene {
    
public:
    baseScene(string settings);
    
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};    
    
    int width;
    int height;
   
    kinectInputV1 * kinectV1;
    
    ofParameterGroup params;
    ofFbo renderFbo;
    
    string settingsFile;
};