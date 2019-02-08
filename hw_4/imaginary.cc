#include <assert.h>
#include <stdexcept>
#include <math.h>
#include "imaginary.h"

Imaginary::Imaginary(){
    real = 0;
    imag = 0;
}

Imaginary::Imaginary(double a, double b) {
    real = a;
    imag = b;
}

double Imaginary::re(){
    return real;
}

double Imaginary::im(){
    return imag;
}

Imaginary Imaginary::conjugate() {
    Imaginary t = *this;
    t.imag = (*this).imag *-1;
    return t;
}

double Imaginary::magnitude () {
  double magnit_im = sqrt( pow((*this).real,2.0) + pow((*this).imag,2.0) );
  //magnit_im = floor(magnit_im *1000)/1000;
  return magnit_im;
}

Imaginary& Imaginary::operator=(const Imaginary& other) {
    if ( this != &other) {
        (*this).real = other.real;
        (*this).imag = other.imag;
    }
    return *this;
}

Imaginary Imaginary::operator+(const Imaginary& other) {
    Imaginary temp;
    temp.real = other.real + (*this).real;
    temp.imag = other.imag + (*this).imag;
    return temp;
}

Imaginary Imaginary::operator*(const Imaginary& other) {
    Imaginary temp;
    temp.real = ((*this).real * other.real) - ((*this).imag * other.imag);
    temp.imag = ((*this).real * other.imag) + ((*this).imag * other.real);
    return temp;
}

Imaginary& Imaginary::operator+=(const Imaginary& other) {
    (*this).real = other.real + (*this).real;
    (*this).imag = other.imag + (*this).imag;
    return *this;
}

Imaginary& Imaginary::operator*=(const Imaginary& other) {
    Imaginary temp = *this;
    real = (temp.real * other.real) - (temp.imag * other.imag);
    imag = (temp.real * other.imag) + (temp.imag * other.real);
    return *this;
}

bool Imaginary::operator==(const Imaginary& other)const{
   if ((*this).real == other.real && (*this).imag == other.imag ){
       return true;
   }else{
       return false;
   }
}

bool Imaginary::operator!=(const Imaginary& other)const{
   if ((*this).real == other.real && (*this).imag == other.imag ){
       return false;
   }else{
       return true;
   }
}


