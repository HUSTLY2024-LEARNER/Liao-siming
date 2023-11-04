#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
#ifdef _DEBUG                       //opencv������� Ϊ�˲�ÿ�ζ�Ҫ���Ի���
#pragma comment(lib,"opencv_world480d.lib")
#else
#pragma comment(lib,"opencv_world480d.lib")
#endif
string image_file = "C:/distorted.png"; // �� ȷ �� · �� �� ȷ

int main(int argc, char **argv){
	// �� �� �� ʵ �� ȥ �� �� �� �� �� �� �롣 �� �� �� �� �� �� �� ��OpenCV�� ȥ �� �䣬 �� �� �� ʵ �� һ �� �� �� �� �� �⡣
   // �� �� �� ��
	double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
	// �� ��
	double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;

	cv::Mat image = cv::imread(image_file,0); // ͼ �� �� �� �� ͼ��CV_8UC1
	int rows = image.rows,cols = image.cols;
	cv::Mat image_undistort = cv::Mat(rows, cols, CV_8UC1); // ȥ �� �� �� �� �� ͼ

	// �� �� ȥ �� �� �� ͼ �� �� �� ��
	for (int v = 0; v < rows; v++){
		for (int u = 0; u < cols; u++){
			// �� �� �� ʽ�� �� �� ��(u,v)�� Ӧ �� �� �� ͼ �� �� �� �� ��(u_distorted, v_distorted)
			double x = (u - cx) / fx, y = (v - cy)/fy; //���ص��Ӧ����ʵͼ���е��Ǹ��������ĵĺ�������
			double r = sqrt(x * x + y * y);  //�õ㵽���ĵľ���
			double x_distorted = x * (1 + k1 * r * r + k2 * r * r * r * r)+2 * p1 * x * y + p2 * (r * r +
				2 * x * x);
				double y_distorted = y * (1 + k1 * r * r + k2 * r * r * r * r)+2*p1 * (r * r + 2 * y * y) + 2 *p2*
				x * y;
			double u_distorted = fx * x_distorted + cx;
			double v_distorted = fy * y_distorted + cy;

			// �� ֵ (�� �� �� �� ֵ)
			if (u_distorted >= 0 && v_distorted >= 0 && u_distorted < cols && v_distorted < rows) {
				image_undistort.at<uchar>(v, u) = image.at<uchar>((int)v_distorted, (int)u_distorted);
			}
			else {
				image_undistort.at<uchar>(v, u) = 0;
			}
		}
	}

	// �� ͼ ȥ �� �� �� ͼ ��
	cv::imshow("distorted", image);
	cv::imshow("undistorted", image_undistort);
	cv::waitKey();
	return 0;

}