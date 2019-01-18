#ifndef IMAGINARY_H
#define IMAGINARY_H

/*! @file */

typedef struct {
    double real;
    double im;
} Imaginary;

/*  Add two fractions together*/
Imaginary add ( Imaginary a, Imaginary b );

Imaginary negate ( Imaginary a );

Imaginary conjugate ( Imaginary a );

Imaginary multiply ( Imaginary a, Imaginary b );

double magnitude ( Imaginary a );

#endif