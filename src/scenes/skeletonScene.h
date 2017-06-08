#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "ofxKinectV2OSC.h"
#include "ofxXmlSettings.h"
#include "../../SkeletonAsset.h"

//#include "distanceCalibration.h"

//#define THROW_RATIO 0.5
//#define ASPECT_RATIO 1.7778

class skeletonScene : public baseScene{
    
public:
    using baseScene::baseScene;
    
    void setup();
    void update();
    void draw();
    //void clear();
    
    //skeleton parameters
    void drawSkeletons();
    void drawLimb(ofVec2f start, ofVec2f end, SkeletonAsset img);
    void drawHead(ofVec2f head, ofVec2f spine, SkeletonAsset img);
    
    void createSkeletonMap();
    ofVec2f depthToProjector(ofVec2f depthPt);
    void drawTorso(ofVec2f topLeft, ofVec2f topRight, ofVec2f bottomRight, ofVec2f bottomLeft);
    Joint getJoint(string type, Skeleton skeleton);
    pair<pair<string, string>, SkeletonAsset> createImageReference(string start, string end, SkeletonAsset image);
    
    ofParameterGroup parameters;
    ofParameter<ofVec2f> torsoPad;
    ofParameter<ofVec2f> skeletonOffset, limbScale;
    ofParameter<float> hipWiden;
    ofParameter<float>opacity;
    ofParameter<bool> showDebug, showSkeletons, soundEnabled, bUseProjection;
    ofParameter<bool>changeFrequency;
    
    ofxKinectV2OSC oscKinect;
    BodyRenderer renderer;
    
    Skeleton* skeleton;
    vector<Skeleton>* skeletons;
    
    SkeletonAsset rUpperArm;
    SkeletonAsset rForeArm;
    SkeletonAsset lUpperArm;
    SkeletonAsset lForeArm;
    SkeletonAsset lShin;
    SkeletonAsset rShin;
    SkeletonAsset rThigh;
    SkeletonAsset lThigh;
    SkeletonAsset neck;
    ofImage torso;
    ofTexture torsoTexture;
    
    ofMesh torsoMesh;
    
    vector<pair<pair<string, string>, SkeletonAsset>> skeletonMap;
    
    HandState rightHandState;
    HandState leftHandState;
    HandState prevRightHandState;
    HandState prevLeftHandState;
    
    ofSoundPlayer lassoLeft;
    ofSoundPlayer lassoRight;
    ofSoundPlayer  fistLeft;
    ofSoundPlayer  fistRight;
    
    ofxXmlSettings XML;
    void setupProjector();
    ofVec2f getProjectorFromDepthPoint(ofVec2f point);
    ofVec2f getProjectorFromCameraPoint(ofVec3f cameraPoint);
    cv::Mat projectorWorldView;
    
    cv::Mat proIntrinsics, proExtrinsics;
    ofxCv::Intrinsics proCalibration;
    cv::Size proSize;

    
};
