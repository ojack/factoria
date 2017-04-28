#pragma once

#include "ofMain.h"
#include "baseScene.h"
//#include "globo.h"

class globosScene : public baseScene{
    
public:
    
    void setup();
    void update();
    void draw();
   
    void initVid(ofVideoPlayer  vid, string filePath);
    
    ofVideoPlayer 		globos[3];
    ofVideoPlayer       maquina;
    
    ofFbo crossfadeFbo;
    ofParameter<float>          maquinaOpacity;
    ofParameter<ofVec2f>        videoScale;
};
