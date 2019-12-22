#ifndef __MATRIX__
#define __MATRIX__

// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

//----------------------------------------- class Matrix

class Matrix {
public:
    double m[4][4];                                // elements

    // default constructor
    constexpr Matrix() : m{1.0, 0.0, 0.0, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0} {}

    // copy constructor
    constexpr Matrix(const Matrix &mat) : m{
            {mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3]},
            {mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3]},
            {mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3]},
            {mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]}} {};

    Matrix                                        // multiplication of two matrices
    operator*(const Matrix &mat) const;

    Matrix &                                            // divsion by a double
    operator /= (double d);

    void                                            // set to the identity matrix
    set_identity();
};


#endif


