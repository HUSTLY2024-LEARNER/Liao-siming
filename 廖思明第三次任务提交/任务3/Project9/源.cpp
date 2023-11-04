#include<iostream>
#include<Eigen/Dense>
#include<opencv2/opencv.hpp>
#include<opencv2/viz.hpp>
using namespace std;
using namespace Eigen;
using namespace cv;
using namespace viz;
#ifdef _DEBUG                       //opencv库的配置 为了不每次都要调试环境
#pragma comment(lib,"opencv_world480d.lib")
#else
#pragma comment(lib,"opencv_world480d.lib")
#endif
#ifdef _DEBUG                       //opencv库的配置 为了不每次都要调试环境
#pragma comment(lib,"opencv_viz480d.lib")
#else
#pragma comment(lib,"opencv_viz480d.lib")
#endif
int main() {
	Mat src = imread("C:/1_whole.png");
	Mat img = Mat(src.rows, src.cols, CV_8UC1);
	Mat img2 = Mat(src.rows, src.cols, CV_8UC1);
	Mat img3 = Mat(src.rows, src.cols, CV_8UC1);
	cvtColor(src, img, COLOR_BGR2GRAY);
	threshold(img, img2, 150, 255, THRESH_BINARY);
	Mat hust = getStructuringElement(MORPH_RECT, Size(10, 10));
	dilate(img2, img3, hust);
	vector<vector<Point>>contours;
	findContours(img3, contours, RETR_TREE, CHAIN_APPROX_NONE);
	Rect bound;                        
	bound = boundingRect(contours[2]);
	cout << bound.x << endl << bound.y << endl << bound.height << bound.width;
	vector<Point3f> objP;
	objP.push_back(Point3f(0, 0, 0));
	objP.push_back(Point3f(1.25f, 0, 0));
	objP.push_back(Point3f(0, 1.35f, 0));
	objP.push_back(Point3f(1.25f, 1.35f, 0));
	vector<Point2f>camjP;
	camjP.push_back(Point2f((float)bound.x, (float) bound.y));
	camjP.push_back(Point2f((float)(bound.x+bound.height), (float)bound.y));
	camjP.push_back(Point2f((float)bound.x, (float)(bound.y+bound.width)));
	camjP.push_back(Point2f((float)(bound.x+bound.height), (float)(bound.y+bound.width)));
	Mat camera = (Mat_<double>(3, 3) << 1900, 0, 960, 0, 1900, 540, 0, 0, 1);
	Mat distCoeff = (Mat_<double>(1, 5) << 0, 0, 0, 0, 0);
	Mat rvec, tvec, rotm;
	solvePnP(objP, camjP, camera, distCoeff, rvec, tvec);
	Rodrigues(rvec, rotm);
	cout << rotm << endl << tvec;
	cv::Affine3d transformation(rotm, tvec);
	Viz3d mywindows("windows1");                             
	mywindows.showWidget("thing", WCoordinateSystem());
	mywindows.showWidget("camera", WCoordinateSystem(), transformation);
	mywindows.spin();
}