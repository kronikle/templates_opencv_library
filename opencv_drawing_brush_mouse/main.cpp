#include <opencv4/opencv2/core/core.hpp>
#include<opencv4/opencv2/imgproc/imgproc.hpp>
#include<opencv4/opencv2/highgui/highgui.hpp>
#include<opencv4/opencv2/ml/ml.hpp>
#include<iostream>

using namespace std;
using namespace cv;

// drawing_vars
int radius = 5;
Mat img;
int ix = 1;
int iy = 1;
//mouse callback function

void draw_mousebrush(int event, int x, int y, int, void* param) {
    if (event == EVENT_LBUTTONDOWN) {
        cout << "x = " << x
                << "\t y = " << y
                << endl;
        circle(img, Point(x, y), 10, Scalar(255, 0, 0), 10);
    }
    if (event == EVENT_MOUSEMOVE) {
        circle(img, Point(x, y), 3, Scalar(255, 255, 255), -1);
    }
    if (event == EVENT_RBUTTONDOWN) {
        img = Mat::zeros(600, 800, CV_8UC3);
    }
    // line(img, Point(10, 10), Point(x, y), Scalar(0, 0, 255), 3);
}


// Function prototypes
void on_mouse(int, int, int, int, void*);

vector<Point> linePoints(int x0, int y0, int x1, int y1) {
    vector<Point> pointsOfLine;

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;) {
        pointsOfLine.push_back(Point(x0, y0));
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 >-dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
    return pointsOfLine;
}

// Public parameters
Mat image(600, 800, CV_8UC3, Scalar(220, 220, 220));
vector<Point> points;
int roi_x0 = 0, roi_y0 = 0, roi_x1 = 0, roi_y1 = 0;
bool start_draw = false;

// Window name for visualisation purposes
const string window_name = "OpenCV Mouse Event Demo";

// FUNCTION : Mouse response for selecting objects in images
// If left button is clicked, start drawing a rectangle and circle as long as mouse moves
//If right button is clicked, look what will happen !
// Stop drawing once a new left click is detected by the on_mouse function

void on_mouse(int event, int x, int y, int, void *) {
    // Action when left button is clicked
    if (event == EVENT_LBUTTONDOWN) {

        /* crea vertici ad ogni click
        if (!start_draw) {
            roi_x0 = x;
            roi_y0 = y;
            start_draw = true;
        } else {
            roi_x1 = x;
            roi_y1 = y;
            start_draw = false;
            vector<vector<Point> > contours;
            contours.push_back(linePoints(roi_x0, roi_y0, roi_x1, roi_y1));
            drawContours(image, contours, 0, Scalar(0, 0, 0), FILLED, 8);
            imshow(window_name, image);
        }
         * */
    }
    // Action when mouse is moving
    if ((event == EVENT_MOUSEMOVE)) {
        if(event==EVENT_FLAG_ALTKEY){
            cout << "dragging" << endl;
        }
        roi_x1 = x;
            roi_y1 = y;
            start_draw = false;
            vector<vector<Point> > contours;
            contours.push_back(linePoints(roi_x0, roi_y0, roi_x1, roi_y1));
            drawContours(image, contours, 0, Scalar(0, 0, 0), FILLED, 8);
            imshow(window_name, image);
        // Redraw bounding box and rectangle
        Mat current_view;
        image.copyTo(current_view);

        line(current_view, Point(roi_x0, roi_y0), Point(x, y), Scalar(0, 0, 255));
        imshow(window_name, current_view);
        roi_x0 = x;
        roi_y0 = y;
    }
}

int main() {
    /*
     * versione semplice a pallini
    img = Mat::zeros(600, 800, CV_8UC3);
    //img.setTo(Scalar(255, 0, 0));

    if (img.empty()) {
        cout << "\nerror reading image" << endl;
        // _getch();
        return -1;
    }
    namedWindow("Image", 1);
    // imshow("Image", img);
    setMouseCallback("Image", draw_mousebrush);
    
    
            
    
    
    while (waitKey(20) != 27) // wait until ESC is pressed
    {
        imshow("Image", img);
        
    }
     */

    // Init window interface and couple mouse actions
    namedWindow(window_name, WINDOW_AUTOSIZE);
    setMouseCallback(window_name, on_mouse);

    imshow(window_name, image);

    int key_pressed = 0;

    do {
        
        // Keys for processing
        // Based on the universal ASCII code of the keystroke: http://www.asciitable.com/
        //      c = 99          add rectangle to current image
        //      <ESC> = 27      exit program
        key_pressed = 0xFF & waitKey(0);
        if (key_pressed == 99) {
            image = Scalar(220 & rand(), 220, 220);
            imshow(window_name, image);
        }
    }        // Continue as long as the <ESC> key has not been pressed
    while (key_pressed != 27);

    // Close down the window
    destroyWindow(window_name);
    return 0;
}