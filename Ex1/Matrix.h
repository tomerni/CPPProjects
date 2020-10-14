// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
	int rows, cols;
} MatrixDims;

/**
 * Matrix class
 */
class Matrix
{
public:
	/**
	 * Constructor that gets the rows and the cols
	 * @param rows the number of rows
	 * @param cols the number of cols
	 */
	Matrix(int rows, int cols);
	/**
	 * default constructor
	 */
	Matrix(): Matrix(1, 1) {};
	/**
	 * copy constructor
	 * @param rhs the matrix to copy
	 */
	Matrix(const Matrix & rhs);
	/**
	 * Destructor
	 */
	~Matrix();
	/**
	 * @return the number of rows
	 */
	int getRows() const { return _dims.rows; };
	/**
	 * @return the number of cols
	 */
	int getCols() const { return _dims.cols; };
	/**
	 * Transforms the matrix into a col vector
	 * @return the current matrix as col vector
	 */
	Matrix& vectorize();
	/**
	 * prints the matrix plain
	 */
	void plainPrint() const;
	/**
	 * Assigment
	 * @param rhs the matrix to assign
	 * @return
	 */
	Matrix& operator=(const Matrix & rhs);
	/**
	 * matrix multiplication
	 * @param rhs the right matrix
	 * @return new matrix with the result of the multiplication
	 */
	Matrix operator*(const Matrix& rhs) const;
	/**
	 * Scalar multiplication on the right
	 * @param c the scalar
	 * @return new matrix with the multiplication result
	 */
	Matrix operator*(float c) const;
	/**
	 * Matrix addition
	 * @param rhs the matrix to accumulate
	 * @return new matrix with the result of the accumulation
	 */
	Matrix operator+(const Matrix& rhs) const;
	/**
	 * Matrix addition accumulation
	 * @param rhs the matrix to accumulate
	 * @return the current matrix after the accumulation
	 */
	Matrix& operator+=(const Matrix& rhs);
	/**
	 * returns the i,j element in the matrix
	 * @param i the row
	 * @param j the col
	 * @return the i,j element in the matrix
	 */
	float operator()(int i, int j) const;
	/**
	 * returns the i,j element in the matrix
	 * @param i the row
	 * @param j the col
	 * @return the i,j element in the matrix
	 */
	float& operator()(int i, int j);
	/**
	 * returns the i'th element
	 * @param i the index of the element
	 * @return the i'th element
	 */
	float& operator[](int i);
	/**
	 * returns the i'th element
	 * @param i the index of the element
	 * @return the i'th element
	 */
	float operator[](int i) const;
	/**
	 * @param c scalar
	 * @param rhs matrix
	 * @return new matrix with the multiplication of the scalar and the matrix
	 */
	friend Matrix operator*(float c, Matrix& rhs);
		/**
	 * @param os output stream
	 * @param rhs the matrix
	 * @return the output stream with the matrix
	 */
	friend std::ostream &operator<<(std::ostream &os, const Matrix& rhs);

	/**
	 * enters the stream to the matrix
	 * @param is the input stream
	 * @param rhs the matrix
	 * @return the current matrix with the data
	 */
	friend Matrix &operator>>(std::istream &is, Matrix& rhs);

private:
	MatrixDims _dims{};
	float** matrix;
};

/**
 * @param c scalar
 * @param rhs matrix
 * @return new matrix with the multiplication of the scalar and the matrix
 */
Matrix operator*(float c, Matrix& rhs);

/**
 * @param os output stream
 * @param rhs the matrix
 * @return the output stream with the matrix
 */
std::ostream &operator<<(std::ostream &os, const Matrix& rhs);

/**
 * enters the stream to the matrix
 * @param is the input stream
 * @param rhs the matrix
 * @return the current matrix with the data
 */
Matrix &operator>>(std::istream &is, Matrix& rhs);

#endif //MATRIX_H
