#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxKinect.h"
#include "ofxKinectProjectorToolkit.h"

#define USE_VIDEO


class kinectInputV1 {
    
public:
    void setup(int minDist, int maxDist);
    void update();
    void draw();
    
    void setAngle(int angle);
    void getContours();
    
    //void updateGlobos();
    vector <ofPolyline> getProjectedContours();
    vector <ofPolyline> projectedContours;
    
    ofVec3f getClosestPoint();
    
    ofParameterGroup params;
    
    ofParameter<float>          nearThreshold;
    ofParameter<float>          farThreshold;
    ofParameter<float>          minArea;
    ofParameter<float>          maxArea;
    ofParameter<float>          threshold;
    ofParameter<float>          persistence;
    ofParameter<float>          maxDistance;
    ofParameter < int >         medianFilterAmount;
    ofParameter<float>          blurAmount;
    ofParameter<ofVec2f>        globalOffset;
    ofParameter < bool > bMirror;
    
    ofxCv::ContourFinder        contourFinder;
    
#ifdef USE_VIDEO
    ofVideoPlayer player;
#else
    ofTexture texDepth;
    ofxKinect kinect;
    ofxKinectProjectorToolkit   kpt;
#endif
    
    bool bFoundABlobThisFrame;
    unsigned char * thresholdedImage;
    unsigned char * graypixels;
    
    ofImage filteredDepthImage;
    bool bIsFrameNew;
    
    int width;
    int height;
};