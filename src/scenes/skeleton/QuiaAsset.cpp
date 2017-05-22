#include "QuiaAsset.h"
#include "ofMain.h"



QuiaAsset::QuiaAsset()
{
	createSkeletonMap();
}


void QuiaAsset::setup()
{
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

}

void QuiaAsset::createSkeletonMap()
{
	skeletonMap.push_back(createImageReference("JointType_ElbowRight", "JointType_HandRight", rForeArm));
	skeletonMap.push_back(createImageReference("JointType_ElbowLeft", "JointType_HandLeft", lForeArm));
	skeletonMap.push_back(createImageReference("JointType_ShoulderRight", "JointType_ElbowRight", rUpperArm));
	skeletonMap.push_back(createImageReference("JointType_ShoulderLeft", "JointType_ElbowLeft", lUpperArm));
	skeletonMap.push_back(createImageReference("JointType_KneeRight", "JointType_AnkleRight", rShin));
	skeletonMap.push_back(createImageReference("JointType_KneeLeft", "JointType_AnkleLeft", lShin));
	skeletonMap.push_back(createImageReference("JointType_HipRight", "JointType_KneeRight", rThigh));
	skeletonMap.push_back(createImageReference("JointType_HipLeft", "JointType_KneeLeft", lThigh));
}

pair<pair<string, string>, skeletonAsset> QuiaAsset::createImageReference(string start, string end, skeletonAsset asset)
{
	return pair<pair<string, string>, skeletonAsset>();
}

