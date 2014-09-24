//
//  main.cpp
//  filterGaussian
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
    cv::Mat output_sep, output_gblur;
    
    cv::Mat kernelGaussian = cv::getGaussianKernel(11/*11x1*/, 0/*auto*/);
    
    cout << kernelGaussian << endl;

    cv::sepFilter2D(input, output_sep, -1/*the same as input*/, kernelGaussian, kernelGaussian);
    
    cv::GaussianBlur(input, output_gblur, cv::Size(11,11), 0/*auto, using ksize*/);
    
    cv::imshow ("src image", input);
    cv::imshow ("gaussian sepFilter2D", output_sep);
    cv::imshow ("gaussian GaussianBlur", output_gblur);
    
    cv::waitKey();
    return 0;
}

// EOF //