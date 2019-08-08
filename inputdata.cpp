#include "inputdata.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
#include <string>
using namespace std;

InputData::InputData()
{
    //time=0.0;
    id=-1;
    x=0.0;
    y=0.0;
    vx=0.0;
    vy=0.0;
    status=0;
    rcs=0.0;
    doubletime=0.0;
}

/**
 * @brief InputData::getInuptData
 * @param a
 * @param fp
 * 通过文件获得数据，每次一条
 */
void InputData::getInuptData(InputData &a, ifstream &fp){
    string str;
    if(getline(fp,str)){                                //判断是否获取到数据
        str.erase(0,str.find_first_not_of("\t\r\n"));   //str预处理
        str.erase(str.find_last_not_of("\t\r\n")+1);
        str.erase(str.find_last_not_of(",")+1);
        istringstream sin(str);                         //str赋值为sstringstream
        vector<string> fields;                          //建立一个string向量
        string temp;
        while(getline(sin,temp,',')){                   //建本行数据存入fields
            fields.push_back(temp);
        }
        a.time = fields[0];                             //将分割好的数据存入对象
        InputData::transfer(fields[1],a.id);            //transfer()将string类型转化为iss类型并再次转化为double
        InputData::transfer(fields[2],a.x);
        InputData::transfer(fields[3],a.y);
        InputData::transfer(fields[4],a.vx);
        InputData::transfer(fields[5],a.vy);
        InputData::transfer(fields[6],a.status);
        InputData::transfer(fields[7],a.rcs);

         //将string类型的time转化为double
        a.timeToTime();
    }else{                                              //若读取失败将status置为-1并退出
        a.status=-1;
        exit(0);
    }

}

/**
 * @brief InputData::transfer
 * @param a
 * @param b
 * 将string类型的数据转化为double型
 */
void InputData::transfer(string &a , double &b){
    istringstream sin(a);
    sin>>b;
}

/**
 * @brief InputData::transfer
 * @param a
 * @param b
 * 将string类型的数据转化为int型
 */
void InputData::transfer(string &a , int &b){
    istringstream sin(a);
    sin>>b;
}

void InputData::timeToTime(){
    istringstream sin(this->time);
    string s[4];
    for(int i=0 ; i<4 ; i++){
        getline(sin,s[i],':');
    }
    double a[4];
    for(int i=0 ; i<4 ; i++){
        transfer(s[i],a[i]);
    }
    this->doubletime=a[0];
    this->doubletime = this->doubletime*60+a[1];
    this->doubletime = this->doubletime*60+a[2];
    this->doubletime = this->doubletime*1000+a[3]+0.0;
    //cout<<this->doubletime<<endl;
}

/**
 * @brief InputData::printData
 * 打印数据
 */
void InputData::printData(){
    cout<<this->time<<','<<this->id<<','<<this->x
       <<','<<this->y<<','<<this->vx<<','<<this->vy<<','<<this->status<<','<<this->rcs<<','<<this->doubletime<<endl;
}

