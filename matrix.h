#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix();
    Matrix(int row , int line ,...);
    int getLine();
    int getRow();
    void printMatrix();
    static Matrix multi(Matrix a , Matrix b);
    static Matrix sum(Matrix a , Matrix b);
    static Matrix trans(Matrix a);
    static Matrix sub(Matrix a , Matrix b);
    static Matrix divisionNum(Matrix a , double b);
    static Matrix multiNum(Matrix a , double b);
    void set(Matrix a);

    double matrix[4][4];
    int row;
    int line;

private:


};

#endif // MATRIX_H
