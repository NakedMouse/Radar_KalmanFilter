#ifndef INPUTDATA_H
#define INPUTDATA_H
#include "fstream"
#include <string>

using namespace std;

class InputData
{
public:

    string time;
    double doubletime;
    int id;
    double x;
    double vx;
    double y;
    double vy;
    double status;
    double rcs;

    InputData();
    static void getInuptData(InputData &a, ifstream &fp);
    static void transfer(string &a , double &b);
    static void transfer(string &a , int &b);
    void printData();
    void timeToTime();
};

#endif // INPUTDATA_H
