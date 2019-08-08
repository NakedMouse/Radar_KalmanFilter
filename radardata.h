#ifndef RADARDATA_H
#define RADARDATA_H
#include "matrix.h"

class RadarData
{
public:

    Matrix x;
    Matrix p;
    Matrix y;
    Matrix py;
    double lasttime;
    int id;
    int status;
    RadarData();

    void setMatrixX(Matrix x);
    void setMatrixP(Matrix p);
    void setMatrixY(Matrix y);
    void setMatrixPy(Matrix py);
    void reset();
};

#endif // RADARDATA_H
