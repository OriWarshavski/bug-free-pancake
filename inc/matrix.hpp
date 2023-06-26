#ifndef MATRIX_HPP_363d68b9_8a9a_4230_8609_bd4d5f4c165b
#define MATRIX_HPP_363d68b9_8a9a_4230_8609_bd4d5f4c165b

#include <exception>

namespace advcpp {

template<typename T>
class Matrix {
public:
    explicit Matrix(size_t a_cols, size_t a_rows);
    Matrix(const Matrix &a_other);
    Matrix& operator=(const Matrix &a_other);
    ~Matrix();

    T& operator()(size_t a_col, size_t a_row) noexcept;   
    T const& operator()(size_t a_col, size_t a_row) const noexcept; 
        
    T& at(size_t a_col, size_t a_row);   
    T const& at(size_t a_col, size_t a_row) const;
    T const& AtHelper(size_t a_col, size_t a_row) const noexcept;

    size_t Rows() const noexcept;
    size_t Columns() const noexcept;

private:
    size_t m_cols;
    size_t m_rows;
    T* m_ptr;
};

}

#include "inl/matrix.hxx"

#endif // MATRIX_HPP_363d68b9_8a9a_4230_8609_bd4d5f4c165b
