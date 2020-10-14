//
// Created by tomer on 6/9/2020.
//
#include "Activation.h"
#include <cmath>

#define ERR "Invalid activation type"

/**
 * Activation constructor
 * @param actType the type of the activation
 */
Activation::Activation(ActivationType actType)
{
	if(actType != Relu && actType != Softmax)
	{
		std::cerr << ERR << std::endl;
		exit(EXIT_FAILURE);
	}
	_type = actType;
}

/**
 * Applies the Relu activation
 * @param input the input matrix
 * @return new matrix after the activation
 */
Matrix relu(const Matrix& input)
{
	Matrix newMat = Matrix(input.getRows(), input.getCols());
	for(int i = 0; i < input.getRows(); i++)
	{
		for(int j = 0; j < input.getCols(); j++)
		{
			if(input(i, j) >= 0)
			{
				newMat(i, j) = input(i, j);
			}
			else
			{
				newMat(i, j) = 0;
			}
		}
	}
	return newMat;
}

/**
 * Applies the Softmax activation
 * @param input the input matrix
 * @return new matrix after the activation
 */
Matrix softmax(const Matrix& input)
{
	Matrix newMat = Matrix(input.getRows(), input.getCols());
	float sum = 0;
	for(int i = 0; i < input.getRows(); i++)
	{
		for(int j = 0; j < input.getCols(); j++)
		{
			sum += std::exp(input(i, j));
		}
	}
	sum = 1 / sum;
	for(int i = 0; i < input.getRows(); i++)
	{
		for(int j = 0; j < input.getCols(); j++)
		{
			newMat(i, j) = std::exp(input(i, j)) * sum;
		}
	}
	return newMat;
}

/**
 * Applies the activation function on the input
 * @param input the input matrix
 * @return new matrix after the activation
 */
Matrix Activation::operator()(const Matrix &input) const
{
	if(_type == Relu)
	{
		return relu(input);
	}
	else
	{
		return softmax(input);
	}
}
