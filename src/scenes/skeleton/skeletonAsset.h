#include "ofMain.h"
class skeletonAsset {
	skeletonAsset();
public:
	void setPath(string path_);
	void load(string path_);
	void draw();
	string path;
};