//
//  main.cpp
//  filter_Gabor2D
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
    
//    cv::Mat kernel = cv::getGaborKernel(cv::Size(125,125), // ksize – Size of the filter returned.
//                                        7, //  sigma  – Standard deviation of the gaussian envelope.
//                                        CV_PI/10,//0,//CV_PI/4, // theta – Orientation of the normal to the parallel stripes of a Gabor function.
//                                        10000, // lambd – Wavelength of the sinusoidal factor.
//                                        .2, // gamma – Spatial aspect ratio.
//                                        0., // psi - phase offset
//                                        CV_64F // or CV_32F (float)
//                                        );

    cv::Mat kernel = cv::getGaborKernel(cv::Size(125,125), // ksize – Size of the filter returned.
                                        7, //  sigma  – Standard deviation of the gaussian envelope.
                                        0,//CV_PI/4, // theta – Orientation of the normal to the parallel stripes of a Gabor function.
                                        7*2, // lambd – Wavelength of the sinusoidal factor.
                                        1., // gamma – Spatial aspect ratio.
                                        0., // psi - phase offset
                                        CV_64F // or CV_32F (float)
                                        );

    //
    cv::Mat kernel_view;
    double minVal, maxVal;
    cv::minMaxLoc(kernel, &minVal, &maxVal); //find minimum and maximum intensities
    printf ("kernel = [%lg, %lg]\n", minVal, maxVal);
    kernel.convertTo(kernel_view, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

    cv::imshow("kernel", kernel_view);
    cv::waitKey();
    
    cv::filter2D(input, output, 0/*output depth is equal to input.depth()*/, kernel);
    
    cv::imshow("input", input);
    cv::imshow("output shapening", output);
    cv::waitKey();
    return 0;
}

// EOF //