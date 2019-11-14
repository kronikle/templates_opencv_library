/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: samuele
 *
 * Created on October 10, 2019, 6:24 PM
 */

#include <math.h>
#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>

using namespace cv;
using namespace std;


/*
 * 
 */


const int w = 500;
int levels = 3;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

static void help()
{
    cout
    << "\nThis program illustrates the use of findContours and drawContours\n"
    << "The original image is put up along with the image of drawn contours\n"
    << "Usage:\n"
    << "./contours2\n"
    << "\nA trackbar is put up which controls the contour level from -3 to 3\n"
    << endl;
}

static void on_trackbar(int, void*)
{
    Mat cnt_img = Mat::zeros(w, w, CV_8UC3);
    int _levels = levels - 3;
    drawContours( cnt_img, contours, _levels <= 0 ? 3 : -1, Scalar(128,255,255),
                  3, LINE_AA, hierarchy, std::abs(_levels) );
    imshow("contours", cnt_img);
}

int main( int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv, "{help h||}");
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    
    // Read image
    Mat im = imread("blob.jpg", IMREAD_GRAYSCALE);


    namedWindow("image", 1);
    imshow("image", im);
    //Extract the contours so that
    vector<vector<Point> > contours0;
    findContours( im, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    contours.resize(contours0.size());
    for( size_t k = 0; k < contours0.size(); k++ )
        approxPolyDP(Mat(contours0[k]), contours[k], 3, true);
    namedWindow( "contours", 1 );
    createTrackbar( "levels+3", "contours", &levels, 7, on_trackbar );
    on_trackbar(0,0);
    waitKey();
    return 0;
}

