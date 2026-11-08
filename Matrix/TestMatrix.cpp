#include "Matrix.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

void testBasicOperations() {
    Matrix first(2, 3);
    Matrix second(2, 3);

    for (int row = 1; row <= 2; ++row) {
        for (int col = 1; col <= 3; ++col) {
            first(row, col) = row + col;
            second(row, col) = 1.0;
        }
    }

    Matrix sum = first + second;
    assert(sum(1, 1) == 3.0);
    assert(sum(2, 3) == 6.0);

    Matrix difference = sum - second;
    assert(difference == first);

    first += second;
    assert(first == sum);

    first -= second;
    assert(first == difference);

    Matrix left(2, 2);
    Matrix right(2, 2);
    left(1, 1) = 1; left(1, 2) = 2;
    left(2, 1) = 3; left(2, 2) = 4;
    right(1, 1) = 5; right(1, 2) = 6;
    right(2, 1) = 7; right(2, 2) = 8;

    Matrix product = left * right;
    assert(product(1, 1) == 19.0);
    assert(product(1, 2) == 22.0);
    assert(product(2, 1) == 43.0);
    assert(product(2, 2) == 50.0);

    left *= right;
    assert(left == product);

    Matrix tall(3, 2);
    Matrix wide(2, 4);
    Matrix nonSquare = tall * wide;
    assert(nonSquare.rows() == 3);
    assert(nonSquare.cols() == 4);
}

void testComparison() {
    Matrix first(2, 2);
    Matrix second(2, 2);
    assert(first == second);
    assert(!(first != second));

    second(2, 2) = 1.0;
    assert(first != second);
    assert(!(first == second));

    assert(Matrix(2, 2) != Matrix(3, 3));
    assert(Matrix(2, 3) != Matrix(3, 2));
}

void testElementAccess() {
    Matrix matrix(2, 2);
    matrix(1, 1) = 5.0;
    matrix(1, 1) += 2.0;
    assert(matrix(1, 1) == 7.0);
    matrix(1, 1) -= 3.0;
    assert(matrix(1, 1) == 4.0);

    matrix(2, 2) = matrix(1, 1);
    assert(matrix(2, 2) == 4.0);

    Matrix other(2, 2);
    other(1, 2) = matrix(2, 1) = 9.0;
    assert(other(1, 2) == 9.0);
    assert(matrix(2, 1) == 9.0);

    const Matrix& constRef = matrix;
    assert(constRef(1, 1) == 4.0);
}

void testReferenceCounting() {
    Matrix original(2, 2);
    original(1, 1) = 10.0;
    original(1, 2) = 20.0;
    assert(original.refCount() == 1);

    Matrix copy = original;
    assert(copy.sharesDataWith(original));
    assert(original.refCount() == 2);

    double value = copy(1, 1);
    assert(value == 10.0);
    assert(copy(1, 2) == 20.0);
    assert(copy.sharesDataWith(original));
    assert(original.refCount() == 2);

    copy(1, 1) = 99.0;
    assert(!copy.sharesDataWith(original));
    assert(original.refCount() == 1);
    assert(copy.refCount() == 1);
    assert(original(1, 1) == 10.0);
    assert(copy(1, 1) == 99.0);
    assert(original(1, 2) == copy(1, 2));

    Matrix assigned;
    assigned = original;
    assert(assigned.sharesDataWith(original));
    assert(original.refCount() == 2);

    Matrix& alias = assigned;
    assigned = alias;
    assert(original.refCount() == 2);

    {
        Matrix scoped = original;
        assert(original.refCount() == 3);
    }
    assert(original.refCount() == 2);

    assigned = copy;
    assert(original.refCount() == 1);
    assert(copy.refCount() == 2);

    Matrix shared = original;
    Matrix ones(2, 2);
    ones(1, 1) = 1.0;
    shared += ones;
    assert(!shared.sharesDataWith(original));
    assert(original(1, 1) == 10.0);
    assert(shared(1, 1) == 11.0);

    shared = original;
    shared -= ones;
    assert(!shared.sharesDataWith(original));
    assert(original(1, 1) == 10.0);
    assert(shared(1, 1) == 9.0);

    shared = original;
    shared *= ones;
    assert(!shared.sharesDataWith(original));
    assert(original(1, 1) == 10.0);
}

void testStreams() {
    Matrix matrix;
    std::istringstream input("2 2\n1.5 2.5\n3.5 4.5");
    input >> matrix;

    assert(matrix.rows() == 2);
    assert(matrix.cols() == 2);
    assert(matrix(1, 1) == 1.5);
    assert(matrix(2, 2) == 4.5);

    std::ostringstream output;
    output << matrix;
    assert(output.str() == "[1.5 2.5]\n[3.5 4.5]");

    Matrix shared = matrix;
    std::istringstream another("1 1 7");
    another >> shared;
    assert(!shared.sharesDataWith(matrix));
    assert(matrix(1, 1) == 1.5);
    assert(shared(1, 1) == 7.0);
}

void testFileStream() {
    const char* fileName = "test_matrix_input.txt";
    {
        std::ofstream file(fileName);
        file << "2 3\n"
             << "1 2 3\n"
             << "4 5 6\n";
    }

    Matrix matrix;
    std::ifstream file(fileName);
    file >> matrix;
    file.close();
    std::remove(fileName);

    assert(matrix.rows() == 2);
    assert(matrix.cols() == 3);
    assert(matrix(1, 1) == 1.0);
    assert(matrix(1, 3) == 3.0);
    assert(matrix(2, 1) == 4.0);
    assert(matrix(2, 3) == 6.0);
}

void testExceptions() {
    bool thrown = false;
    try {
        Matrix invalid(-1, 2);
    } catch (const MatrixInvalidDimensions&) {
        thrown = true;
    }
    assert(thrown);

    Matrix matrix(2, 2);
    thrown = false;
    try {
        matrix(3, 1);
    } catch (const MatrixIndexOutOfRange&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        matrix(1, 0) = 1.0;
    } catch (const MatrixIndexOutOfRange&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        const Matrix& constRef = matrix;
        constRef(0, 1);
    } catch (const MatrixIndexOutOfRange&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        Matrix(2, 2) + Matrix(3, 3);
    } catch (const MatrixDimensionsMismatch&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        Matrix(2, 2) - Matrix(2, 3);
    } catch (const MatrixDimensionsMismatch&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        Matrix(2, 3) * Matrix(2, 3);
    } catch (const MatrixDimensionsMismatch&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        Matrix target(2, 2);
        target += Matrix(2, 3);
    } catch (const MatrixDimensionsMismatch&) {
        thrown = true;
    }
    assert(thrown);
}

void testReadExceptions() {
    Matrix matrix(1, 2);
    matrix(1, 1) = 1.0;
    matrix(1, 2) = 2.0;
    Matrix backup = matrix;

    bool thrown = false;
    try {
        std::istringstream input("1 2 3.0 abc");
        input >> matrix;
    } catch (const MatrixReadError&) {
        thrown = true;
    }
    assert(thrown);
    assert(matrix == backup);

    thrown = false;
    try {
        std::istringstream input("2 2 1 2 3");
        input >> matrix;
    } catch (const MatrixReadError&) {
        thrown = true;
    }
    assert(thrown);
    assert(matrix == backup);

    thrown = false;
    try {
        std::istringstream input("");
        input >> matrix;
    } catch (const MatrixReadError&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        std::ifstream missing("this_file_does_not_exist.txt");
        missing >> matrix;
    } catch (const MatrixReadError&) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        std::istringstream input("-1 2");
        input >> matrix;
    } catch (const MatrixInvalidDimensions&) {
        thrown = true;
    }
    assert(thrown);
    assert(matrix == backup);
}

int main() {
    testBasicOperations();
    testComparison();
    testElementAccess();
    testReferenceCounting();
    testStreams();
    testFileStream();
    testExceptions();
    testReadExceptions();

    std::cout << "All tests passed.\n";
}
