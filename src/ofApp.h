#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxKinect.h"

#include "ofxGui.h"
#include "ofxSyphon.h"
#include "ofxMidi.h"
#include "ofxKinectV2OSC.h"
#include "ofxXmlSettings.h"
#include "ofxBlur.h"
#include "kinectInputV1.h"
#include "sceneManager.h"

// projector resolution
#define PROJECTOR_RESOLUTION_X 1280
#define PROJECTOR_RESOLUTION_Y 720

//kinect image resolution
#define KINECT_WIDTH 512
#define KINECT_HEIGHT 424

//distance range to detect kinect
#define KINECT_MIN_DIST 500
#define KINECT_MAX_DIST 8000

using namespace ofxCv;
using namespace cv;


class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void setupProjection();
    void drawProjection(ofEventArgs & args);
    
    kinectInputV1                           kinectV1;
    
    sceneManager                            SM;
    
    ofRectangle                             outputRect;
    ofxPanel                                gui;
    ofxPanel                                kinectGui;
    
    
    bool                                    bShowDebug;
    bool                                    bSetFullScreen;
   
    ofParameter<ofVec2f>                    globalOffset;
    ofParameter<float>                      maquinaOpacity;
    ofParameter<bool>                       useVideo, useProjector, drawGlobos;
    
    ofxSyphonServer                         mascaraSyphon;
    ofxSyphonServer                         globosSyphon;
    ofxSyphonServer                         skeletonSyphon;
    
    ofFbo renderFbo;
    ofFbo skeletonFbo;
    ofFbo mascaraFbo;
    ofFbo globosFbo;
    ofFbo crossfadeFbo;
    
    string                     files[3];
    ofParameter<int>          settingsIndex;
    
    int angle;
};
