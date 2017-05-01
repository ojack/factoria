#include "sceneManager.h"

//---------------------------------------------------------------
void sceneManager::setup(){
    
    // traditional for loop
    for (int i = 0; i < scenes.size(); i++){
        scenes[i]->setup();
        gui->add(scenes[i]->params);
    }
    
    // range based for loop
    //    for (auto scene : scenes){
    //        scene->setup();
    //    }
    //
    currentScene = 0;
    ofLog() << "loading: "<< scenes[currentScene]->settingsFile;
    gui->loadFromFile(scenes[currentScene]->settingsFile);
}

void sceneManager::nextScene(){
    currentScene++;
    currentScene %= scenes.size();
    ofLog() << "loading: "<< scenes[currentScene]->settingsFile;
    gui->loadFromFile(scenes[currentScene]->settingsFile);
}

void sceneManager::randomScene(){
    int newIndex = (int)ofRandom(0, scenes.size());
    if(newIndex == currentScene){
        nextScene();
    } else {
        currentScene = newIndex;
    }
}

//---------------------------------------------------------------
void sceneManager::update(){
    scenes[currentScene]->update();
    
}
void sceneManager::saveCurrentSettings(){
    ofLog() << "saving: "<< scenes[currentScene]->settingsFile;
    gui->saveToFile(scenes[currentScene]->settingsFile);
}
//---------------------------------------------------------------
void sceneManager::draw(){
    ofPushStyle();
    scenes[currentScene]->draw();
    ofPopStyle();
}

void sceneManager::clear(){
   // scenes[currentScene]->clear();
}