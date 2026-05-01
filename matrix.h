#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>


template <class T, int row, int col>
class Matrix{
private:
    static constexpr int m_row {row}; 
    static constexpr int m_col {col};
    static constexpr int m_numElem = row * col;
    T m_data[row * col]{};


    void generateIdentity(){
        int linIndex = 0;
        for (int i = 0; i < m_row; i++){
            for (int j = 0; j < m_col; j++){
                linIndex = i * m_col + j;
                if (i == j){
                    m_data[linIndex] = 1;
                } else {
                    m_data[linIndex] = 0;
                }
            }
        }
    }

    bool validateSizesAddition(const Matrix& rMatrix) const {
        if (this->m_row != rMatrix.m_row || this->m_col != rMatrix.m_col){
            return false;
        } else {
            return true;
        }
    }

    bool validateSizesMultiplication(const Matrix& rMatrix) const {
        if (this->m_col != rMatrix.m_row){
            return false;
        } else {
            return true;
        }
    }
    
    //ugly monster I have not yet mastered how to turn into a princess
    template <int n>
    T minorCalculator(const T (&lowerMatrix)[n * n]) const{
        if constexpr (n == 1){
            return lowerMatrix[0];
        } else if constexpr (n == 2){
            return lowerMatrix[0] * lowerMatrix[3] - lowerMatrix[1] * lowerMatrix[2];
        } else {

            T det = 0;
            for (int colMin = 0; colMin < n; colMin++){  //excluded column 
                T sub[(n-1) * (n-1)];
                //row iteration in lower matrix
                for (int i = 1; i < n; i++){
                    //counting the number of columns in the smaller matrix 
                    int subCol = 0; 
                    //column iteration in the whole matrix
                    for (int j = 0; j < n; j++){ 
                        //if not excluded col then we do the magic 
                        if (j != colMin){   
                            sub[(i-1) * (n-1) + subCol] = lowerMatrix[(i * n) + j];
                            subCol++;
                        }
                    }
                }
                T sign = (colMin % 2 == 0) ? 1 : -1;
                det += sign * lowerMatrix[colMin] * minorCalculator<n-1>(sub);
            }
            return det;
        }
    }
    
public:

    Matrix(const std::vector<std::vector<T>>& data)
    {
        int linearIndex = 0;
        for (int i = 0; i < data.size(); i++){
            for (int j = 0; j < data[0].size(); j++){
                linearIndex = i * col + j;
                m_data[linearIndex] = data[i][j];
            }
        }
    }

    Matrix(const T (&data)[row * col])
    {   
        for (int i = 0; i < row * col; i++){
                m_data[i] = data[i];
        }
    }

    Matrix()
    {
        generateIdentity();
    }

    ~Matrix() = default;
    


    friend std::ostream& operator<<(std::ostream& out, const Matrix<T,row,col>& matrix){
        int linIndex = 0;
        for (int i = 0; i < row ; i++){
            for (int j = 0; j < col; j++){
                linIndex = (i * col) + j;
                out << matrix.m_data[linIndex] << " ";
            }
        out << "\n";
        }
        return out;
    }


    friend Matrix operator+(const Matrix<T,row,col>& lMatrix, const Matrix<T,row,col>& rMatrix) {
        int linearIndex = 0; 
        if (lMatrix.validateSizesAddition(rMatrix)){
            T temp[row * col] = {0};
            for (int i = 0; i < lMatrix.m_row; i++){
                for (int j = 0; j < lMatrix.m_col; j++){
                    linearIndex = i * m_col + j;
                    temp[linearIndex] = lMatrix.m_data[linearIndex] + rMatrix.m_data[linearIndex];
                }
            }
            Matrix<T,row,col> sum(temp);
            return sum;
        }
        throw std::invalid_argument("Check matrix dimensions.");
    }




    template<typename U, int rowLeft, int colLeft, int rowRight, int colRight>
    friend Matrix<U, rowLeft, colRight>
    operator*(const Matrix<U, rowLeft, colLeft>&, const Matrix<U, rowRight, colRight>&);
    

    T determinant() const{
        static_assert(row == col, "Matrix must be square!");
        return minorCalculator<row>(m_data);
    }  
};


    //ugly monster I have not yet mastered how to turn into a princess
    template<typename U, int rowLeft, int colLeft, int rowRight, int colRight>
    Matrix<U, rowLeft, colRight> operator*(const Matrix<U, rowLeft, colLeft>& lMatrix,
                                                const Matrix<U, rowRight, colRight>& rMatrix) 
    {
        if (colLeft != rowRight){
            throw std::invalid_argument("Check matrix dimensions.");
        }
        U temp[rowLeft * colRight]{};
        for (int n = 0; n < rowLeft; n++){
            for (int i = 0; i < colRight; i++){
                U result = 0;
                for (int j = 0; j < colLeft; j++){
                    int linearIndexLeft = n * colLeft + j;
                    int linearIndexRight = j * colRight + i;
                    result += lMatrix.m_data[linearIndexLeft] * rMatrix.m_data[linearIndexRight];
                }
                temp[n * colRight + i] = result;
            }
        }
        return Matrix<U, rowLeft, colRight>(temp);
    }



#endif