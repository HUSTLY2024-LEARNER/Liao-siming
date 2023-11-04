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
    double roll;                    
    double pitch;
    double yaw;
    cin >> roll >> pitch >> yaw;
    double roll_arc = roll * 0.0174533;
    double pitch_arc = pitch * 0.0174533;
    double yaw_arc = yaw * 0.0174533;
    Vector3d euler_angle(roll_arc, pitch_arc, yaw_arc);
    AngleAxisd rotationvector(euler_angle[2], Vector3d::UnitZ());
    Matrix3d rotationMatrix1= rotationvector.toRotationMatrix();
    AngleAxisd rotationvector1(euler_angle[1], Vector3d::UnitY());
    Matrix3d rotationMatrix2 = rotationvector1.toRotationMatrix();
    AngleAxisd rotationvector2(euler_angle[0], Vector3d::UnitX());
    Matrix3d rotationMatrix3 = rotationvector2.toRotationMatrix();
    Matrix3d rotationMatrix = rotationMatrix1 * rotationMatrix2 * rotationMatrix3;
    Eigen::Affine3d veh_to_left = Eigen::Affine3d::Identity();
    veh_to_left.translation() << 2.5,0,0;
    veh_to_left.rotate(rotationMatrix);
    cout << veh_to_left.matrix();
    Viz3d window1("window1");
    window1.showWidget("Coordinate1", WCoordinateSystem());
    window1.showWidget("Coordinate", WCoordinateSystem(),veh_to_left);
    window1.spin();
}