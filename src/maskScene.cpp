//
//  maskScene.cpp
//  QUIA_ALZATE
//
//  Created by ojack on 12/13/16.
//
//

#include "maskScene.h"

void maskScene::setup(){
    renderFbo.allocate(width, height);
    renderFbo.begin();
    ofClear(0, 0, 0);
    renderFbo.end();
}

void maskScene::update(){
    kinectV1->update();
    kinectV1->getContours();
    
    
    
}

void maskScene::draw(){
    vector <ofPolyline> contours = kinectV1->getProjectedContours();
   // ofLog()<<"drawing mask " << contours.size();
    for(auto contour: contours){
        ofBeginShape();
        ofFill();
        ofSetColor(255, 255, 255);
        for (auto point: contour.getVertices()) {
          //  ofLog() << point.x << point.y;
            ofVertex(point.x, point.y);
        }
        ofVertex(contour.getVertices().at(0).x, contour.getVertices().at(0).y);
        ofEndShape();
    }
    
  
}