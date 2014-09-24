//
//  main.cpp
//  bit_planes
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
    cv::Mat input = cv::imread ("fruits.jpg"); // color image
    cv::Mat J;
    cv::Mat dest_image[8];
    
    cv::cvtColor(input, J, CV_BGR2GRAY);
    
    cv::Mat_<uchar> image = J; // soft copy of J
    
    for (int i=0; i< 8; i++) {
        unsigned char mask = 1 << i;
        dest_image[i] = cv::Mat::zeros(J.size(), J.type());
        cv::Mat_<uchar> dest = dest_image[i];
        for (int r=0; r<J.rows; r++)
            for (int c=0; c<J.cols; c++) {
                uchar pixel = image(r,c);
                uchar dest_pixel = pixel & mask;
                
                dest(r,c) = dest_pixel << (7-i);
            }
        char name[1024];
        sprintf (name, "bit plane %d", i);
        cv::imshow (name, dest_image[i]);
    }
    
    cv::imshow ("src image", J);
    cv::waitKey();
    return 0;
}

// EOF //