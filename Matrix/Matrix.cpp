#include "Matrix.h"
#include "MatrixExceptions.h"

#include <istream>
#include <ostream>

void Matrix::release() {

    if (refCount_ != nullptr) {
        --(*refCount_);

        if (*refCount_ == 0) {
            for (int row = 0; row < rows_; ++row) {
                delete[] data_[row];
            }

            delete[] data_;
            delete refCount_;
        }
    }
}

void Matrix::detach() {

    if (refCount_ == nullptr || *refCount_ == 1) {
        return;
    }

    double** newData = new double*[rows_];

    for (int row = 0; row < rows_; ++row) {
        newData[row] = new double[cols_];

        for (int col = 0; col < cols_; ++col) {
            newData[row][col] = data_[row][col];
        }
    }

    --(*refCount_);

    data_ = newData;
    refCount_ = new int(1);
}

void Matrix::checkIndex(int row, int col) const {
    if (row < 1 || row > rows_ || col < 1 || col > cols_) {
        throw MatrixIndexOutOfRange();
    }
}

Matrix::Matrix(int rows, int cols) 
    : rows_(rows), cols_(cols), data_(nullptr), refCount_(nullptr) 
{
    if (rows < 0 || cols < 0) {
        throw MatrixInvalidDimensions();
    }

    if (rows == 0 || cols == 0) {
        return;
    }

    data_ = new double*[rows_];

    for (int row = 0; row < rows_; ++row) {
        data_[row] = new double[cols_];

        for (int col = 0; col < cols_; ++col) {
            data_[row][col] = 0.0;
        }
    }

    refCount_ = new int(1);

}

Matrix::Matrix(const Matrix& other) 
    : rows_(other.rows_),
    cols_(other.cols_),
    data_(other.data_),
    refCount_(other.refCount_)
{
    if (refCount_ != nullptr) {
        ++(*refCount_);
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    release();

    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = other.data_;
    refCount_ = other.refCount_;

    if (refCount_ != nullptr) {
        ++(*refCount_);
    }

    return *this;
}


Matrix::~Matrix() {
    release();
}

int Matrix::rows() const {
    return rows_;
}

int Matrix::cols() const {
    return cols_;
}

int Matrix::refCount() const {
    return refCount_ != nullptr ? *refCount_ : 0;
}

bool Matrix::sharesDataWith(const Matrix& other) const {
    return data_ != nullptr && data_ == other.data_;
}

double Matrix::operator()(int row, int col) const {

    checkIndex(row, col);
    return data_[row - 1][col - 1];
}

Matrix::ElementProxy Matrix::operator()(int row, int col) {

    checkIndex(row, col);
    return ElementProxy(*this, row, col);
}


Matrix::ElementProxy::ElementProxy(Matrix& matrix, int row, int col)
    : matrix_(matrix), row_(row), col_(col)
{
}

Matrix::ElementProxy::operator double() const {
    return matrix_.data_[row_ - 1][col_ - 1];
}

Matrix::ElementProxy& Matrix::ElementProxy::operator=(double value) {
    matrix_.detach();
    matrix_.data_[row_ - 1][col_ - 1] = value;
    return *this;
}

Matrix::ElementProxy& Matrix::ElementProxy::operator=(const ElementProxy& other) {
    return *this = static_cast<double>(other);
}

Matrix::ElementProxy& Matrix::ElementProxy::operator+=(double value) {
    matrix_.detach();
    matrix_.data_[row_ - 1][col_ - 1] += value;
    return *this;
}

Matrix::ElementProxy& Matrix::ElementProxy::operator-=(double value) {
    matrix_.detach();
    matrix_.data_[row_ - 1][col_ - 1] -= value;
    return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const {

    if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
        throw MatrixDimensionsMismatch();
    }

    Matrix res(rows_, cols_);

    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            res.data_[row][col] = data_[row][col] + rhs.data_[row][col];
        }
    }

    return res;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
        throw MatrixDimensionsMismatch();
    }

    Matrix res(rows_,cols_);
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            res.data_[row][col] = data_[row][col] - rhs.data_[row][col];
        }
    }

    return res;
}

Matrix Matrix::operator*(const Matrix& rhs) const {

    if (cols_ != rhs.rows_) {
        throw MatrixDimensionsMismatch();
    }

    Matrix res(rows_,rhs.cols_);

    for (int i = 0; i < rows_; ++i){
        for (int j = 0; j < rhs.cols_; ++j){
            for (int k = 0; k < rhs.rows_; ++k) {
                res.data_[i][j] += data_[i][k] * rhs.data_[k][j]; 
            }
        }
    }


    return res;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
 
    if (cols_ != rhs.cols_ || rows_ != rhs.rows_ ) {
        throw MatrixDimensionsMismatch();
    }

    Matrix result = * this + rhs;
    *this = result;

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {

    if (cols_ != rhs.cols_ || rows_ != rhs.rows_ ) {
        throw MatrixDimensionsMismatch();
    }

    this->detach();
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            data_[row][col] -= rhs.data_[row][col];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {

    if (cols_ != rhs.rows_) {
        throw MatrixDimensionsMismatch();
    }

    Matrix result = *this * rhs;
    *this = result;

    return *this;
}

bool Matrix::operator==(const Matrix& rhs) const {
    if (cols_ != rhs.cols_ || rows_ != rhs.rows_) {
        return false;
    }

    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            if (data_[row][col] != rhs.data_[row][col]) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& rhs) const {
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    for (int row = 0; row < matrix.rows_; ++row) {
        out << '[';

        for (int col = 0; col < matrix.cols_; ++col) {
            if (col != 0) {
                out << ' ';
            }
            out << matrix.data_[row][col];
        }

        out << ']';
        if (row + 1 < matrix.rows_) {
            out << '\n';
        }
    }

    return out;
}

// Expected format: "rows cols" followed by rows * cols elements.
// Reads into a temporary so that on error the target matrix is left unchanged.
std::istream& operator>>(std::istream& in, Matrix& matrix) {
    int rows = 0;
    int cols = 0;

    if (!(in >> rows >> cols)) {
        throw MatrixReadError();
    }

    Matrix result(rows, cols);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (!(in >> result.data_[row][col])) {
                throw MatrixReadError();
            }
        }
    }

    matrix = result;
    return in;
}

