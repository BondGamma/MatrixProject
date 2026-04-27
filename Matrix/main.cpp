#include "matrix.h"


int main(){
    

    int A[10] = {
        1, 2, 3, 4, 5,     
        6, 7, 8, 9, 10   
    };

    int B[10] = {
        1, 6,      
        2, 7,
        3, 8,
        4, 9,
        5, 10
    };


    Matrix<int,2,5> tete(A);
    Matrix<int,5,2> tata(B);


    // Matrix<int,5,5> result = testA * testB;
    // std::cout << result;

    std::cout << tete * tata;

    return 0;
}