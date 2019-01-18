#include <math.h>
#include "imaginary.h"

Imaginary add ( Imaginary a, Imaginary b ) {
  return (Imaginary) { a.real + b.real , a.im + b.im };
}

Imaginary negate ( Imaginary a) {
  return (Imaginary) { a.real * -1 , a.im * -1 };
}

Imaginary conjugate ( Imaginary a) {
  return (Imaginary) { a.real, a.im * -1 };
}

Imaginary multiply ( Imaginary a, Imaginary b ) {
  double real_new = (a.real * b.real) - (a.im * b.im);
  double im_new = (a.im * b.real) + (a.real * b.im);
  return (Imaginary) { real_new , im_new};
}

double magnitude ( Imaginary a ) {
  double magnit_im = sqrt( pow(a.real,2.0) + pow(a.im,2.0) );
  magnit_im = floor(magnit_im *1000)/1000;
  return magnit_im;
}