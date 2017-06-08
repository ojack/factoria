#include "SkeletonAsset.h"



SkeletonAsset::SkeletonAsset()
{
}


SkeletonAsset::~SkeletonAsset()
{
}

void SkeletonAsset::load(string path, bool is_video=false)
{
	isVideo = is_video;
	if (isVideo) {
		video.load(path);
	}
	else {
		image.load(path);
	}
}

void SkeletonAsset::draw(float x, float y, float w, float h)
{
	if (isVideo) {
		video.draw(x, y, w, h);
	}
	else {
		image.draw(x, y, w, h);
	}
}

void SkeletonAsset::update()
{
}

float SkeletonAsset::getHeight()
{
	float output = 0.0f;
	if (isVideo) {
		output = 0.0f;
	}
	else {
		output = image.getHeight();
	}
	return output;
}

float SkeletonAsset::getWidth()
{
	float output = 0.0f;
	if (isVideo) {
		output = 0.0f;
	}
	else {
		output = image.getWidth();
	}
	return output;
}
