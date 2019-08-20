#include "inputdatacorrect.h"
#include "math.h"
#include "stdio.h"

using namespace std;


/**
 * @brief InputDataCorrect::InputDataCorrect
 * 本类进行坐标矫正，以及获取车道边缘到雷达位置用以判断雷达位置
 */
InputDataCorrect::InputDataCorrect()
{
}

/**
 * @brief InputDataCorrect::correct
 * @param a
 * 根据getLine获得的参数K对输入的参数进行修正，转换成标准坐标系（无偏角）上的坐标
 * 同样可用于速度的变换
 */
void InputDataCorrect::correct(InputData &a){

    //进行坐标转换
    double R = sqrt(a.x*a.x+a.y*a.y);
    double vr = sqrt(a.vx*a.vx+a.vy+a.vy);
    double x,y,va,vy;
    x = R*cos(atan2(a.y,a.x)-this->k);
    y = R*sin(atan2(a.y,a.x)-this->k);
    vx = vr*cos(atan2(a.vy,a.vx)-this->k);
    vy = vr*sin(atan2(a.vy,a.vx)-this->k);

    //重新赋值
    a.x = x;
    a.y = y;
    a.vx = vx;
    a.vy = vy;
}

/**
 * @brief InputDataCorrect::getLine
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param x3
 * @param y3
 * @param x4
 * @param y4
 * 从传入的四个点(x1,y1)(x2,y2)等获得参数K以及Y轴上雷达与道路边缘的距离yup和ydown
 */
void InputDataCorrect::getLine(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
{
    this->k=(y2-y1)/(x2-x1);
    this->k=atan(this->k);
    this->ydown=y4-((y3-y4)/(x3-x4))*x4;
    this->yup=y1-((y2-y1)/(x2-x1))*x1;

}
