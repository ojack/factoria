#pragma once
#include "ofMain.h"
#include "skeletonAsset.h"
class skeletonImage: public skeletonAsset{
public:
	skeletonImage();
	ofImage image;
	void load();
	void draw();
};

