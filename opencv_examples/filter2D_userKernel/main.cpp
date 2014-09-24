//
//  main.cpp
//  filter2D_userKernel
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
    if (input.data==0) {
        cerr << "image open error" << endl;
        return 0;
    }
    cv::Mat output;
    
    cv::Mat kernel(3,3,CV_32FC1);

    // Lapalcian-based image sharpening filter
    kernel = 0.; // initialize
    kernel.at<float>(1,1) = 5;
    kernel.at<float>(0,1) = -1;
    kernel.at<float>(1,0) = -1;
    kernel.at<float>(1,2) = -1;
    kernel.at<float>(2,1) = -1;
    
    cout << kernel << endl;
  
    cv::filter2D(input, output, 0/*output depth is equal to input.depth()*/, kernel);
    
    cv::imshow("input", input);
    cv::imshow("output shapening", output);
    cv::waitKey();
    return 0;
}