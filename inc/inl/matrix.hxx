#include "matrix.hpp"
#include <cstddef>
#include <algorithm>
#include <exception>
#include <iostream>


namespace advcpp {

static void AtException(size_t a_rowNum, size_t a_totalRows, size_t a_col, size_t a_totalCols);

template<typename T>
static T* PtrCreate(T* const &a_toCopy, size_t a_cols, size_t a_rows) 
{
    T* newPtr = new T[a_rows * a_cols];
    T* first = a_toCopy;
    T* last = a_toCopy + a_rows * a_cols;
    std::copy(first, last, newPtr);
    return newPtr;
}

template<typename T>
Matrix<T>::Matrix(size_t a_cols, size_t a_rows)
: m_cols(a_cols)
, m_rows(a_rows)
, m_ptr(new T[a_rows * a_cols])
{
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &a_other) 
: m_cols(a_other.m_cols)
, m_rows(a_other.m_rows)
, m_ptr(PtrCreate(a_other.m_ptr, m_cols, m_rows))
{
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &a_other) 
{
    if(this != &a_other) {
        m_rows = a_other.m_rows;
        m_cols = a_other.m_cols;
        T* newPtr = PtrCreate(a_other.m_ptr, m_cols, m_rows);
        delete[] m_ptr;
        m_ptr = newPtr;
    }
    return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] m_ptr;
}

template<typename T>
T& Matrix<T>::operator()(size_t a_col, size_t a_row) noexcept {
    return m_ptr[a_row * m_cols + a_col];
}

template<typename T>
const T& Matrix<T>::operator()(size_t a_col, size_t a_row) const noexcept {
    return m_ptr[a_row * m_cols + a_col];
}

template<typename T>
T& Matrix<T>::at(size_t a_col, size_t a_row) {
    AtException(a_row, m_rows, a_col, m_cols);
    return m_ptr[a_row * m_cols + a_col];
}

template<typename T>
T const& Matrix<T>::at(size_t a_col, size_t a_row) const {
    AtException(a_row, m_rows, a_col, m_cols);
    return m_ptr[a_row * m_cols + a_col];
}
template<typename T>
size_t Matrix<T>::Rows() const noexcept {
    return m_rows;
}
 
template<typename T>
size_t Matrix<T>::Columns() const noexcept {
    return m_cols;
}

static void AtException(size_t a_row, size_t a_totalRows, size_t a_col, size_t a_totalCols) {
    if(a_row >= a_totalRows || a_col >= a_totalCols) {
         throw std::invalid_argument("index out of range");
    }
}
} // namespace advcpp

