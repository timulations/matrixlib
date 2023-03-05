#include <cassert>

#include "matrixLib.hpp"

using namespace MatrixLib;

void test_constructors() {
    /* Test default constructor */
    Matrix<int, 3, 4> mat1;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            assert(mat1[i][j] == 0);
        }
    }

    // Test constructor with initializer list
    Matrix<int, 2, 2> mat2{{1, 2}, {3, 4}};
    assert(mat2[0][0] == 1);
    assert(mat2[0][1] == 2);
    assert(mat2[1][0] == 3);
    assert(mat2[1][1] == 4);

    // Test constructor with array
    std::array<std::array<int, 2>, 2> arr{{{1, 2}, {3, 4}}};
    Matrix<int, 2, 2> mat3(arr);
    assert(mat3[0][0] == 1);
    assert(mat3[0][1] == 2);
    assert(mat3[1][0] == 3);
    assert(mat3[1][1] == 4);

    // Test copy constructor
    Matrix<int, 2, 2> mat4(mat3);
    assert(mat4[0][0] == 1);
    assert(mat4[0][1] == 2);
    assert(mat4[1][0] == 3);
    assert(mat4[1][1] == 4);

    // Test move constructor
    Matrix<int, 2, 2> mat5(std::move(mat4));
    assert(mat5[0][0] == 1);
    assert(mat5[0][1] == 2);
    assert(mat5[1][0] == 3);
    assert(mat5[1][1] == 4);
}

void test_assignment() {
    Matrix<int, 2, 2> a = {{1, 2}, {3, 4}};
    Matrix<int, 2, 2> b = {{5, 6}, {7, 8}};

    // Test copy assignment
    b = a;
    assert(a == b);

    // Test self assigment
    b = b;
    assert(a == b);

    // Test chaining
    Matrix<int, 2, 2> c = {{9, 10}, {11, 12}};
    b = c = a;
    assert(a == b);
    assert(a == c);

    a = {{1, 2}, {3, 4}};
    b = {{5, 6}, {7, 8}};

    // Test move assignment 
    b = std::move(a);
    assert(b == (Matrix<int, 2, 2>{{1, 2}, {3, 4}}));

    // Test self-assignment
    b = std::move(b);
    assert(b == (Matrix<int, 2, 2>{{1, 2}, {3, 4}}));

    // Test chaining
    c = {{9, 10}, {11, 12}};
    b = std::move(c) = std::move(a);
    assert(b == (Matrix<int, 2, 2>{{1, 2}, {3, 4}}));
    assert(c == (Matrix<int, 2, 2>{{1, 2}, {3, 4}})); 
}

void test_accessors() {
    Matrix<int, 3, 3> mat{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};

    // Test subscript operator
    assert(mat[0][0] == 1 && mat[1][1] == 5 && mat[2][2] == 9);

    // Test parentheses operator
    assert(mat(0, 0) == 1 && mat(1, 1) == 5 && mat(2, 2) == 9);
}

void test_mutators() {
    Matrix<int, 2, 2> mat{{{1, 2}, {3, 4}}};

    // Test subscript operator
    mat[0][1] = 5;
    assert(mat[0][1] == 5);

    // Test parentheses operator
    mat(1, 0) = 6;
    assert(mat(1, 0) == 6);
}

void test_equality() {
    Matrix<int, 2, 3> a = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int, 2, 3> b = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int, 2, 3> c = {{6, 5, 4}, {3, 2, 1}};

    assert(a == b);
    assert(b == a);
    assert(a != c);
    assert(c != a);
    assert(b != c);
    assert(c != b);
}

void test_arithmetic_operations() {
    Matrix<int, 2, 2> mat1{{{1, 2}, {3, 4}}};
    Matrix<int, 2, 2> mat2{{{5, 6}, {7, 8}}};

    // Test matrix addition
    Matrix<int, 2, 2> mat3 = mat1 + mat2;
    assert(mat3[0][0] == 6 && mat3[1][1] == 12);

    // Test matrix subtraction
    Matrix<int, 2, 2> mat4 = mat1 - mat2;
    assert(mat4[0][0] == -4 && mat4[1][1] == -4);

    // Test matrix scalar multiplication
    mat1 *= 2;
    assert(mat1[0][0] == 2 && mat1[1][1] == 8);

    // Test matrix multiplication
    Matrix<int, 2, 2> mat5_actual = mat1 * mat2;
    Matrix<int, 2, 2> mat5_expected{{38, 44}, {86, 100}};

    assert(mat5_actual == mat5_expected);

    Matrix<int, 2, 3> mat6 = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int, 3, 2> mat7 = {{7, 8}, {9, 10}, {11, 12}};
    Matrix<int, 2, 2> mat8_expected = {{58, 64}, {139, 154}};

    Matrix<int, 2, 2> mat8_actual = mat6 * mat7;
    assert(mat8_expected == mat8_actual);
}


int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    #define DO_TEST(x) x; printf(#x)

    DO_TEST(test_constructors());
    DO_TEST(test_assignment());
    DO_TEST(test_accessors());
    DO_TEST(test_mutators());
    DO_TEST(test_equality());
    DO_TEST(test_arithmetic_operations());

    return EXIT_SUCCESS;
}