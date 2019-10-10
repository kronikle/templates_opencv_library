#include <opencv4/opencv2/opencv.hpp>

#include <iostream>


using namespace std;
using namespace cv;

int mouse_x;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
    if (event == EVENT_MOUSEMOVE) {
        cout << "(" << x << ", " << y << ")" << endl;
    }
}


 int main(){  
    cv::Mat3b img(200, 200, Vec3b(0, 255, 0));

    namedWindow("example");
    setMouseCallback("example", mouse_callback);

    imshow("example", img);
    waitKey();

    return 0;
}

