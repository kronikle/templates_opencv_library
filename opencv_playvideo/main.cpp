#include <opencv2/videoio.hpp>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int, char**) {
    VideoCapture cap(/*0*/ "1K1A0412.MOV"); // open the default camera
    if (!cap.isOpened()) // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges", 1);
    for (;;) {
        Mat frame;
        cap >> frame; // get a new frame from camera

        if (cap.get(CAP_PROP_POS_FRAMES) == cap.get(CAP_PROP_FRAME_COUNT)) {
            cap.set(CAP_PROP_POS_FRAMES, 0);
        }

        imshow("edges", frame);
        if (waitKey(30) >= 0) break; // 30 defines speed of video
    }

    return 0;
}
