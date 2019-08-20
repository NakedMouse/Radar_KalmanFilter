#ifndef INPUTDATACORRECT_H
#define INPUTDATACORRECT_H
#include "inputdata.h"

class InputDataCorrect
{
public:
    InputDataCorrect();
    double k;
    double yup;
    double ydown;

    void correct(InputData &a);
    void getLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
};

#endif // INPUTDATACORRECT_H
