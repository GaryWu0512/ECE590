#ifndef IMAGINARY
#define IMAGINARY

#include <assert.h>
#include <iostream>
#include <stdexcept>

class Imaginary {

public:
    public:
      Imaginary();
      Imaginary(double a, double b);
      double re();
      double im();
      Imaginary conjugate();
      double magnitude();

      Imaginary& operator=(const Imaginary& other);
      Imaginary operator+(const Imaginary& other);
      Imaginary operator*(const Imaginary& other);
      Imaginary& operator+=(const Imaginary& other);
      Imaginary& operator*=(const Imaginary& other);
      bool  operator==(const Imaginary& other) const;
      bool  operator!=(const Imaginary& other) const;

private:

    double real, imag;
};

#endif
