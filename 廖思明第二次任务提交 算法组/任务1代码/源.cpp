#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
double arr[3] = { 0 };
double max(double a, double b, double c) {
	if (a >= b && a >= c) return a;
	else if (b >= a && b >= c) return b;
	else return c;
}
double min(double a, double b, double c) {
	if (a <= b && a <= c) return a;
	else if (b <= a && b <= c) return b;
	else return c;
}

#ifdef _DEBUG
#pragma comment(lib,"opencv_world480d.lib")
#else
#pragma comment(lib,"opencv_world480d.lib")
#endif
int main() {
	Mat image1;
	image1 = imread("C:\\1.png");
	double S;
	double V;
	double H;
	Mat image2(image1.rows, image1.cols, CV_8UC3);
	for (int i = 0; i < image1.rows; i++) {               //通过BGR转HSV公式进行色彩空间的转换，通过at方法对每个像素值操作，以下均为套用公式过程，不做解释。
		for (int j = 0; j < image1.cols; j++) {
			arr[0]= ((double)image1.at<Vec3b>(i, j)[0]/255);
			arr[1]= ((double)image1.at<Vec3b>(i, j)[1]/255);
			arr[2]= ((double)image1.at<Vec3b>(i, j)[2]/255);
			V= max(arr[0], arr[1], arr[2]);
			image2.at<Vec3b>(i, j)[2] =(int)(V*255);
			if (V != 0)  S = (V - min(arr[0], arr[1], arr[2])) / V;
			else S = 0;
			image2.at<Vec3b>(i, j)[1] =(int)(S*255);
			if (V == arr[2]) H = 60 * (arr[1] - arr[0]) / (V - min(arr[0], arr[1], arr[2]));
			if (V == arr[1]) H = 120 + 60 * (arr[0] - arr[2]) / (V - min(arr[0], arr[1], arr[2]));
			if (V == arr[0]) H = 240 + 60 * (arr[2] - arr[1]) / (V - min(arr[0], arr[1], arr[2]));
			image2.at<Vec3b>(i, j)[0] = (int)(H*255);
		}
	}
	namedWindow("window1", WINDOW_NORMAL);
	imshow("window1", image2);
	waitKey(0);
}