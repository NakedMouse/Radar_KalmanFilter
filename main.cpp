#include <iostream>
#include "kalmanfilter.h"
#include "matrix.h"
#include "radardata.h"
#include "inputdata.h"
#include "fstream"
#include <sstream>
#include <string>

using namespace std;

int main()
{
    RadarData data[100];
    RadarData pre_data[100];
    void kalmanFilterMain(RadarData &a ,InputData &b, RadarData &c);


    //文件读操作
    InputData inData;
    ifstream fp("C:\\Users\\zhou\\Desktop\\testfile.csv");
    //ifstream fp("C:\\Users\\zhou\\Desktop\\2019_08_02_16_11_49.csv");
    string str;
    getline(fp,str);
    InputData::getInuptData(inData,fp);

    //筛选并运行kalman滤波器
    while(inData.status!=-1){
    //for(int i=0 ; i<1700 ;i++){
        if(inData.status==2){

            kalmanFilterMain(data[inData.id],inData,pre_data[inData.id]);

            if(inData.id==35){          //打印指定ID的数据
                cout<<"ID:"<<inData.id<<"  inData.x:"<<inData.x;
                cout<<"   inData.y:"<<inData.y<<"    time:"<<inData.time<<"=================="<<endl;
                cout<<"              x:"<<data[inData.id].x.matrix[0][0]<<"  "<<data[inData.id].x.matrix[1][0];
                cout<<"   y:"<<data[inData.id].y.matrix[0][0]<<"  "<<data[inData.id].y.matrix[1][0]<<endl;

                cout<<"Forecast 2s:  x:";
                cout<<pre_data[inData.id].x.matrix[0][0]<<"  "<<pre_data[inData.id].x.matrix[1][0];
                cout<<"   y:"<<pre_data[inData.id].y.matrix[0][0]<<"  "<<pre_data[inData.id].y.matrix[1][0]<<endl;

            }

        }
        InputData::getInuptData(inData,fp);
    }
    fp.close();

    return 0;
}


/**
 * @brief kalmanFilterMain
 * @param a
 * kalman滤波器主程序入口
 */
void kalmanFilterMain(RadarData &a , InputData &b , RadarData &c){

    //简单判断时间是否连续
    if(a.lasttime==0||b.doubletime-a.lasttime>300){
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

}


