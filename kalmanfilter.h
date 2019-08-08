#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include "matrix.h"

class KalmanFilter
{
public:
    KalmanFilter();
    static void kalmanFilter(Matrix &x , Matrix &p , double z);
    static void kalmanFilter(Matrix &x , Matrix &p , double z , double t);
    static void kalmanWithoutMesureData(Matrix &x , Matrix &p );
};

#endif // KALMANFILTER_H
