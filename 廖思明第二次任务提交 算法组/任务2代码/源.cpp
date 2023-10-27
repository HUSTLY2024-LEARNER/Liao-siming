#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace std;
using namespace cv;

#ifdef _DEBUG
#pragma comment(lib,"opencv_world480d.lib")
#else
#pragma comment(lib,"opencv_world480d.lib")
#endif

int main() {
	Mat image;
	image = imread("C:\\1.png");
	int width,height;
	cin >> width;            //输入缩放后图片期望的长宽，从而得出缩放任意倍率
	cin >> height;
	double change_w = (double)image.cols/width;
	double change_h = (double)image.rows/height;
	Mat src(width, height,CV_8UC3);
	for (int i = 0; i < height; i++) {                      //通过双线性插值法实现缩放操作，核心是用原图中相邻四相邻像素点加权得出应插入像素值
		for (int j = 0; j < width; j++) {
			int image_x_int = (int)((j+0.5)*change_w - 0.5);
			int image_y_int = (int)((i+0.5)*change_h-0.5);
			double u = (double)(((j + 0.5)*change_w - 0.5)-image_x_int);
			double v = (double)(((i + 0.5)*change_h - 0.5)-image_y_int);
			if (image_x_int+1== image.cols||image_y_int+1 == image.rows) {
				src.at<Vec3b>(i, j) = image.at<Vec3b>(image_y_int, image_x_int);
				continue;
			}
			src.at<Vec3b>(i, j)=(1. - v)*(1. - u)*image.at<Vec3b>(image_y_int, image_x_int)+(1. - v) * u *image.at<Vec3b>(image_y_int, image_x_int + 1)+ v * (1. - u) * image.at<Vec3b>(image_y_int + 1, image_x_int) + u * v * image.at<Vec3b>(image_y_int + 1, image_x_int + 1);
		}
	}
	namedWindow("window1");
	imshow("window1", src);
	waitKey(0);
}