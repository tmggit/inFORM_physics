//
//  HybridTokens.cpp
//  Relief2
//
//  Created by Daniel Windham on 3/18/15.
//
//

#include "HybridTokens.h"

HybridTokens::HybridTokens(KinectTracker *tracker) {
    kinectTracker = tracker;
    pinHeightMapImage.allocate(RELIEF_PROJECTOR_SIZE_X, RELIEF_PROJECTOR_SIZE_X, GL_RGBA);
}

void HybridTokens::drawHeightMap() {
    pinHeightMapImage.draw(0, 0);
}

void HybridTokens::drawGraphics() {
}

void HybridTokens::update(float dt) {
    pinHeightMapImage.begin();
    ofBackground(0);
    ofSetColor(255);

    // for now, assume a ready cube is flat and aligned to the coordinate axes
    if (kinectTracker->cubeIsReady) {
        // specify schema
        bool useStaticSecondSword = true;
        bool intersect = false;
        bool blockade = true;
        
        // known width and height of our cubes
        int width = 26;
        int height = 26;
        
        // dynamic cube
        ofPoint center = kinectTracker->currentBlob.centroid;
        
        // for now, hardcode a description of the static block
        ofPoint fixedCenter(35, 70);
        
        // draw dynamic sword up
        ofSetColor(140);
        int left, right, top, bottom;
        left = (kinectTracker->cubeCenterX - 13) * RELIEF_PROJECTOR_SIZE_X / 190;
        right = (kinectTracker->cubeCenterX + 13) * RELIEF_PROJECTOR_SIZE_X / 190;
        top = (kinectTracker->cubeCenterY - 13 - 3 * height) * RELIEF_PROJECTOR_SIZE_X / 190;
        bottom = (kinectTracker->cubeCenterY - 13 - 0.3 * height) * RELIEF_PROJECTOR_SIZE_X / 190;
        ofRect(left, top, right - left, bottom - top);
        
        if (useStaticSecondSword) {
            // draw static sword right
            ofSetColor(140);
            int fixedLeft, fixedRight, fixedTop, fixedBottom;
            fixedLeft = (fixedCenter.x + 13 + 0.3 * height) * RELIEF_PROJECTOR_SIZE_X / 190;
            fixedRight = (fixedCenter.x + 13 + 3 * height) * RELIEF_PROJECTOR_SIZE_X / 190;
            fixedTop = (fixedCenter.y - 13) * RELIEF_PROJECTOR_SIZE_X / 190;
            fixedBottom = (fixedCenter.y + 13) * RELIEF_PROJECTOR_SIZE_X / 190;
            ofRect(fixedLeft, fixedTop, fixedRight - fixedLeft, fixedBottom - fixedTop);
            
            // draw sword intersections
            if (intersect) {
                ofSetColor(255);
                if (fixedLeft < right && fixedRight > left && fixedTop < bottom && fixedBottom > top) {
                    int overlapLeft, overlapRight, overlapTop, overlapBottom;
                    overlapLeft = left < fixedLeft ? fixedLeft : left;
                    overlapRight = right < fixedRight ? right : fixedRight;
                    overlapTop = top < fixedTop ? fixedTop : top;
                    overlapBottom = bottom < fixedBottom ? bottom : fixedBottom;
                    ofRect(overlapLeft, overlapTop, overlapRight - overlapLeft, overlapBottom - overlapTop);
                }
            }
            
            // draw blockade
            if (blockade) {
                int closeDistance = 13 * RELIEF_PROJECTOR_SIZE_X / 190;
                if (left < fixedRight + closeDistance) {
                    int adjWidth = width * RELIEF_PROJECTOR_SIZE_X / 190;
                    int adjHeight = height * RELIEF_PROJECTOR_SIZE_X / 190;
                    int cubeBottom = (kinectTracker->cubeCenterY + 13) * RELIEF_PROJECTOR_SIZE_X / 190;
                    ofRect(fixedRight - adjWidth / 4, cubeBottom - adjHeight, adjWidth / 4, adjHeight);
                }
            }
        }
    }
    pinHeightMapImage.end();
}

void HybridTokens::keyPressed(int key) {
    if (key == 'q') {
    }
    
    if (key == 'w') {
    }
}