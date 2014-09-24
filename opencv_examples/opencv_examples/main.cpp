//
//  main.cpp
//  opencv_examples
//
//  Created by Yongduek Seo on 2014. 9. 24..
//  Copyright (c) 2014년 Yongduek Seo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main(int argc, const char * argv[])
{
    // bit plane images
    cv::Mat I = cv::imread ("fruits.jpg"); // color image
    cv::Mat J;
    std::vector< cv::Mat_<uchar> > dest_image(8);
    
    cv::cvtColor(I, J, CV_BGR2GRAY);
    
    cv::Mat_<uchar> image = J; // soft copy of J
    
    for (int i=0; i< 8; i++) {
        unsigned char mask = 1 << i;
        
        for (int r=0; r<J.rows; r++)
            for (int c=0; c<J.cols; c++) {
                uchar pixel = image(r,c);
                uchar dest_pixel = pixel & mask;
                
                dest_image[i](r,c) = dest_pixel;
            }
    }
    
    cv::imshow ("src image", I);
    cv::waitKey();
    return 0;
}

