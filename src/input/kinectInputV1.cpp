//
//  inputManager.cpp
//  QUIA_ALZATE
//
//  Created by ojack on 12/9/16.
//
//

#include "kinectInputV1.h"

void kinectInputV1::setup(int minDist, int maxDist){
    params.setName("kinect");
    params.add(nearThreshold.set("nearThresh", 230, 0, 255));
    params.add(farThreshold.set("farThresh", 10, 0, 255));
    params.add(minArea.set("minArea", 1000, 0, 5000));
    params.add(maxArea.set("maxArea", 70000, 15000, 150000));
    params.add(threshold.set("threshold", 15, 1, 100));
    params.add(persistence.set("persistence", 15, 1, 100));
    params.add(maxDistance.set("maxDistance", 32, 1, 100));
    params.add(globalOffset.set("global offset", ofVec2f(0.0, 0.0), ofVec2f(-100.0, -100.0), ofVec2f(100.0, 100.0)));
    bIsFrameNew = false;
    
    
#ifdef USE_VIDEO
    player.load("kinectv1/atwood.mov");
    player.play();
    player.setLoopState(OF_LOOP_NORMAL);
    
    graypixels = new unsigned char[512*424];
    filteredDepthImage.allocate(512, 424, OF_IMAGE_GRAYSCALE);
#else
    
    kpt.loadCalibration("kinectv1/calibration.xml");
    kinect.init();
    kinect.open();
    kinect.setRegistration(true);
    kinect.setDepthClipping(minDist, maxDist);
    graypixels = new unsigned char[kinect.width*kinect.height];
    filteredDepthImage.allocate(kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
#endif
    
    
}



void kinectInputV1::update(){
#ifdef USE_VIDEO
    player.update();
    player.setVolume(0);
    if (player.isFrameNew() == true){
        bIsFrameNew = true;
        unsigned char * data  = player.getPixels().getData();
        for (int i = 0; i < 512*424; i++){
            if( data[i*3] < nearThreshold &&  data[i*3] > farThreshold) {
                graypixels[i] = data[i*3];
            } else {
                graypixels[i] = 0;
            }
        }
        filteredDepthImage.setFromPixels(graypixels, 512, 424, OF_IMAGE_GRAYSCALE);
        
        if(bMirror){
            filteredDepthImage.mirror(false, true);
        }
    } else {
        bIsFrameNew = false;
    }
#else
    kinect.update();
    if(kinect.isFrameNew()) {
        bIsFrameNew = true;
        texDepth.loadData( kinect.getDepthPixels() );
        unsigned char * data  = kinect.getDepthPixels().getData();
 
        for (int i = 0; i < kinect.width*kinect.height; i++){
            if( data[i] < nearThreshold &&  data[i] > farThreshold) {
                graypixels[i] = data[i];
            } else {
                graypixels[i] = 0;
            }
        }
        
        filteredDepthImage.setFromPixels(graypixels, kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
        if(bMirror){
            filteredDepthImage.mirror(false, true);
        }
    } else {
        bIsFrameNew = false;
    }
    #endif
}

ofVec3f kinectInputV1::getClosestPoint(){
    int img_width;
    int img_height;
    ofRectangle bounds = contourFinder.getPolyline(0).getBoundingBox();
    #ifdef USE_VIDEO
        img_width = 512;
        img_height = 424;
    #else
        img_width = kinect.width;
        img_height = kinect.height;
    #endif
    
    int closestPoint = 0;
    ofVec2f position = ofVec2f(0, 0);
    ofLog() << "bounds" << bounds.getMinX();
    for (int i = bounds.getMinX(); i < bounds.getMaxX(); i++){
        for(int j = bounds.getMinY(); j < bounds.getMaxY(); j++){
         //img_width*img_height; i++){
            if( graypixels[j*img_width + i] >= closestPoint){
                closestPoint = graypixels[j*img_width + i];
                position = ofVec2f(i, j);
            }
        }
    }
    #ifdef USE_VIDEO
        return ofVec3f(position.x, position.y, closestPoint);
     #else
        ofVec3f worldPoint = kinect.getWorldCoordinateAt(position.x, position.y);
        ofVec2f projectedPoint = kpt.getProjectedPoint(worldPoint);
        return ofVec3f(projectedPoint.x*width, projectedPoint.y*height, closestPoint);
     #endif
}

void kinectInputV1::setAngle(int angle){
#ifndef USE_VIDEO
    kinect.setCameraTiltAngle(angle);
#endif
    
}

void kinectInputV1::getContours(){
    if(bIsFrameNew){
        contourFinder.setSortBySize(true);
        contourFinder.setThreshold(threshold);
        contourFinder.setMinArea(minArea);
        contourFinder.setMaxArea(maxArea);
        contourFinder.findContours(filteredDepthImage);
        contourFinder.getTracker().setPersistence(persistence);
        contourFinder.getTracker().setMaximumDistance(maxDistance);
    }
}

vector <ofPolyline> kinectInputV1::getProjectedContours(){
    //if using video, dont calculate projection
#ifdef USE_VIDEO
    return contourFinder.getPolylines();
#else
    if(bIsFrameNew){
        projectedContours.clear();
        
        for(int i = 0; i < contourFinder.size(); i++) {
            vector<cv::Point> points = contourFinder.getContour(i);
            
            //map coordinates to projector coordinates
            ofPolyline line;
            for (int j=0; j<points.size(); j++) {
                ofVec3f worldPoint = kinect.getWorldCoordinateAt(points[j].x, points[j].y);
                ofVec2f projectedPoint = kpt.getProjectedPoint(worldPoint);
                line.addVertex(ofVec3f(width * projectedPoint.x, height * projectedPoint.y));
            }
            projectedContours.push_back(line);
        }
        
        
    }
    return projectedContours;
#endif
}

void kinectInputV1::draw(){
    ofPushMatrix();
#ifdef USE_VIDEO
    player.draw(0,0);
    filteredDepthImage.draw(512,0);
    
#else
    //kinect.draw(0, 0);
    texDepth.draw(0,0);
   // filteredDepthImage.draw(512,0);
#endif
  //  ofTranslate(512, 0);
   // contourFinder.draw();
    ofPopMatrix();
}