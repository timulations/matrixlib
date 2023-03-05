#include <iostream>
#include <vector>

#include "matrixLib.hpp"

int main(int argc, char *argv[]) {

    (void)argc; (void)argv;
    
    constexpr MatrixLib::Matrix<int,3,4> matrixA{{1,2,3,4}, {6,5,4,3}, {1,3,2,5}};
    constexpr MatrixLib::Matrix<int,4,2> matrixB{{1,3}, {2,4}, {3, 5}, {6,2}};
    constexpr MatrixLib::Matrix<int,4,2> matrixC{{0,7}, {1,10}, {13, 12}, {5,2}};

    std::cout << "Matrix A is:\n";
    std::cout << matrixA << std::endl;

    std::cout << "Matrix B is:\n";
    std::cout << matrixB << std::endl;

    std::cout << "Matrix C is:\n";
    std::cout << matrixC << std::endl;

    std::cout << "Matrix B + Matrix C is:\n" << matrixB + matrixC << std::endl;
    std::cout << "Matrix B - Matrix C is:\n" << matrixB - matrixC << std::endl;
    std::cout << "Matrix A * Matrix B is:\n" << matrixA * matrixB << std::endl;

    return EXIT_SUCCESS;
}