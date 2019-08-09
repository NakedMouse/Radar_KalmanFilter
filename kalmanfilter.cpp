#include "kalmanfilter.h"
#include <stdio.h>
#include <iostream>


using namespace std;

KalmanFilter::KalmanFilter()
{

}

/**
 * @brief KalmanFilter::kalmanWithoutMesureData
 * @param x
 * @param p
 * 不含实测Z值的kalman滤波器，用于短期状态预判
 */
void KalmanFilter::kalmanWithoutMesureData(Matrix &x , Matrix &p ){
    Matrix F(2,2,1.0,0.05,0.0,1.0);
    Matrix Q(2,2,0.05,0.0,0.0,0.05);

    //预测
    x.set(Matrix::multi(F, x));                                                    //计算预测x
    p.set(Matrix::sum(Matrix::multi(Matrix::multi(F, p), Matrix::trans(F)), Q));   //计算预测P,FPFt+Q
}

/**
 * @brief KalmanFilter::kalmanFilter
 * @param x  上一时刻的位置状态矩阵，2*1
 * @param p  上一时刻的状态转移矩阵，2*2
 * @param z  这一时刻实测值，double型
 * @param t  与上一时刻的时间差，单位ms
 * 含上一时刻时间差的kalman滤波器
 */
void KalmanFilter::kalmanFilter(Matrix &x , Matrix &p , double z , double t){
    Matrix F(2,2,1.0,t,0.0,1.0);
    Matrix Q(2,2,0.05,0.0,0.0,0.05);
    Matrix H(1,2,1.0,0.0);
    double R = 1.0;

    //预测
    Matrix x_;
    x_.set(Matrix::multi(F, x));                                                    //计算预测x
    Matrix P_;
    P_.set(Matrix::sum(Matrix::multi(Matrix::multi(F, p), Matrix::trans(F)), Q));   //计算预测P,FPFt+Q

    //更新 K值
    double K_;
    K_= Matrix::multi(Matrix::multi(H,P_),Matrix::trans(H)).matrix[0][0]+R;         //计算K_ 中间值
    Matrix K;
    K.set(Matrix::divisionNum(Matrix::multi(P_, Matrix::trans(H)), K_));            //计算K矩阵

    //更新x与p
    x.set(Matrix::sum(x_, Matrix::multiNum(K, z- Matrix::multi(H, x_).matrix[0][0])));
    p.set(Matrix::sub(P_, Matrix::multi(K, Matrix::multi(H, P_))));
}

/**
 * @brief kalmanFilterMain
 * @param a
 * kalman滤波器主程序入口
 */
void KalmanFilter::kalmanFilterMain(RadarData &p , InputData b , RadarData &q){

    RadarData a=p;
    RadarData c;
    //a.id = b.id;
    c.id = b.id;
    //简单判断时间是否连续
    if(a.lasttime==0||b.doubletime-a.lasttime>350){
        if(a.lasttime==0){
            a.lasttime=b.doubletime;
        }else{
            a.lasttime = b.doubletime-178;
        }
        a.lasttime=b.doubletime;
        a.x.matrix[0][0]=b.x;
        a.x.matrix[1][0]=b.vx;
        a.y.matrix[0][0]=b.y;
        a.y.matrix[1][0]=b.vy;
    }
    //调用kalman滤波器对xy轴分别运算
    KalmanFilter::kalmanFilter(a.x,a.p,b.x,(b.doubletime-a.lasttime)/1000.00);    //动态t以及测量数据
    KalmanFilter::kalmanFilter(a.y,a.py,b.y,(b.doubletime-a.lasttime)/1000.00);
    a.lasttime = b.doubletime;

    c = a;

    for(int i=0 ; i<10 ;i++){
        KalmanFilter::kalmanWithoutMesureData(c.x, c.p);
        KalmanFilter::kalmanWithoutMesureData(c.y,c.py);
    }
    p = a;
    q = c;
}
