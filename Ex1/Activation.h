//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * Activation calss
 */
class Activation
{
public:
	/**
	 * Activation constructor
	 * @param actType the type of the activation
	 */
	Activation(ActivationType actType);
	/**
	 * @return the activation type
	 */
	ActivationType getActivationType() const {return _type; };
	/**
	 * Applies the activation function on the input
	 * @param input the input matrix
	 * @return new matrix after the activation
	 */
	Matrix operator()(const Matrix& input) const;
	/**
	 * Applies the Relu activation
	 * @param input the input matrix
	 * @return new matrix after the activation
	 */
	friend Matrix relu(const Matrix& input);
	/**
	 * Applies the Softmax activation
	 * @param input the input matrix
	 * @return new matrix after the activation
	 */
	friend Matrix softmax(const Matrix& input);
private:
	ActivationType _type;
};

/**
 * Applies the Relu activation
 * @param input the input matrix
 * @return new matrix after the activation
 */
Matrix relu(Matrix& input);

/**
 * Applies the Softmax activation
 * @param input the input matrix
 * @return new matrix after the activation
 */
Matrix softmax(Matrix& input);

#endif //ACTIVATION_H
