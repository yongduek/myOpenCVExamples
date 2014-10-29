//
//  main.cpp
//  videoHomographyTracking
//
//  Created by Yongduek Seo on 10/22/14.
//  Copyright (c) 2014 Yongduek Seo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "brisk.h"

using namespace std;

struct imageModel {
    cv::Mat image;
    std::vector<cv::KeyPoint> kpts;
    cv::Mat desc;
};

int main(int argc, const char * argv[]) {

    string strVideoFilename = "video.mov";
    cv::VideoCapture video, videofile;
    int width, height;
    
    video.open(0/*camera id*/);
    video.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    video.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    

    videofile.open(strVideoFilename);
    
    if (videofile.isOpened()==false) {
        cout << "video file open failed: " << strVideoFilename << endl;
        return 0;
    }
    else {
        width = videofile.get(cv::CAP_PROP_FRAME_WIDTH);
        height = videofile.get(cv::CAP_PROP_FRAME_HEIGHT);
        printf ("! video file size=%dx%d\n", width, height);
    }

        cv::BRISK featureDetector(10/*FAST threshold*/, 4/*detection octaves*/,1.0f/*pattern scale*/);
//    cv::ORB featureDetector(1024 /*nMaxFeatures*/);
//    cv::AKAZE featureDetector;

    cv::Ptr<cv::DescriptorExtractor> dex;
    dex = (cv::Ptr<cv::DescriptorExtractor>) new aaa::BriskDescriptorExtractor();
    
    cv::Mat displayImage;
    
    clock_t clockStart = clock();
    unsigned frameCount=0;
    
    while (true) {
        cv::Mat gray;
        if (videofile.isOpened()) {
            cv::Mat frame;
            video >> frame;
            if (frame.empty()) break;
//            cv::resize(frame, frame, cv::Size(width/2,height/2));
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
//            cv::resize(gray, gray, cv::Size(width/2,height/2));
        }
        
        
        vector<cv::KeyPoint> kpts;
        cv::Mat descriptors;

        featureDetector (gray, cv::noArray(), kpts, descriptors);
        
        featureDetector.detect(gray, kpts); //(gray, cv::noArray(), kpts, descriptors);
//        featureDetector.compute(gray, kpts, descriptors);
        
        cv::drawKeypoints(gray, kpts, displayImage, cv::Scalar(100,5,5));
//        cv::drawKeypoints(gray, kpts, displayImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    
        float ellapsed = (clock()-clockStart)/(float)CLOCKS_PER_SEC;
        string msg = "frameRate= " + to_string(++frameCount/ellapsed) + " fps "
        + to_string(kpts.size()) + " points";
        cv::putText(displayImage, msg, cv::Point(20,20), 1, 1, cv::Scalar(0,0,255));
        cv::imshow ("display", displayImage);
        
        if (cv::waitKey(2)==27) break;
    }
    
    video.release();
    cout << "Finished.\n";
    return 0;
}
