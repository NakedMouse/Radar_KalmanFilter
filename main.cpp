#include <iostream>
#include "kalmanfilter.h"
#include "matrix.h"
#include "radardata.h"
#include "inputdata.h"
#include "fstream"
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    //本版本仅用于测试预测数据的精确度,基本思路是将所有测量数据（testfile.csv中仅包含少量数据）预先存入数组中
    //以方便对比,由修正数据为基准预测500ms后的位置及速度，再在数组中找到与预测时间相差±50ms的数据一同输出对比
    //并获得偏差率,仅需记录kalman滤波器文件中的数据R\Q
    InputData mesure[6][600];       //存储测量数据
    RadarData data;                 //临时存储修正数据
    RadarData pre_data;             //临时存储预测数据
    int a[6]={0,0,0,0,0,0};

    //文件读操作
    InputData inData;               //临时存储文件读入数据
    ifstream fp("C:\\Users\\zhou\\Desktop\\testfile.csv");
    //ifstream fp("C:\\Users\\zhou\\Desktop\\2019_08_02_16_11_49.csv");
    string str;
    getline(fp,str);                //去掉文件第一行
    InputData::getInuptData(inData,fp);


    //所有运动的测量数据存入数组
    while(inData.status!=-1){
        if(inData.status==2){
            mesure[inData.id%30][a[inData.id%30]] = inData;
            //cout<<mesure[inData.id%30][a[inData.id%30]].x<<endl;
            a[inData.id%30]++;
        }
        InputData::getInuptData(inData,fp);
    }

    int k=0; //改变以下循环的值
    for(int i=0 ; i<a[k] ; i++){

        KalmanFilter::kalmanFilterMain(data,mesure[k][i],pre_data);

        int time = data.lasttime+500;
        int point=-1;
        for(int j=i ; j<a[k] ; j++){
            if(mesure[k][j].doubletime<time-50) continue;
            else if(mesure[k][j].doubletime>time+50 || mesure[k][j].doubletime-mesure[k][j-1].doubletime>350) break;
            else if(mesure[k][j].x>data.x.matrix[0][0]) break;
            else point = j;
        }

        cout<<"ID:"<<mesure[k][i].id<<"  inData.x:"<<mesure[k][i].x;
        cout<<"   inData.v:"<<mesure[k][i].vx<<"    time:"<<mesure[k][i].time<<"=================="<<endl;
        cout<<"              x:"<<data.x.matrix[0][0]<<"  "<<data.x.matrix[1][0];
        cout<<"   y:"<<data.y.matrix[0][0]<<"  "<<data.y.matrix[1][0]<<endl;
        //data.p.printMatrix();
        cout<<"              x:";
        cout<<pre_data.x.matrix[0][0]<<"  "<<pre_data.x.matrix[1][0];
        cout<<"   y:"<<pre_data.y.matrix[0][0]<<"  "<<pre_data.y.matrix[1][0]<<endl;
        if(point!=-1){
            cout<<"       mesure.x:"<<mesure[k][point].x;
            cout<<"        deviation:"<<pre_data.x.matrix[0][0]-mesure[k][point].x<<endl;
        }
        //if(isnan(data.x.matrix[0][0])) break;

    }
    fp.close();

    return 0;
}





