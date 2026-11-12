#include "Matrix.h"
#include "MatrixExceptions.h"

#include <istream>
#include <ostream>

static double** allocateData(int rows, int cols) {
    double** data = new double*[rows];
    int row = 0;

    try {
        for (; row < rows; ++row) {
            data[row] = new double[cols];
        }
    } catch (...) {
        for (int allocated = 0; allocated < row; ++allocated) {
            delete[] data[allocated];
        }
        delete[] data;
        throw;
    }

    return data;
}

static void freeData(double** data, int rows) {
    for (int row = 0; row < rows; ++row) {
        delete[] data[row];
    }

    delete[] data;
}

struct Matrix::MatrixBuffer {
    double** data;
    int rows;
    int cols;
    int refCount;

    MatrixBuffer(int nrows, int ncols)
        : data(nullptr), rows(nrows), cols(ncols), refCount(1)
    {
        if (rows < 0 || cols < 0) {
            throw MatrixInvalidDimensions();
        }

        data = allocateData(rows, cols);

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                data[row][col] = 0.0;
            }
        }
    }

    ~MatrixBuffer() {
        freeData(data, rows);
    }

    MatrixBuffer* detach() {
        if (refCount == 1) {
            return this;
        }

        MatrixBuffer* copy = new MatrixBuffer(rows, cols);

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                copy->data[row][col] = data[row][col];
            }
        }

        --refCount;
        return copy;
    }

    MatrixBuffer(const MatrixBuffer&) = delete;
    MatrixBuffer& operator=(const MatrixBuffer&) = delete;
};

void Matrix::release() {
    if (--buffer_->refCount == 0) {
        delete buffer_;
    }
}

void Matrix::detach() {
    buffer_ = buffer_->detach();
}

void Matrix::checkIndex(int row, int col) const {
    if (row < 1 || row > buffer_->rows || col < 1 || col > buffer_->cols) {
        throw MatrixIndexOutOfRange();
    }
}

Matrix::Matrix(int rows, int cols)
    : buffer_(new MatrixBuffer(rows, cols))
{
}

Matrix::Matrix(const Matrix& other)
    : buffer_(other.buffer_)
{
    ++buffer_->refCount;
}

Matrix& Matrix::operator=(const Matrix& other) {
    ++other.buffer_->refCount;
    release();
    buffer_ = other.buffer_;

    return *this;
}


Matrix::~Matrix() {
    release();
}

int Matrix::rows() const {
    return buffer_->rows;
}

int Matrix::cols() const {
    return buffer_->cols;
}

int Matrix::refCount() const {
    return buffer_->refCount;
}

bool Matrix::sharesDataWith(const Matrix& other) const {
    return buffer_ == other.buffer_;
}

double Matrix::operator()(int row, int col) const {

    checkIndex(row, col);
    return buffer_->data[row - 1][col - 1];
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
    return matrix_.buffer_->data[row_ - 1][col_ - 1];
}

Matrix::ElementProxy& Matrix::ElementProxy::operator=(double value) {
    matrix_.detach();
    matrix_.buffer_->data[row_ - 1][col_ - 1] = value;
    return *this;
}

Matrix::ElementProxy& Matrix::ElementProxy::operator=(const ElementProxy& other) {
    return *this = static_cast<double>(other);
}

Matrix::ElementProxy& Matrix::ElementProxy::operator+=(double value) {
    matrix_.detach();
    matrix_.buffer_->data[row_ - 1][col_ - 1] += value;
    return *this;
}

Matrix::ElementProxy& Matrix::ElementProxy::operator-=(double value) {
    matrix_.detach();
    matrix_.buffer_->data[row_ - 1][col_ - 1] -= value;
    return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const {

    const int rows = buffer_->rows;
    const int cols = buffer_->cols;

    if (rows != rhs.buffer_->rows || cols != rhs.buffer_->cols) {
        throw MatrixDimensionsMismatch();
    }

    Matrix res(rows, cols);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            res.buffer_->data[row][col] =
                buffer_->data[row][col] + rhs.buffer_->data[row][col];
        }
    }

    return res;
}

Matrix Matrix::operator-(const Matrix& rhs) const {

    const int rows = buffer_->rows;
    const int cols = buffer_->cols;

    if (rows != rhs.buffer_->rows || cols != rhs.buffer_->cols) {
        throw MatrixDimensionsMismatch();
    }

    Matrix res(rows, cols);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            res.buffer_->data[row][col] =
                buffer_->data[row][col] - rhs.buffer_->data[row][col];
        }
    }

    return res;
}

Matrix Matrix::operator*(const Matrix& rhs) const {

    if (buffer_->cols != rhs.buffer_->rows) {
        throw MatrixDimensionsMismatch();
    }

    Matrix res(buffer_->rows, rhs.buffer_->cols);

    for (int i = 0; i < buffer_->rows; ++i){
        for (int j = 0; j < rhs.buffer_->cols; ++j){
            for (int k = 0; k < rhs.buffer_->rows; ++k) {
                res.buffer_->data[i][j] += buffer_->data[i][k] * rhs.buffer_->data[k][j];
            }
        }
    }


    return res;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {

    if (buffer_->cols != rhs.buffer_->cols || buffer_->rows != rhs.buffer_->rows) {
        throw MatrixDimensionsMismatch();
    }

    Matrix result = * this + rhs;
    *this = result;

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {

    if (buffer_->cols != rhs.buffer_->cols || buffer_->rows != rhs.buffer_->rows) {
        throw MatrixDimensionsMismatch();
    }

    this->detach();
    for (int row = 0; row < buffer_->rows; ++row) {
        for (int col = 0; col < buffer_->cols; ++col) {
            buffer_->data[row][col] -= rhs.buffer_->data[row][col];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {

    if (buffer_->cols != rhs.buffer_->rows) {
        throw MatrixDimensionsMismatch();
    }

    Matrix result = *this * rhs;
    *this = result;

    return *this;
}

bool Matrix::operator==(const Matrix& rhs) const {
    if (buffer_->cols != rhs.buffer_->cols || buffer_->rows != rhs.buffer_->rows) {
        return false;
    }

    for (int row = 0; row < buffer_->rows; ++row) {
        for (int col = 0; col < buffer_->cols; ++col) {
            if (buffer_->data[row][col] != rhs.buffer_->data[row][col]) {
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
    const Matrix::MatrixBuffer& buffer = *matrix.buffer_;

    for (int row = 0; row < buffer.rows; ++row) {
        out << '[';

        for (int col = 0; col < buffer.cols; ++col) {
            if (col != 0) {
                out << ' ';
            }
            out << buffer.data[row][col];
        }

        out << ']';
        if (row + 1 < buffer.rows) {
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
            if (!(in >> result.buffer_->data[row][col])) {
                throw MatrixReadError();
            }
        }
    }

    matrix = result;
    return in;
}
