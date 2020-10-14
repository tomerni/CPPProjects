//
// Created by tomer on 6/9/2020.
//

#include "Dense.h"

/**
 * Applies the layer on the input
 * @param input the input matrix
 * @return output matrix after the appliance of the layer
*/
Matrix Dense::operator()(const Matrix& input)
{
	Matrix newMatrix = _w * input + _b;
	return _activation(newMatrix);
}