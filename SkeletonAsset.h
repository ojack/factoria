#pragma once
#include "ofMain.h"
class SkeletonAsset
{
public:
	SkeletonAsset();
	~SkeletonAsset();
	ofImage image;
	ofVideoPlayer video;
	bool isVideo;
	void load(string path, bool is_video);
	void draw(float x, float y, float w, float h);
	void update();
	float getHeight();
	float getWidth();
	
	
};

