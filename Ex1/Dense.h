//
// Created by tomer on 6/9/2020.
//

#ifndef EX4_DENSE_H
#define EX4_DENSE_H

#include "Matrix.h"
#include "Activation.h"

/**
 * Dense class
 */
class Dense
{
public:
	/**
	 * Dense constructor
	 * @param w the weights matrix
	 * @param b the bias matrix
	 * @param type the activation type
	 */
	Dense(const Matrix& w, const Matrix& b, const ActivationType type): _activation(type)
	{_w = w; _b = b; };
	/**
	 * @return the weights matrix
	 */
	Matrix getWeights() const {return _w; };
	/**
	 * @return the bias matrix
	 */
	Matrix getBias() const {return _b; };
	/**
	 * @return the activation type
	 */
	Activation getActivation() const {return _activation; };
	/**
	 * Applies the layer on the input
	 * @param input the input matrix
	 * @return output matrix after the appliance of the layer
	 */
	Matrix operator()(const Matrix& input);
private:
	Matrix _w;
	Matrix _b;
	Activation _activation;
};


#endif //EX4_DENSE_H
