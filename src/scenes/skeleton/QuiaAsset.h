#pragma once
#include "ofMain.h"
#include "skeletonAsset.h"
#include "skeletonManager.h"
class QuiaAsset: public skeletonManager
{
public:
	QuiaAsset();
	skeletonAsset rUpperArm;
	skeletonAsset rForeArm;
	skeletonAsset lUpperArm;
	skeletonAsset lForeArm;
	skeletonAsset lShin;
	skeletonAsset rShin;
	skeletonAsset rThigh;
	skeletonAsset lThigh;
	skeletonAsset neck;
	skeletonAsset torso;
	ofTexture torsoTexture;
	void setup();
	void createSkeletonMap();
	pair<pair<string, string>, skeletonAsset> createImageReference(string start, string end, skeletonAsset asset);
	vector<pair<pair<string, string>, skeletonAsset>> skeletonMap;

};

