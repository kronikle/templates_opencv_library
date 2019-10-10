#include <iostream>
#include <sstream>
#include <array>
#include <string.h>

#include <opencv4/opencv2/opencv.hpp>

#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using namespace cv;
using boost::asio::ip::udp;

float w_window = 200.0;
float h_window = 200.0;

void send_udp(int _x, int _y) {
    try {
        const char ip[] = "127.0.0.1";
        const char port[] = "2002";

        boost::asio::io_context io_context;

        udp::resolver resolver(io_context);
        udp::endpoint receiver_endpoint =
                *resolver.resolve(udp::v4(), ip, port).begin(); // ("IP", "port")

        udp::socket socket(io_context);
        socket.open(udp::v4());



        //boost::array<char, 2> send_buf = {{ (char)_x, (char)_y}}; // buono per pure data

        string s = to_string(_x) + '|' + to_string(_y);

//        char * my_char = new char[s.length() + 1];
//        strcpy(my_char, s.c_str());
        char my_char[1024];
        strcpy(my_char, s.c_str());
        cout << "my_char: " << my_char << endl;

        string culo = "culo";
        char test[] = "culo";



        socket.send_to(boost::asio::buffer(/*send_buf*/ my_char), receiver_endpoint);

        /// manage message back from server
        //    boost::array<char, 128> recv_buf;
        //    udp::endpoint sender_endpoint;
        //    size_t len = socket.receive_from(
        //        boost::asio::buffer(recv_buf), sender_endpoint);
        //
        //    std::cout.write(recv_buf.data(), len);
        ///[end] manage message back from server
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void mouse_callback(int event, int x, int y, int flag, void *param) {
    if (event == EVENT_MOUSEMOVE) {
        cout << "(" << x << ", " << y << ")" << endl;

        int norm_x = (x / w_window) * 255;
        int norm_y = (y / h_window) * 255;

        send_udp(norm_x, norm_y);
    }
}

int main() {


    cv::Mat3b img(w_window, h_window, Vec3b(0, 255, 0));

    namedWindow("example");
    setMouseCallback("example", mouse_callback);

    imshow("example", img);
    waitKey();

    return 0;
}