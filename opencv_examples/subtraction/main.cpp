//
//  main.cpp
//  subtraction
//
//  Created by Yongduek Seo on 10/28/14.
//  Copyright (c) 2014 Yongduek Seo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, const char * argv[]) {

    cv::VideoCapture camera;
    int width, height;
    
    camera.open(0/*camera id*/);
    // size change for real-time
    camera.set(cv::CAP_PROP_FRAME_WIDTH, width=640);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, height=480);
    
    cv::Mat frame;
    cv::Mat_<uchar> gray(height,width), prevGray(height, width);
    cv::Mat_<uchar> binary(height,width);
    do {
        camera >> frame;
        if (frame.empty()) break;
        cv::imshow ("frame", frame);
        
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::Mat diff = gray - prevGray;
        cv::Mat abs = cv::abs(diff);
        cv::imshow ("absolute of diff", abs);
        
        float th = cv::threshold(abs, binary, 0, 255, cv::THRESH_OTSU | cv::THRESH_BINARY);
        if (th<40.) {
            th = 40.;
            cv::threshold(abs, binary, th, 255, cv::THRESH_BINARY);
        }
        printf ("th= %f\n", th);
        cv::imshow ("binary", binary);
        
        gray.copyTo (prevGray);
        
        if (cv::waitKey(1)==27) break;
    } while (true);
    

    return 0;
}
