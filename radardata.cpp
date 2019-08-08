#include "radardata.h"
#include "matrix.h"
#include "iostream"
#include <stdio.h>

RadarData::RadarData():x(2,1,0.0,0.0),p(2,2,1.0,0.0,0.0,1.0),y(2,1,0.0,0.0),py(2,2,1.0,0.0,0.0,1.0)
{
}

void RadarData::setMatrixX(Matrix x){
    this->x.set(x);
}
void RadarData::setMatrixP(Matrix p){
    this->p.set(p);
}
void RadarData::setMatrixY(Matrix y){
    this->y.set(y);
}
void RadarData::setMatrixPy(Matrix py){
    this->py.set(py);
}


/**
 * @brief RadarData::reset
 * 重置数据
 */
void RadarData::reset(){
    Matrix a(2,2,1.0,0.0,0.0,1.0);
    Matrix b(2,1,0.0,0.0);
    p.set(a);
    py.set(a);
    x.set(b);
    y.set(b);
}

