#include "matrix.h"


int main(){
    

    int A[16] = {
        5, 2, 0, 0,
        2, 5, 2, 0,
        0, 2, 5, 2,
        0, 0, 2, 5
    };

    long long B[25] = {
    4, 1, 0, 0, 0,
    1, 4, 1, 0, 0,
    0, 1, 4, 1, 0,
    0, 0, 1, 4, 1,
    0, 0, 0, 1, 4
    };


    //need to optimize the matrix for dynamic type of the information
    Matrix<long long,5,5> tete(B);
    // Matrix<int,5,2> tata(B);
    std::cout << tete.determinant();

    
    return 0;
}