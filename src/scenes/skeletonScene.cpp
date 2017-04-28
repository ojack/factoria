//
//  skeletonScene.cpp
//  QUIA_ALZATE
//
//  Created by ojack on 12/9/16.
//
//

#include "skeletonScene.h"

void skeletonScene::setup(){
   // calibration.setup(ofVec2f(width, height), THROW_RATIO, ASPECT_RATIO);
  
   // params.add(calibration.params);
    
    
    params.setName("skeleton");
    params.add(torsoPad.set("torso pad", ofVec2f(0.1, 0.1), ofVec2f(0.0, 0.0), ofVec2f(1.0, 1.0)));
    params.add(skeletonOffset.set("skeletonOffset", ofVec2f(0, 0), ofVec2f(-200, -200), ofVec2f(200, 200)));
    params.add(limbScale.set("limbScale", ofVec2f(1.0, 1.0), ofVec2f(0, 0), ofVec2f(5.0, 5.0)));
    params.add(hipWiden.set("hip widen", 1.2, 1.0, 6.0));
    params.add(showDebug.set("show debug", false));
    params.add(showSkeletons.set("show skeletons", true));
    params.add(soundEnabled.set("SOUND ENABLED", true));
    //kinect osc
    ofTrueTypeFont smallFont, largeFont;
    smallFont.loadFont("selena.otf", 16); //http://openfontlibrary.org/en/font/selena
    
    oscKinect.setup(12345, smallFont);
    skeletons = oscKinect.getSkeletons();
    
   // renderer.setup(skeletons, smallFont);
    
    rUpperArm.load("skeleton/right-shoulder.png");
    rUpperArm.load("skeleton/right-shoulder.png");
    rForeArm.load("skeleton/right-forearm.png");
    lUpperArm.load("skeleton/left-shoulder.png");
    lForeArm.load("skeleton/left-forearm.png");
    lShin.load("skeleton/left-shin.png");
    rShin.load("skeleton/right-shin.png");
    rThigh.load("skeleton/right-thigh.png");
    lThigh.load("skeleton/left-thigh.png");
    neck.load("skeleton/neck.png");
    torso.load("skeleton/body-gears-connected.png");
    
    
    createSkeletonMap();
    
    lassoLeft.load("sonidos/up 01.wav");
    lassoRight.load("sonidos/bass 01.wav");
    fistLeft.load("sonidos/bass 04.wav");
    fistRight.load("sonidos/bass 03.wav");



    if (XML.loadFile(ofToDataPath("kinectv2/calibrationalzate2.xml"))) {
        ofLogNotice() << "loaded!";
        setupProjector();
    }
    else {
        ofLogError() << "unable to load";
    }
    
 /*   torsoMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    torsoMesh.addTexCoord(ofVec2f(torso.getWidth()/2, torso.getHeight()/2));
    torsoMesh.addTexCoord(ofVec2f(0, 0));
    torsoMesh.addTexCoord(ofVec2f(torso.getWidth(), 0));
    torsoMesh.addTexCoord(ofVec2f(torso.getWidth(), torso.getHeight()));
    torsoMesh.addTexCoord(ofVec2f(0, torso.getHeight()));
    torsoMesh.addTexCoord(ofVec2f(0, 0));*/
    
   

}

void skeletonScene::update(){
    oscKinect.update();
}

void skeletonScene::draw(){
      drawSkeletons();
}

void skeletonScene::drawSkeletons() {
    
  
    int thickness = 5;
    ofSetColor(255, 255, 255);
    ofSetLineWidth(thickness);
   
    ofLog()<<"num skels: "<<skeletons->size();
    for(int i = 0; i < skeletons->size(); i++) {
        if(soundEnabled){
            HandState handRight = skeletons->at(i).getRightHand().getState();
            HandState handLeft = skeletons->at(i).getLeftHand().getState();
            ofLogVerbose() << handRight << " prev " << rightHandState;
            if (handRight != rightHandState) {
                if(handRight!=prevRightHandState){
                    if (handRight == LASSO) {
                        lassoRight.play();
                        lassoRight.setVolume(1.0f);
                        lassoRight.setPosition(0.0f);
                    }
                    else if (handRight == OPEN) {
                        lassoRight.setVolume(0.0f);
                        fistRight.setVolume(0.0f);
                    }
                    else if(handRight == CLOSED){
                        fistRight.play();
                        fistRight.setVolume(1.0f);
                        fistRight.setPosition(0.0f);
                    }
                }
            }
            if (handLeft != leftHandState){
                if(handLeft != prevLeftHandState){
                    if (handLeft == LASSO) {
                        lassoLeft.play();
                        lassoLeft.setVolume(1.0f);
                        lassoLeft.setPosition(0.0f);
                    }
                    else if (handLeft == OPEN) {
                        lassoLeft.setVolume(0.0f);
                        fistLeft.setVolume(0.0f);
                    }
                    else if(handLeft == CLOSED){
                        fistLeft.play();
                        fistLeft.setVolume(1.0f);
                        fistLeft.setPosition(0.0f);
                    }
                }
            }
            prevRightHandState = rightHandState;
            prevLeftHandState = leftHandState;
            rightHandState = handRight;
            leftHandState = handLeft;
            
        } else {
            lassoLeft.setVolume(0.0f);
            fistLeft.setVolume(0.0f);
            lassoRight.setVolume(0.0f);
            fistRight.setVolume(0.0f);
        }
        
        for (auto limb : skeletonMap) {
            pair<string, string> joints = limb.first;
            //   ofLogVerbose() << "joint" << joints.first;
            Joint start = getJoint(joints.first, skeletons->at(i));
            Joint end = getJoint(joints.second, skeletons->at(i));
           
            ofVec2f projStart = getProjectorFromCameraPoint(ofVec3f(start.x(), start.y(), start.z()));
            ofVec2f projEnd = getProjectorFromCameraPoint(ofVec3f(end.x(), end.y(), end.z()));
            drawLimb(projStart, projEnd, limb.second);
        }
        
        ofVec3f shoulderLeft = getJoint("JointType_ShoulderLeft", skeletons->at(i)).getPoint();
        ofVec3f shoulderRight = getJoint("JointType_ShoulderRight", skeletons->at(i)).getPoint();
        ofVec3f HipRight = getJoint("JointType_HipRight", skeletons->at(i)).getPoint();
        ofVec3f HipLeft = getJoint("JointType_HipLeft", skeletons->at(i)).getPoint();
        ofVec3f SpineShoulder = getJoint("JointType_SpineShoulder", skeletons->at(i)).getPoint();
        ofVec3f Head = getJoint("JointType_Head", skeletons->at(i)).getPoint();
        drawTorso(getProjectorFromCameraPoint(shoulderLeft), getProjectorFromCameraPoint(shoulderRight), getProjectorFromCameraPoint(HipRight), getProjectorFromCameraPoint(HipLeft));
        drawHead(getProjectorFromCameraPoint(Head), getProjectorFromCameraPoint(SpineShoulder), neck);
    }
}

Joint skeletonScene::getJoint(string jointType, Skeleton skeleton){
    if (jointType == "ThumbRight") {
        return skeleton.getThumbRight();
    } else if (jointType == "SpineBase") {
        return skeleton.getSpineBase();
    } else if (jointType == "SpineMid") {
        return skeleton.getSpineMid();
    } else if (jointType == "Neck") {
        return skeleton.getNeck();
    } else if (jointType == "JointType_Head") {
        return skeleton.getHead();
    } else if (jointType == "JointType_ShoulderLeft") {
        return skeleton.getShoulderLeft();
    } else if (jointType == "JointType_ElbowLeft") {
        return skeleton.getElbowLeft();
    } else if (jointType == "WristLeft") {
        return skeleton.getWristLeft();
    } else if (jointType == "JointType_HandLeft") {
        return skeleton.getHandLeft();
    } else if (jointType == "JointType_ShoulderRight") {
        return skeleton.getShoulderRight();
    } else if (jointType == "JointType_ElbowRight") {
        return skeleton.getElbowRight();
    } else if (jointType == "WristRight") {
        return skeleton.getWristRight();
    } else if (jointType == "JointType_HandRight") {
        return skeleton.getHandRight();
    } else if (jointType == "JointType_HipLeft") {
        return skeleton.getHipLeft();
    } else if (jointType == "JointType_KneeLeft") {
        return skeleton.getKneeLeft();
    } else if (jointType == "JointType_AnkleLeft") {
        return skeleton.getAnkleLeft();
    } else if (jointType == "FootLeft") {
        return skeleton.getFootLeft();
    } else if (jointType == "JointType_HipRight") {
        return skeleton.getHipRight();
    } else if (jointType == "JointType_KneeRight") {
        return skeleton.getKneeRight();
    } else if (jointType == "JointType_AnkleRight") {
        return skeleton.getAnkleRight();
    } else if (jointType == "FootRight") {
        return skeleton.getFootRight();
    } else if (jointType == "JointType_SpineShoulder") {
        return skeleton.getSpineShoulder();
    } else if (jointType == "HandTipLeft") {
        return skeleton.getHandTipLeft();
    } else if (jointType == "ThumbLeft") {
        return skeleton.getThumbLeft();
    } else if (jointType == "HandTipRight") {
        return skeleton.getHandTipRight();
    } else {
        ofLogVerbose() << "no joint found";
    }
}



void skeletonScene::drawHead(ofVec2f start, ofVec2f end, ofImage img) {
    //ofDrawLine(start, end);
    ofSetColor(255, 255, 255);
    ofVec2f c = ofVec2f(end.x - start.x, end.y - start.y);
    float angle = ofVec2f(0, 1).angle(c);
    
    float distance = start.distance(end);
    float drawWidth = distance;
    float drawHeight = distance * 2;
    /*float drawHeight = distance / (1 - img.getWidth() / img.getHeight());
     float drawWidth = drawHeight - distance;*/
    ofPushMatrix();
    ofTranslate(start.x, start.y);
    ofRotate(angle, 0, 0, 1);
    ofTranslate(-drawWidth*limbScale->x / 2, -drawWidth*limbScale->y / 2);
    img.draw(0, 0, drawWidth*limbScale->x, drawHeight*limbScale->y);
    ofPopMatrix();
    /*	if (drawDebug) {
     ofSetColor(0, 355, 0);
     ofDrawCircle(start.x, start.y, 20);
     ofDrawCircle(end.x, end.y, 20);
     }*/
    
}

void skeletonScene::drawLimb(ofVec2f start, ofVec2f end, ofImage img) {
    //ofDrawLine(start, end);
    //img.draw(start.x, start.y);
    ofSetColor(255, 255, 255);
    ofVec2f c = ofVec2f(end.x - start.x, end.y - start.y);
    float angle = ofVec2f(0, 1).angle(c);
    
    float distance = start.distance(end);
    float drawHeight = distance / (1 - img.getWidth() / img.getHeight());
    float drawWidth = drawHeight - distance;
    ofPushMatrix();
    ofTranslate(start.x, start.y);
    ofRotate(angle, 0, 0, 1);
    ofTranslate(-drawWidth*limbScale->x / 2, -drawWidth*limbScale->y / 2);
    img.draw(0, 0, drawWidth*limbScale->x, drawHeight*limbScale->y);
    ofPopMatrix();
    
    if (showDebug) {
        ofSetColor(0, 355, 0);
        ofDrawCircle(start.x, start.y, 20);
        ofDrawCircle(end.x, end.y, 20);
    }
    
}


void skeletonScene::drawTorso(ofVec2f p1, ofVec2f p2, ofVec2f p3, ofVec2f p4) {
    //scale points based on torso pad
    ofSetColor(255, 255, 255);
    
    ofVec2f pt1 = p1;
    ofVec2f pt2 = p2;
    ofVec2f pt3 = p3;
    ofVec2f pt4 = p4;
    
    ofVec2f diff1 = pt2-pt1;
    ofVec2f diff2 = pt3-pt2;
    ofVec2f diff3 = (pt4-pt3)*hipWiden;
    ofVec2f diff4 = pt1-pt4;
    pt1 -= diff1*torsoPad->x;
    pt2 += diff1*torsoPad->x;
    pt2 -= diff2*torsoPad->y;
    pt3 += diff2*torsoPad->y;
    pt3 -= diff3*torsoPad->x;
    pt4 += diff3*torsoPad->x;
    pt4 -= diff4*torsoPad->y;
    pt1 += diff4*torsoPad->y;
    
    torso.getTexture().bind();
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(pt1.x, pt1.y);
    glTexCoord2f(torso.getWidth(), 0);
    // glTexCoord2f(1.0, 0.0);
    glVertex2f(pt2.x, pt2.y);
    //glTexCoord2f(1.0, 1.0);
    glTexCoord2f(torso.getWidth(), torso.getHeight());
    glVertex2f(pt3.x, pt3.y);
    //glTexCoord2f(0.0, 1.0);
    glTexCoord2f(0, torso.getHeight());
    glVertex2f(pt4.x, pt4.y);
    glTexCoord2f(0.0, 0.0);
    // glTexCoord2f(0, torso.getHeight());
    glVertex2f(pt1.x, pt1.y);
    
    glEnd();
    
    torso.getTexture().unbind();
    
  /*
    
    torsoMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
   // torsoMesh.clearTexCoords();
    torsoMesh.clearVertices();
    
    torsoMesh.addVertex(pt0);
    torsoMesh.addVertex(pt1);
    torsoMesh.addVertex(pt2);
    torsoMesh.addVertex(pt3);
    torsoMesh.addVertex(pt4);
    torsoMesh.addVertex(pt1);
    
    torso.getTexture().bind();
    torsoMesh.draw();
     torso.getTexture().unbind();
   // torso.getTexture().unbind();*/
    
   if (showDebug) {
        ofSetColor(255, 0, 0);
        
        ofDrawCircle(pt1.x, pt1.y, 20);
        ofDrawCircle(pt2.x, pt2.y, 20);
        ofDrawCircle(pt3.x, pt3.y, 20);
        ofDrawCircle(pt4.x, pt4.y, 20);
        
        ofSetColor(0, 0, 255);
        ofDrawCircle(p1.x, p1.y, 20);
        ofDrawCircle(p2.x, p2.y, 20);
        ofDrawCircle(p3.x, p3.y, 20);
        ofDrawCircle(p4.x, p4.y, 20);
   }
}


void skeletonScene::createSkeletonMap() {
    skeletonMap.push_back(createImageReference("JointType_ElbowRight", "JointType_HandRight", rForeArm));
    skeletonMap.push_back(createImageReference("JointType_ElbowLeft", "JointType_HandLeft", lForeArm));
    skeletonMap.push_back(createImageReference("JointType_ShoulderRight", "JointType_ElbowRight", rUpperArm));
    skeletonMap.push_back(createImageReference("JointType_ShoulderLeft", "JointType_ElbowLeft", lUpperArm));
    skeletonMap.push_back(createImageReference("JointType_KneeRight", "JointType_AnkleRight", rShin));
    skeletonMap.push_back(createImageReference("JointType_KneeLeft", "JointType_AnkleLeft", lShin));
    skeletonMap.push_back(createImageReference("JointType_HipRight", "JointType_KneeRight", rThigh));
    skeletonMap.push_back(createImageReference("JointType_HipLeft", "JointType_KneeLeft", lThigh));
}

pair<pair<string, string>, ofImage> skeletonScene::createImageReference(string start, string end, ofImage image) {
    pair<string, string> limb = make_pair(start, end);
    return make_pair(limb, image);
}


ofVec2f skeletonScene::getProjectorFromCameraPoint(ofVec3f cameraPoint) {
    cv::Mat cameraMat = (cv::Mat1d(1, 4) << cameraPoint.x, cameraPoint.y, cameraPoint.z, 1);
    cv::Mat projectorPoint = cameraMat*projectorWorldView;
    projectorPoint /= (projectorPoint.at<double>(2));
    float yPoint = width - (projectorPoint.at<double>(1) + 1)*height / 2;
    return ofVec2f((projectorPoint.at<double>(0) + 1)*width / 2 + skeletonOffset->x, yPoint+skeletonOffset->y);
}

void skeletonScene::setupProjector() {
    cv::Mat cameraPose = cv::Mat1d(4, 4);
    XML.pushTag("ProjectorCameraEnsemble");
    XML.pushTag("cameras");
    ofLogError() << XML.getNumTags("ProjectorCameraEnsemble.Camera");
    XML.pushTag("ProjectorCameraEnsemble.Camera", 0);
    XML.pushTag("pose");
    XML.pushTag("ValuesByColumn");
    XML.pushTag("ArrayOfdouble", 0);
    cameraPose.at<double>(0, 0) = XML.getValue("double", 0.0, 0);
    cameraPose.at<double>(1, 0) = XML.getValue("double", 0.0, 1);
    cameraPose.at<double>(2, 0) = XML.getValue("double", 0.0, 2);
    cameraPose.at<double>(3, 0) = XML.getValue("double", 0.0, 3);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 1);
    cameraPose.at<double>(0, 1) = XML.getValue("double", 0.0, 0);
    cameraPose.at<double>(1, 1) = XML.getValue("double", 0.0, 1);
    cameraPose.at<double>(2, 1) = XML.getValue("double", 0.0, 2);
    cameraPose.at<double>(3, 1) = XML.getValue("d5p1:Sdouble", 0.0, 3);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 2);
    cameraPose.at<double>(0, 2) = XML.getValue("double", 0.0, 0);
    cameraPose.at<double>(1, 2) = XML.getValue("double", 0.0, 1);
    cameraPose.at<double>(2, 2) = XML.getValue("double", 0.0, 2);
    cameraPose.at<double>(3, 2) = XML.getValue("double", 0.0, 3);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 3);
    cameraPose.at<double>(0, 3) = XML.getValue("double", 0.0, 0);
    cameraPose.at<double>(1, 3) = XML.getValue("double", 0.0, 1);
    cameraPose.at<double>(2, 3) = XML.getValue("double", 0.0, 2);
    cameraPose.at<double>(3, 3) = XML.getValue("double", 0.0, 3);
    XML.popTag();
    
    XML.popTag();
    XML.popTag();
    
    XML.popTag();
    XML.popTag();
    XML.popTag();
    XML.popTag();
    
    proIntrinsics = cv::Mat1d(3, 3);
    XML.pushTag("ProjectorCameraEnsemble");
    XML.pushTag("projectors");
    ofLogError() << XML.getNumTags("ProjectorCameraEnsemble.Projector");
    XML.pushTag("ProjectorCameraEnsemble.Projector", 0);
    XML.pushTag("cameraMatrix");
    XML.pushTag("ValuesByColumn");
    XML.pushTag("ArrayOfdouble", 0);
    proIntrinsics.at<double>(0, 0) = XML.getValue("double", 0.0, 0);
    proIntrinsics.at<double>(1, 0) = XML.getValue("double", 0.0, 1);
    proIntrinsics.at<double>(2, 0) = XML.getValue("double", 0.0, 2);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 1);
    proIntrinsics.at<double>(0, 1) = XML.getValue("double", 0.0, 0);
    proIntrinsics.at<double>(1, 1) = XML.getValue("double", 0.0, 1);
    proIntrinsics.at<double>(2, 1) = XML.getValue("double", 0.0, 2);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 2);
    proIntrinsics.at<double>(0, 2) = XML.getValue("double", 0.0, 0);
    proIntrinsics.at<double>(1, 2) = XML.getValue("double", 0.0, 1);// *1 + proSize.height;
    proIntrinsics.at<double>(2, 2) = XML.getValue("double", 0.0, 2);
    XML.popTag();
    XML.popTag();
    XML.popTag();
    
    proExtrinsics = cv::Mat1d(4, 4);
    XML.pushTag("pose");
    XML.pushTag("ValuesByColumn");
    XML.pushTag("ArrayOfdouble", 0);
    proExtrinsics.at<double>(0, 0) = XML.getValue("double", 0.0, 0);
    proExtrinsics.at<double>(1, 0) = XML.getValue("double", 0.0, 1);
    proExtrinsics.at<double>(2, 0) = XML.getValue("double", 0.0, 2);
    proExtrinsics.at<double>(3, 0) = XML.getValue("double", 0.0, 3);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 1);
    proExtrinsics.at<double>(0, 1) = XML.getValue("double", 0.0, 0);
    proExtrinsics.at<double>(1, 1) = XML.getValue("double", 0.0, 1);
    proExtrinsics.at<double>(2, 1) = XML.getValue("double", 0.0, 2);
    proExtrinsics.at<double>(3, 1) = XML.getValue("double", 0.0, 3);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 2);
    proExtrinsics.at<double>(0, 2) = XML.getValue("double", 0.0, 0);
    proExtrinsics.at<double>(1, 2) = XML.getValue("double", 0.0, 1);
    proExtrinsics.at<double>(2, 2) = XML.getValue("double", 0.0, 2);
    proExtrinsics.at<double>(3, 2) = XML.getValue("double", 0.0, 3);
    XML.popTag();
    XML.pushTag("ArrayOfdouble", 3);
    proExtrinsics.at<double>(0, 3) = XML.getValue("double", 0.0, 0);
    proExtrinsics.at<double>(1, 3) = XML.getValue("double", 0.0, 1);
    proExtrinsics.at<double>(2, 3) = XML.getValue("double", 0.0, 2);
    proExtrinsics.at<double>(3, 3) = XML.getValue("double", 0.0, 3);
    XML.popTag();
    XML.popTag();
    XML.popTag();
    
    cv::Mat cameraToDepth = (cv::Mat1d(4, 4) << 1, 0, 0, -69,
                             0, 1, 0, -38,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
    
    cv::Mat world = cameraPose.t(); // world matrix
    ofLogVerbose() << cameraPose;
    ofLogVerbose() << proExtrinsics;
    cv::Mat inverse = proExtrinsics.inv();
    ofLogVerbose() << inverse;
    cv::Mat view = inverse.t(); //view matrix
    ofLogVerbose() << view;
    
    proSize.width = width;
    proSize.height = height;
    
    cv::Size testSize = cv::Size(1280.0, 720.0);
    ofLogVerbose() << testSize;
    
    //calculate projector view matrix
    auto fx = proIntrinsics.at<double>(0, 0);
    auto fy = proIntrinsics.at<double>(1, 1);
    auto cx = proIntrinsics.at<double>(0, 2);
    auto cy = proIntrinsics.at<double>(1, 2);
    double n = 0.1;
    double f = 100.0;
    
    float w = width;
    float h = height;
    
    cv::Mat projectionMatrix = (cv::Mat1d(4, 4) << -(2 * fx / w), 0, -(2 * cx / w - 1), 0,
                                0, 2 * fy / h, 2 * cy / h - 1, 0,
                                0, 0, f / (f - n), -n* f / (f - n),
                                0, 0, 1, 0);
    
    cv::Mat projection = projectionMatrix.t(); // projection matrix
    
    ofLogVerbose() << projection;
    
    projectorWorldView = world*view*projection;
    
    ofLogVerbose() << projectorWorldView;
    
}