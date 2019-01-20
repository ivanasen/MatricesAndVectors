# MatricesAndVectors
C++ header-only library for work with templated matrices and vectors. Made as a homework project for Intro to Programming class at FMI.

## Usage

There are 3 classes which can be used for calculations:

 1.  `Matrix`
 2.  `Vector`
 3.  `Scalar`
 
Here are some code examples:

 ```c++
 linalg::Matrix<double> matrix1 {
	 { 1, 2, 3 },
	 { 1, 2, 3 },
	 { 1, 2, 3 }
 };
 linalg::Matrix<double> matrix2 {
	 { 1, 2, 3 },
	 { 1, 2, 3 },
	 { 1, 2, 3 }
 };

linalg::Matrix<double> result = matrix1 + matrix2;

linalg::Vector<double> vector = { 121, 343, 4 };

linalg::Matrix<double> transormedVector = matrix1 * vector;
 ```
Operators  `+ - * /` are all overloaded in order to support corresponding mathematical operations.

Available methods for Matrices are:
 1. Calculation of matrix determinant
 2. Calculation of inverse of a given Matrix
 3. Calculation of Dot and vector products of vectors
 4. Linear transformations