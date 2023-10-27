#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
#ifdef _DEBUG                       //opencv������� Ϊ�˲�ÿ�ζ�Ҫ���Ի���
#pragma comment(lib,"opencv_world480d.lib")
#else
#pragma comment(lib,"opencv_world480d.lib")
#endif
int main() {
	Mat image1,image2,dst;      
	image1 = imread("C:\\1.png");
	Mat hust = getStructuringElement(MORPH_RECT, Size(40, 40));    //���������������ʹ���
	inRange(image1, Scalar{ 235,0,0 }, Scalar{ 255,210,200 }, dst); /*���ﱾ������Ҫ�Ƚ���ɫ�ʿռ�ת����hsv��ת�����Ҷ�ͼ���ֵͼ�ģ����������ϴ���ֵ�ָ��ҵ�����һ��ֱ�ӷָ����ɫ������
	���Ծ�ֱ�����ˣ�����Ч������������ֱ��ת�Ҷ�ͼ��ת��ֵͼҪ�úܶ࣬����û�������������ţ����Ծ��������ְ취��doge������Ȼ˵����Ƚ���ɫ�ʿռ�ת����ͨ��������Ȳ�������Ӿ�ȷ����*/
	dilate(dst, image2,hust);   //���ͣ�ʵ��������������������ֻ��һ�������Ӷ����Һ��涨λ�����Ķ�������׼ȷ
	vector<vector<Point>>contours;  
	findContours(image2, contours, RETR_TREE, CHAIN_APPROX_NONE);  //��������
	//drawContours(image1, contours, 0, (0, 0, 255), 3, 8);     �����ǿ�ʼΪ�˲����ǲ���ֻ��һ������
	Rect bound;   
	bound = boundingRect(contours[0]);    
	Rect bounds(bound.x, bound.y, bound.width, bound.height);//����ֻ��һ���������ұ���Զ�λ�Ķ������꣬�Ӷ���������������������н�ȡ����
	Mat ROI = image1(bounds);
	namedWindow("window2",WINDOW_NORMAL);
	imshow("window2", ROI);
	waitKey(0);
}