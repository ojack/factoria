

#include "globosScene.h"

void globosScene::setup(){
    params.setName("globos");
    params.add(maquinaOpacity.set("maquina opacity", 0.0, 0.0, 1.0));
    params.add(videoScale.set("video scale", ofVec2f(1.0, 1.0), ofVec2f(0.0, 0.0), ofVec2f(4.0, 4.0)));
    
  //  for(globo)
   // initVid(globos[0], "video/derecha.mov");
   // initVid(globos[1], "video/duerme.mov");
    //initVid(globos[2], "video/sonrie.mov");
    
   // maquina = new ofVideoPlayer();
    //initVid(maquina, "video/maquina.mov");
    
    globos[0].loadMovie("globos/derecha.mov");
    globos[1].loadMovie("globos/duerme.mov");
    globos[2].loadMovie("globos/sonrie.mov");
    maquina.loadMovie("globos/maquina.mov");
    
    
    maquina.setLoopState(OF_LOOP_PALINDROME);
    globos[0].setLoopState(OF_LOOP_PALINDROME);
    globos[1].setLoopState(OF_LOOP_PALINDROME);
    globos[2].setLoopState(OF_LOOP_PALINDROME);
    
    globos[0].play();
    globos[1].play();
    globos[2].play();
    maquina.play();
    
    crossfadeFbo.allocate(640, 480);
    crossfadeFbo.begin();
    ofClear(0, 0, 0);
    crossfadeFbo.end();
    
    renderFbo.allocate(width, height);
    renderFbo.begin();
    ofClear(0, 0, 0);
    renderFbo.end();
}

/*void initVid(ofVideoPlayer  vid, string filePath){
    vid.loadMovie(filePath);
    vid.setLoopState(OF_LOOP_PALINDROME);
    vid.play();
}*/

bool comparePosition( ofPolyline &a, ofPolyline &b){
    return a.getCentroid2D().x < b.getCentroid2D().x;
}

void globosScene::update(){
    kinectV1->update();
    kinectV1->getContours();
    
    for(int i = 0; i < 3; i++){
        globos[i].update();
    }
    maquina.update();
    
    ofBackground(0);
    ofSetColor(255, 255, 255);
     renderFbo.begin();
    ofClear(0, 0, 0);
    renderFbo.end();
    

        crossfadeFbo.begin();
        ofEnableAlphaBlending();
        ofClear(0);
        ofSetColor(255, 255, 255, 255-255*maquinaOpacity);
        globos[1].draw(0, 0, crossfadeFbo.getWidth(), crossfadeFbo.getHeight());
        ofFill();
        ofSetColor(255, 255, 255, 255*maquinaOpacity);
        maquina.draw(0, 0, crossfadeFbo.getWidth(), crossfadeFbo.getHeight());
        ofFill();
        ofDisableAlphaBlending();
        crossfadeFbo.end();
        
    
}

void globosScene::draw(){
   
    vector<ofPolyline> contours = kinectV1->getProjectedContours();
    ofSort(contours, comparePosition);
    
    if(contours.size() ==1){
        ofPoint center = contours.at(0).getCentroid2D();
        ofRectangle boundingBox = contours.at(0).getBoundingBox();
        float width = boundingBox.width*videoScale->x;
        float height = boundingBox.height*videoScale->y;
        crossfadeFbo.draw(center.x-width/2, center.y-height/2, width, height);
        
        ofVec3f closest = kinectV1->getClosestPoint();
        ofPushMatrix();
        ofSetColor(255, 0, 0);
        ofDrawCircle(closest.x,closest.y, 20);
        ofLog() << closest;
        ofPopMatrix();
        
    } else {
        for(int i = 0; i < contours.size(); i++) {
            if(i < 3){
                ofPoint center = contours.at(i).getCentroid2D();
                ofRectangle boundingBox = contours.at(i).getBoundingBox();
                float width = boundingBox.width*videoScale->x;
                float height = boundingBox.height*videoScale->y;
                /*if(i==1){
                    crossfadeFbo.draw(center.x-width/2, center.y-height/2, width, height);
                } else {*/
                    globos[i].draw(center.x-width/2, center.y-height/2, width, height);
               // }
            }
        }
    }
    
   
    

}