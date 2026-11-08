#pragma once

#include <stdexcept>

class MatrixIndexOutOfRange : public std::out_of_range {
public:
    MatrixIndexOutOfRange()
        : std::out_of_range("Matrix index is out of range") {}
};

class MatrixInvalidDimensions : public std::invalid_argument {
public:
    MatrixInvalidDimensions()
        : std::invalid_argument("Matrix dimensions cannot be negative") {}
};

class MatrixDimensionsMismatch : public std::runtime_error {
public:
    MatrixDimensionsMismatch()
        : std::runtime_error("Matrix dimensions do not match") {}
};

class MatrixReadError : public std::runtime_error {
public:
    MatrixReadError()
        : std::runtime_error("Failed to read matrix from stream") {}
};
