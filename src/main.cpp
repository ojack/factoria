#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2); //we define the OpenGL version we want to use
    settings.width = 1280;
    settings.setPosition(ofVec2f(0, 0));
    settings.height = 720;
    settings.windowMode = OF_WINDOW;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    //Init projection screen
   
    settings.setPosition(ofVec2f(1400, 0));
    settings.height = 720;
    settings.width = 1280;
    settings.shareContextWith = mainWindow;
    //settings.multiMonitorFullScreen = true;
    //settings.windowMode = OF_FULLSCREEN;
    shared_ptr<ofAppBaseWindow> projectionWindow = ofCreateWindow(settings);
    projectionWindow->setVerticalSync(false);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupProjection();
    ofAddListener(projectionWindow->events().draw,mainApp.get(),&ofApp::drawProjection);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
