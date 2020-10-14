//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128}, {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},  {10, 1}};

/**
 * MlpNetwork class
 */
class MlpNetwork
{
public:
	/**
	 * MlpNetwork constructor
	 * @param weights array of Matrices of the weights
	 * @param biases array of Matrices of the biases
	 */
	MlpNetwork(Matrix weights[], Matrix biases[]);
	/**
	 * Applies the network on the input
	 * @param input the matrix input
	 * @return digit struct with the result
	 */
	Digit operator()(const Matrix& input) const;
private:
	Matrix _w1;
	Matrix _w2;
	Matrix _w3;
	Matrix _w4;
	Matrix _b1;
	Matrix _b2;
	Matrix _b3;
	Matrix _b4;
};
#endif // MLPNETWORK_H
