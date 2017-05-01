#include "ofApp.h"
#include "globosScene.h"
#include "skeletonScene.h"
#include "maskScene.h"

void ofApp::setup() {
     int angle = 0;
    ofSetVerticalSync(true);
    ofSetWindowShape(1280, 960);
    ofSetLogLevel(OF_LOG_VERBOSE);
    bSetFullScreen = false;
    bShowDebug = true;
   
    kinectV1.setup(KINECT_MIN_DIST, KINECT_MAX_DIST);
    kinectV1.width = PROJECTOR_RESOLUTION_X;
    kinectV1.height = PROJECTOR_RESOLUTION_Y;
  
    kinectGui.setup("kinect");
    kinectGui.setPosition(200, 0);
    kinectGui.add(kinectV1.params);
    
    outputRect = ofRectangle(0, 0, PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);
    gui.setup("parameters");
    
    SM.scenes.push_back(new maskScene("mascara.xml"));
    SM.scenes.push_back(new skeletonScene("skeleton.xml"));
    SM.scenes.push_back(new globosScene("globos.xml"));
    
    for (int i = 0; i < SM.scenes.size(); i++){
        SM.scenes[i]->width = PROJECTOR_RESOLUTION_X;
        SM.scenes[i]->height = PROJECTOR_RESOLUTION_Y;
        SM.scenes[i]->kinectV1 = &kinectV1;
    }
    SM.gui = &gui;
  
    gui.setHeaderBackgroundColor(ofColor(100, 0, 0));
    /*for (int i = 0; i < SM.scenes.size(); i++){
        gui.add(SM.scenes[i]->params);
    }*/
    
      SM.setup();
}

void ofApp::setupProjection(){
    // ofToggleFullscreen();
}


void ofApp::update() {
   
    SM.update();
    
}

void ofApp::drawProjection(ofEventArgs & args){
    if(bSetFullScreen){
        ofSetFullscreen(true);
    } else {
        ofSetFullscreen(false);
    }
   
    ofClear(0, 0, 0, 0);
    SM.draw();
    
}

void ofApp::draw() {
    string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0);
    ofSetWindowTitle(info);
    ofClear(0);
    ofSetColor(255, 255, 255, 255);
   
    kinectV1.draw();

    gui.draw();
    kinectGui.draw();
  
}

void ofApp::keyPressed(int key) {
    if(key == OF_KEY_LEFT)  {
       
    } else if(key == OF_KEY_RIGHT)  {
      // gui.loadFromFile(files[settingsIndex]);
        SM.nextScene();
        SM.clear();
        
    }  else if (key == 's'){
       // gui.saveToFile(files[settingsIndex]);
        SM.saveCurrentSettings();
    } else if(key=='k'){
        kinectGui.saveToFile("kinect.xml");
    } else if(key==' '){
        bShowDebug = !bShowDebug;
    } else if(key=='f'){
        
        bSetFullScreen = !bSetFullScreen;
        ofLog()<< bSetFullScreen;
    } else if (key == OF_KEY_UP){
        angle++;
        if(angle>30) angle=30;
        kinectV1.setAngle(angle);
    } else if (key == OF_KEY_DOWN){
        angle--;
        if(angle<-30) angle=-30;
        kinectV1.setAngle(angle);
    }

}
