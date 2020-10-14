//
// Created by tomer on 6/8/2020.
//

#include <cstring>
#include "Matrix.h"
#define ALLOC_ERR "Error: Memory problem"
#define DIMS_ERR "Error: The dimensions are not valid"
#define FILE_ERR "Error: reading the file"

using std::nothrow;
using std::endl;
using std::cout;
using std::cerr;

/**
 * Constructor that gets the rows and the cols
 * @param rows the number of rows
 * @param cols the number of cols
 */
Matrix::Matrix(int rows, int cols)
{
	if(rows < 0 || cols < 0 || (rows == 0 && cols != 0) || (cols == 0 && rows != 0))
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	_dims.cols = cols;
	_dims.rows = rows;
	matrix = new (nothrow) float*[rows];
	if(matrix == nullptr)
	{
		cerr << ALLOC_ERR << endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < rows; i++)
	{
		matrix[i] = new (nothrow) float[cols];
		if(matrix[i] == nullptr)
		{
			cerr << ALLOC_ERR << endl;
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

/**
 * copy constructor
 * @param rhs the matrix to copy
 */
Matrix::Matrix(const Matrix & rhs)
{
	_dims.rows = rhs.getRows();
	_dims.cols = rhs.getCols();
	matrix = new (nothrow) float*[_dims.rows];
	if(matrix == nullptr)
	{
		cerr << ALLOC_ERR << endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < _dims.rows; i++)
	{
		matrix[i] = new (nothrow) float[_dims.cols];
		if(matrix[i] == nullptr)
		{
			cerr << ALLOC_ERR << endl;
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 0; i < _dims.rows; i++)
	{
		for(int j = 0; j < _dims.cols; j++)
		{
			matrix[i][j] = rhs.matrix[i][j];
		}
	}
}

/**
 * Destructor
 */
Matrix::~Matrix()
{
	for(int i = 0; i < _dims.rows; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}

/**
 * Transforms the matrix into a col vector
 * @return the current matrix as col vector
 */
Matrix& Matrix::vectorize()
{
	int length = _dims.rows * _dims.cols;
	float ** newMatrix = new (nothrow) float*[length];
	if(newMatrix == nullptr)
	{
		cerr << ALLOC_ERR << endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < length; i++)
	{
		newMatrix[i] = new (nothrow) float[1];
		if(newMatrix[i] == nullptr)
		{
			cerr << ALLOC_ERR << endl;
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 0; i < length; i++)
	{
		newMatrix[i][0] = matrix[i / _dims.cols][i % _dims.cols];
	}
	for(int i = 0; i < _dims.rows; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
	matrix = newMatrix;
	_dims.cols = 1;
	_dims.rows = length;
	return *this;
}

/**
 * prints the matrix plain
 */
void Matrix::plainPrint() const
{
	for(int i = 0; i < _dims.rows; i++)
	{
		for(int j = 0; j < _dims.cols; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

/**
 * Assigment
 * @param rhs the matrix to assign
 * @return
 */
Matrix & Matrix::operator=(const Matrix &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}
	for(int i = 0; i < _dims.rows; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
	_dims.rows = rhs.getRows();
	_dims.cols = rhs.getCols();
	matrix = new (nothrow) float*[_dims.rows];
	if(matrix == nullptr)
	{
		cerr << ALLOC_ERR << endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < _dims.rows; i++)
	{
		matrix[i] = new (nothrow) float[_dims.cols];
		if(matrix[i] == nullptr)
		{
			cerr << ALLOC_ERR << endl;
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 0; i < _dims.rows; i++)
	{
		for(int j = 0; j < _dims.cols; j++)
		{
			matrix[i][j] = rhs.matrix[i][j];
		}
	}
	return *this;
}

/**
* Scalar multiplication on the right
* @param c the scalar
* @return new matrix with the multiplication result
*/
Matrix Matrix::operator*(const float c) const
{
	Matrix newMatrix = Matrix(_dims.rows, _dims.cols);
	for(int i = 0; i < _dims.rows; i++)
	{
		for(int j = 0; j < _dims.cols; j++)
		{
			newMatrix.matrix[i][j] = matrix[i][j] * c;
		}
	}
	return newMatrix;
}

/**
 * Matrix addition
 * @param rhs the matrix to accumulate
 * @return new matrix with the result of the accumulation
 */
Matrix Matrix::operator+(const Matrix &rhs) const
{
	if(rhs.getRows() != _dims.rows || rhs.getCols() != _dims.cols)
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	Matrix newMatrix = Matrix(_dims.rows, _dims.cols);
	for(int i = 0; i < _dims.rows; i++)
	{
		for(int j = 0; j < _dims.cols; j++)
		{
			newMatrix.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
		}
	}
	return newMatrix;
}

/**
 * matrix multiplication
 * @param rhs the right matrix
 * @return new matrix with the result of the multiplication
 */
Matrix Matrix::operator*(const Matrix &rhs) const
{
	if(rhs.getRows() != _dims.cols)
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	Matrix newMatrix = Matrix(_dims.rows, rhs.getCols());
	for(int i = 0; i < _dims.rows; i ++)
	{
		for(int j = 0; j < rhs.getCols(); j++)
		{
			float res = 0;
			for(int t = 0; t < _dims.cols; t++)
			{
				res += matrix[i][t] * rhs.matrix[t][j];
			}
			newMatrix.matrix[i][j] = res;
		}
	}
	return newMatrix;
}

/**
 * Matrix addition accumulation
 * @param rhs the matrix to accumulate
 * @return the current matrix after the accumulation
 */
Matrix & Matrix::operator+=(const Matrix &rhs)
{
	if(rhs.getRows() != _dims.rows || rhs.getCols() != _dims.cols)
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < _dims.rows; i++)
	{
		for(int j = 0; j < _dims.cols; j++)
		{
			matrix[i][j] += rhs.matrix[i][j];
		}
	}
	return *this;
}

/**
 * @param c scalar
 * @param rhs matrix
 * @return new matrix with the multiplication of the scalar and the matrix
 */
Matrix operator*(float c, Matrix& rhs)
{
	Matrix newMatrix = Matrix(rhs.getRows(), rhs.getCols());
	for(int i = 0; i < rhs.getRows(); i++)
	{
		for(int j = 0; j < rhs.getCols(); j++)
		{
			newMatrix(i, j) = rhs(i, j) * c;
		}
	}
	return newMatrix;
}

/**
 * returns the i,j element in the matrix
 * @param i the row
 * @param j the col
 * @return the i,j element in the matrix
 */
float Matrix::operator()(int i, int j) const
{
	if(i < 0 || i >= _dims.rows || j < 0 || j >= _dims.cols)
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	return matrix[i][j];
}

/**
 * returns the i,j element in the matrix
 * @param i the row
 * @param j the col
 * @return the i,j element in the matrix
 */
float& Matrix::operator()(int i, int j)
{
	if(i < 0 || i >= _dims.rows || j < 0 || j >= _dims.cols)
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	return matrix[i][j];
}

/**
 * returns the i'th element
 * @param i the index of the element
 * @return the i'th element
 */
float& Matrix::operator[](int i)
{
	if(i < 0 || i >= _dims.rows * _dims.cols)
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	int numCols = i % _dims.cols;
	int numRows = i / _dims.cols;
	return matrix[numRows][numCols];
}

/**
 * returns the i'th element
 * @param i the index of the element
 * @return the i'th element
 */
float Matrix::operator[](int i) const
{
	if(i < 0 || i >= _dims.rows * _dims.cols)
	{
		cerr << DIMS_ERR << endl;
		exit(EXIT_FAILURE);
	}
	int numCols = i % _dims.cols;
	int numRows = i / _dims.cols;
	return matrix[numRows][numCols];
}

/**
 * @param os output stream
 * @param rhs the matrix
 * @return the output stream with the matrix
 */
std::ostream &operator<<(std::ostream &os, const Matrix& rhs)
{
	for(int i = 0; i <rhs.getRows(); i++)
	{
		for(int j = 0; j < rhs.getCols(); j++)
		{
			if(rhs(i, j) <= 0.1f)
			{
				os << "  ";
			}
			else
			{
				os << "**";
			}
		}
		os << endl;
	}
	return os;
}

/**
 * enters the stream to the matrix
 * @param is the input stream
 * @param rhs the matrix
 * @return the current matrix with the data
 */
Matrix& operator>>(std::istream &is, Matrix& rhs)
{
	char chunk[sizeof(float)];
	for(int i = 0; i < rhs.getRows() * rhs.getCols(); i++)
	{
		if(!is.good())
		{
			cerr << FILE_ERR << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			is.read(chunk, sizeof(float));
			if(is.eof())
			{
				cerr << FILE_ERR << endl;
				exit(EXIT_FAILURE);
			}
			std::memcpy(&rhs.matrix[i / rhs.getCols()][i % rhs.getCols()], chunk, sizeof(float));
		}
	}
	is.read(chunk, sizeof(float));
	if(!is.eof())
	{
		cerr << FILE_ERR << endl;
		exit(EXIT_FAILURE);
	}
	return rhs;
}
