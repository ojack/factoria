#pragma once

#include "ofMain.h"
#include "baseScene.h"


class maskScene : public baseScene{
    
public:
    using baseScene::baseScene;
    
    void setup();
    void update();
    void draw();
    //void clear();
    
   
};
