# MatrixLib

Disclaimer: This is a simple library which I wrote in my spare time to practice setting up a full project on GitHub.

This is a basic header-only matrix library, with basic support for matrix arithmetic operations and compile time support.

## CI
[![Actions Status](https://github.com/timulations/matrixlib/workflows/CMake%20Build,%20Test,%20Codecov%20and%20Doxygen/badge.svg)](https://github.com/timulations/matrixlib/actions/workflows/cmake.yml)

## Quickstart
To get started, copy both `matrixLib.hpp` and `utils.h` into your project and `#include "matrixLib.hpp"` to start using the library.

Example:
```cpp
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
```

## Full Documentation
Please refer to doc/MatrixLib.pdf
