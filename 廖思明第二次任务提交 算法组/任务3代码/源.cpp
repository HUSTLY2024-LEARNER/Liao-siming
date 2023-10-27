#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
#ifdef _DEBUG                       //opencv库的配置 为了不每次都要调试环境
#pragma comment(lib,"opencv_world480d.lib")
#else
#pragma comment(lib,"opencv_world480d.lib")
#endif
int main() {
	Mat image1,image2,dst;      
	image1 = imread("C:\\1.png");
	Mat hust = getStructuringElement(MORPH_RECT, Size(40, 40));    //创建核来进行膨胀处理
	inRange(image1, Scalar{ 235,0,0 }, Scalar{ 255,210,200 }, dst); /*这里本来是想要先进行色彩空间转换到hsv再转换到灰度图与二值图的，但是想起上次阈值分割我调好了一组直接分割出蓝色的数据
	所以就直接用了，发现效果还不错，比我直接转灰度图再转二值图要好很多，并且没有其他轮廓干扰，所以就用了这种办法（doge），虽然说如果先进行色彩空间转换再通过开运算等操作会更加精确。。*/
	dilate(dst, image2,hust);   //膨胀，实际意义是让整个车牌上只有一条轮廓从而让我后面定位车牌四顶点坐标准确
	vector<vector<Point>>contours;  
	findContours(image2, contours, RETR_TREE, CHAIN_APPROX_NONE);  //查找轮廓
	//drawContours(image1, contours, 0, (0, 0, 255), 3, 8);     这里是开始为了测试是不是只有一条轮廓
	Rect bound;   
	bound = boundingRect(contours[0]);    
	Rect bounds(bound.x, bound.y, bound.width, bound.height);//发现只有一条轮廓后，我便可以定位四顶点坐标，从而将车牌区域从整个区域中截取出来
	Mat ROI = image1(bounds);
	namedWindow("window2",WINDOW_NORMAL);
	imshow("window2", ROI);
	waitKey(0);
}