//
// Created by tomer on 6/9/2020.
//

#include "MlpNetwork.h"
#include "Dense.h"

/**
 * MlpNetwork constructor
 * @param weights array of Matrices of the weights
 * @param biases array of Matrices of the biases
*/
MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases)
{
	_w1 = weights[0];
	_w2 = weights[1];
	_w3 = weights[2];
	_w4 = weights[3];
	_b1 = biases[0];
	_b2 = biases[1];
	_b3 = biases[2];
	_b4 = biases[3];
}

/**
 * Applies the network on the input
 * @param input the matrix input
 * @return digit struct with the result
*/
Digit MlpNetwork::operator()(const Matrix &input) const
{
	Digit result;
	Dense denseStage1 = Dense(_w1, _b1, Relu);
	Matrix matStage1 = denseStage1(input);
	Dense denseStage2 = Dense(_w2, _b2, Relu);
	Matrix matStage2 = denseStage2(matStage1);
	Dense denseStage3 = Dense(_w3, _b3, Relu);
	Matrix matStage3 = denseStage3(matStage2);
	Dense denseStage4 = Dense(_w4, _b4, Softmax);
	Matrix matStage4 = denseStage4(matStage3);
	unsigned int val = 0;
	float prob = 0;
	for(int i = 0; i < matStage4.getRows(); i++)
	{
		for(int j = 0; j < matStage4.getCols(); j++)
		{
			if(matStage4(i, j) > prob)
			{
				prob = matStage4(i, j);
				val = i;
			}
		}
	}
	result.value = val;
	result.probability = prob;
	return result;
}