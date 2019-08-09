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
    //本版本仅用于测试预测数据的精确度,基本思路是将所有测量数据（testfile.csv中仅包含少量数据）预先存入数组中
    //以方便对比,由修正数据为基准预测500ms后的位置及速度，再在数组中找到与预测时间相差±50ms的数据一同输出对比
    //并获得偏差率,仅需记录kalman滤波器文件中的数据R\Q
    InputData mesure[6][600];
    RadarData data;
    RadarData pre_data;
    void kalmanFilterMain(RadarData &a ,InputData b, RadarData &c);

    //文件读操作
    InputData inData;
    ifstream fp("C:\\Users\\zhou\\Desktop\\testfile.csv");
    //ifstream fp("C:\\Users\\zhou\\Desktop\\2019_08_02_16_11_49.csv");
    string str;
    getline(fp,str);
    InputData::getInuptData(inData,fp);
    int a[6]={0,0,0,0,0,0};

    //所有运动的测量数据存入数组
    while(inData.status!=-1){
        if(inData.status==2){
            mesure[inData.id%30][a[inData.id%30]] = inData;
            //cout<<mesure[inData.id%30][a[inData.id%30]].x<<endl;
            a[inData.id%30]++;
        }
        InputData::getInuptData(inData,fp);
    }


    int k=4; //改变以下循环的值
    for(int i=0 ; i<a[k] ; i++){

        kalmanFilterMain(data,mesure[k][i],pre_data);


        cout<<"ID:"<<mesure[k][i].id<<"  inData.x:"<<mesure[k][i].x;
        cout<<"   inData.y:"<<mesure[k][i].y<<"    time:"<<mesure[k][i].time<<"=================="<<endl;
        cout<<"              x:"<<data.x.matrix[0][0]<<"  "<<data.x.matrix[1][0];
        cout<<"   y:"<<data.y.matrix[0][0]<<"  "<<data.y.matrix[1][0]<<endl;

        cout<<"              x:";
        cout<<pre_data.x.matrix[0][0]<<"  "<<pre_data.x.matrix[1][0];
        cout<<"   y:"<<pre_data.y.matrix[0][0]<<"  "<<pre_data.y.matrix[1][0]<<endl;

    }
    fp.close();
//    //筛选并运行kalman滤波器
//    while(inData.status!=-1){
//    //for(int i=0 ; i<1700 ;i++){
//        if(inData.status==2){

//            kalmanFilterMain(data[inData.id%30],inData,pre_data[inData.id%30]);

//            if(inData.id==35){          //打印指定ID的数据
//                cout<<"ID:"<<inData.id<<"  inData.x:"<<inData.x;
//                cout<<"   inData.y:"<<inData.y<<"    time:"<<inData.time<<"=================="<<endl;
//                cout<<"              x:"<<data[inData.id%30].x.matrix[0][0]<<"  "<<data[inData.id%30].x.matrix[1][0];
//                cout<<"   y:"<<data[inData.id%30].y.matrix[0][0]<<"  "<<data[inData.id%30].y.matrix[1][0]<<endl;

//                cout<<"              x:";
//                cout<<pre_data[inData.id%30].x.matrix[0][0]<<"  "<<pre_data[inData.id%30].x.matrix[1][0];
//                cout<<"   y:"<<pre_data[inData.id%30].y.matrix[0][0]<<"  "<<pre_data[inData.id%30].y.matrix[1][0]<<endl;

//            }

//        }
//        InputData::getInuptData(inData,fp);
//    }

    fp.close();
    return 0;
}


/**
 * @brief kalmanFilterMain
 * @param a
 * kalman滤波器主程序入口
 */
void kalmanFilterMain(RadarData &p , InputData b , RadarData &q){

    RadarData a;
    RadarData c;
    a.id = b.id;
    c.id = b.id;
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
    p = a;
    q = c;
}


