#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include "matrix.h"
#include "radardata.h"
#include "inputdata.h"

class KalmanFilter
{
public:
    KalmanFilter();
    static void kalmanFilter(Matrix &x , Matrix &p , double z);
    static void kalmanFilter(Matrix &x , Matrix &p , double z , double t);
    static void kalmanWithoutMesureData(Matrix &x , Matrix &p );
    static void kalmanFilterMain(RadarData &a ,InputData b, RadarData &c);
};

#endif // KALMANFILTER_H
