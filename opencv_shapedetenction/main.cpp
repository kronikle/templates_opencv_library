#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>



using namespace cv;
using namespace std;

const int w = 500;
int levels = 3;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

static void on_trackbar(int, void*)
{
    Mat cnt_img = Mat::zeros(w, w, CV_8UC3);
    int _levels = levels - 3;
    drawContours( cnt_img, contours, _levels <= 0 ? 3 : -1, Scalar(128,255,255),
                  3, LINE_AA, hierarchy, std::abs(_levels) );
    imshow("contours", cnt_img);
}

int main(int argc, char** argv)
{
 
    // Loads an image
    Mat src = imread( "blob.jpg", IMREAD_COLOR );
    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        return -1;
    }
    
    
    Mat gray;
    
    cvtColor(src, gray, COLOR_BGR2GRAY);
    
    medianBlur(gray, gray, 5);
    
    vector<Vec3f> circles;
    
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/8,  // change this value to detect circles with different distances to each other
                 100, 30, 1, 100 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }
     
    
    //Extract the contours so that
    vector<vector<Point> > contours0;

    findContours(gray, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    contours.resize(contours0.size());

    

    for (size_t k = 0; k < contours0.size(); k++ )
        approxPolyDP(Mat(contours0[k]), contours[k], 3, true);
    namedWindow( "contours", 1 );
    createTrackbar( "levels+3", "contours", &levels, 7, on_trackbar );
    on_trackbar(0,0);
    
   
   
    
    
    
    imshow("detected circles", src);
    waitKey();
    return 0;
}