//
//  KinectTracker.h
//  Relief2
//
//  Created by Sean Follmer on 3/24/13.
//
//

#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxKCore.h"


#ifndef __Relief2__KinectTracker__
#define __Relief2__KinectTracker__

#include <iostream>

class KinectTracker {
public:
    ofxKinect kinect;
    
    void setup();
    void exit();
    void draw(int x, int y, int width, int height, int probe_x, int probe_y);
    void drawColorImage(int x, int y, int width, int height);
    void drawDetectedObjects(int x, int y, int width, int height);
    void update();
    
    void findBalls(int hue_target, int hue_tolerance, int sat_limit, vector<Blob>& blobs);
    void findFingers(vector<ofPoint>& points);
    void findFingersAboveSurface(vector<ofPoint>& points);
    
    void setPinHeightMap(ofPixels & tempPixels);
    
    void saveDepthImage();
    void loadDepthBackground();

    void drawCount(int width, int height);
    
    vector<ofPoint>  redBalls;
    vector<ofPoint>  blueBalls;
    vector<ofPoint>  fingers; //z is relative above height map
    vector<ofPoint>  absFingers; //z is absolute (not vodka)
    
    ofPixels pinHeightMap;
    int pinHeightMapWidth = 30;
    int pinHeightMapHeight = 30;
    
    ofPoint src[4],dst[4];

    ofxCvColorImage colorImg, depthThreshold, thresholdedColorImg, scaledColorImg;
    ofxCvGrayscaleImage depthImg, depthImgBG, depthImgBGPlusSurface, depthImgFiltered, pinHeightMapImage;
    ofImage depthImageAlpha;
    ofImage colorImageAlpha;
    ofImage detectedObjectsImageAlpha;

    int frame = 0;
    int size;
    ostringstream pointLocationsText;
    
	ofxCvGrayscaleImage grayThreshNear, grayThreshFar;
	
	int nearThreshold;
	int farThreshold;
	bool bThreshWithOpenCV;

    ofxCvColorImage hsvImage;
    ofxCvGrayscaleImage hueThreshNear, hueThreshFar, hueThresh, satThresh; // the near thresholded image
    ofxCvGrayscaleImage hue,sat,bri,filtered;

    ofFbo kinectView;
    
    
    ContourFinder finger_contourFinder;
    ContourFinder ball_contourFinder;
    BlobTracker finger_tracker;
    BlobTracker ball_tracker;
    Calibration calib;
    
    ofTrueTypeFont verdana;


};

#endif /* defined(__Relief2__KinectTracker__) */
