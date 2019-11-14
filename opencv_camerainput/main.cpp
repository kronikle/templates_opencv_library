#include "opencv2/opencv.hpp"
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

int main(int, char**) {
    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened()) // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("output", 1);
    for (;;) {
        Mat frame;
        cap >> frame; // get a new frame from camera

        imshow("output", frame);
        if (waitKey(0) >= 0) break; // 30 defines speed of video
    }
    return 0;
}
