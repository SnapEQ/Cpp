#pragma once

#include <iosfwd>
#include "MatrixExceptions.h"

class Matrix {
    private:
        int rows_;
        int cols_;
        double** data_;
        int* refCount_;

        void release();
        void detach();
        void checkIndex(int row, int col) const;

    public:

        class ElementProxy {

            private:
                Matrix& matrix_;
                int row_;
                int col_;

            public:
                ElementProxy(Matrix& matrix, int row, int col);

                operator double() const;
                ElementProxy& operator=(double value);
                ElementProxy& operator=(const ElementProxy& other);
                ElementProxy& operator+=(double value);
                ElementProxy& operator-=(double value);

        };

        Matrix(int rows = 0, int cols = 0);
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        ~Matrix();

        int rows() const;
        int cols() const;
        int refCount() const;
        bool sharesDataWith(const Matrix& other) const;

        double operator()(int row, int col) const;
        ElementProxy operator()(int row, int col);

        Matrix operator+(const Matrix& rhs) const;
        Matrix operator-(const Matrix& rhs) const;
        Matrix operator*(const Matrix& rhs) const;

        Matrix& operator+=(const Matrix& rhs);
        Matrix& operator-=(const Matrix& rhs);
        Matrix& operator*=(const Matrix& rhs);

        bool operator==(const Matrix& rhs) const;
        bool operator!=(const Matrix& rhs) const;

        friend std::ostream& operator<<(std::ostream&, const Matrix&);
        friend std::istream& operator>>(std::istream&, Matrix&);

};
