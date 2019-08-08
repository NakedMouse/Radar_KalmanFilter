#include "matrix.h"
#include <iostream>
#include "stdarg.h"

using namespace std;

Matrix::Matrix()
{
}

/**
 * @brief Matrix::Matrix
 * @param row
 * @param line
 * 构造函数，row、line后是矩阵完整数据
 */
Matrix::Matrix(int row , int line ,...){
    va_list ap;
    va_start(ap,line);
    this->row=row;
    this->line=line;
    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<line ; j++){
            this->matrix[i][j] = va_arg(ap,double);
        }
    }
    va_end(ap);
}

int Matrix::getLine(){
    return line;
}

int Matrix::getRow(){
    return row;
}

/**
 * @brief Matrix::printMatrix
 * 打印矩阵信息
 */
void Matrix::printMatrix(){
    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<line ;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

/**
  * @brief Matrix::multi
  * @param a
  * @param b
  * @return
  * 矩阵乘法
  */
 Matrix Matrix:: multi(Matrix a , Matrix b) {
    Matrix result;
    result.row=a.row;
    result.line=b.line;
    for(int i=0,j=0; i<a.getRow() ; i++){
        for(j=0 ; j<b.getLine() ; j++){
            double sum =0.0;
            for(int k =0 ; k <a.getLine() ;k++){
                sum+=a.matrix[i][k]*b.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }
    return result ;
}

 /**
 * @brief Matrix::sum
 * @param a
 * @param b
 * @return
 * 矩阵求和
 */
Matrix  Matrix::sum(Matrix a , Matrix b){
     Matrix result;
     result.row=a.row;
     result.line=a.line;
     for(int i=0,j=0; i<a.getRow() ;i++){
         for(j=0 ; j<a.getLine() ;j++){
             result.matrix[i][j]=a.matrix[i][j]+b.matrix[i][j];
         }
     }
     return result;
 }

/**
 * @brief Matrix::trans
 * @param a
 * @return
 * 矩阵转置
 */
Matrix Matrix::trans(Matrix a){
    Matrix result;
    result.row=a.row;
    result.line=a.line;
    for(int i=0,j=0 ; i<a.getRow() ; i++){
        for(j=0 ; j<a.getLine() ; j++){
            result.matrix[j][i]=a.matrix[i][j];
        }
    }
    return result;
 }

/**
 * @brief Matrix::sub
 * @param a
 * @param b
 * @return
 * 矩阵减法
 */
Matrix Matrix::sub(Matrix a , Matrix b){
    Matrix result;
    result.row=a.row;
    result.line=a.line;
    for(int i=0,j=0; i<a.getRow() ;i++){
        for(j=0 ; j<a.getLine() ;j++){
            result.matrix[i][j]=a.matrix[i][j]-b.matrix[i][j];
        }
    }
    return result;
}

/**
 * @brief Matrix::divisionNum
 * @param a
 * @param b
 * @return
 * 矩阵除以数字
 */
Matrix Matrix::divisionNum(Matrix a , double b){
    Matrix result;
    result.row=a.row;
    result.line=a.line;
    for(int i = 0 ; i<a.getRow() ; i++){
        for(int j = 0 ; j<a.getLine() ; j++){
            result.matrix[i][j]=a.matrix[i][j]/b;
        }
    }
    return result;
}

/**
 * @brief Matrix::multiNum
 * @param a
 *
 * @param b
 * @returns
 * 矩阵乘以数字
 */
Matrix Matrix::multiNum(Matrix a , double b){
    Matrix result;
    result.row=a.row;
    result.line=a.line;
    for(int i = 0 ; i<a.getRow() ; i++){
        for(int j = 0 ; j<a.getLine() ; j++){
            result.matrix[i][j]=a.matrix[i][j]*b;
        }
    }
    return result;
}

/**
 * @brief Matrix::set
 * @param a
 * 矩阵赋值
 */
void Matrix::set(Matrix a){
    this->row = a.row;
    this->line = a.line;
    for(int i=0 ; i<a.row ; i++){
        for(int j=0 ; j<line ;j++){
            this->matrix[i][j] = a.matrix[i][j];
        }
    }
}
