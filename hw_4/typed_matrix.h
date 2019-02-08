#define TYPED_MATRIX

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include "typed_array.h"
#include "imaginary.h"

template <typename ElementType>

class TypedMatrix {
public:
    TypedMatrix();
    TypedMatrix(int n, int m);

    ElementType& get(int i, int j) const;

    void set(int i, int j, ElementType value);

    TypedMatrix& operator=(const TypedMatrix& other);
    TypedMatrix& operator+=(const TypedMatrix& other);
    TypedMatrix& operator*=(const TypedMatrix& other);
    bool operator==(const TypedMatrix& other)const;
    TypedMatrix operator+(const TypedMatrix& other);
    TypedMatrix operator*(const TypedMatrix& other);

    int size_row()const;
    int size_col()const;


private:
    TypedArray<TypedArray<ElementType>> matrix;
    int size_r;
    int size_c;
};

template <typename ElementType>
int TypedMatrix<ElementType>::size_row()const {
     return size_r;
}

template <typename ElementType>
int TypedMatrix<ElementType>::size_col()const {
     return size_c;
}

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix() {
    size_r = 1;
    size_c = 1;
    (*this).set(0,0,ElementType());
}

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(int n, int m){
    size_r = m;
    size_c = n;
    int i,j;
    for(i = 0; i<m; i++){
        for(j = 0 ; j<n; j++){
            (*this).set(i,j,ElementType());
        }
    }   
}

template <typename ElementType>
ElementType &TypedMatrix<ElementType>::get(int i, int j) const {
    if (i < 0 || j < 0) {
        throw std::range_error("matric mOut of range index in matrix");
    }
    if ( i >= size_r || j >= size_c)  {
        throw std::range_error("matrix Out of range index in matrix");
    }
    
    return matrix.safe_get(i).safe_get(j);
}

template <typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType value) {
    if (i < 0 || j < 0) {
        throw std::range_error("Negative index in matrix");
    }
    matrix.get(i).set(j,value);
    return;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator=(const TypedMatrix<ElementType>& other) {
    (*this).size_r = other.size_r;
    (*this).size_c = other.size_c;
    for(int i = 0; i< (*this).size_row(); i++){
        for(int j = 0 ; j<(*this).size_col(); j++){
            ElementType nm = other.get(i,j);
            (*this).set(i,j,nm);
        }
    }   
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator+=(const TypedMatrix<ElementType>& other) {
    if ((*this).size_row() != other.size_row() || (*this).size_col() != other.size_col()) {
        throw std::range_error("false");
    }
    for(int i = 0; i< (*this).size_row(); i++){
        for(int j = 0 ; j<(*this).size_col(); j++){
            ElementType nm_other = other.get(i,j);
            ElementType nm_this = (*this).get(i,j);
            (*this).set(i,j,nm_other + nm_this);
        }
    }   
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator*=(const TypedMatrix<ElementType>& other) {
    if ((*this).size_row() != other.size_row() || (*this).size_col() != other.size_col()) {
        throw std::range_error("false");
    }
    for(int i = 0; i< (*this).size_row(); i++){
        for(int j = 0 ; j<(*this).size_col(); j++){
            ElementType nm_other = other.get(i,j);
            ElementType nm_this = (*this).get(i,j);
            (*this).set(i,j,nm_other * nm_this);
        }
    }   
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator*(const TypedMatrix<ElementType>& other) {
    if ((*this).size_col() != other.size_row()) {
        throw std::range_error("false");
    }
    int r1,c1,r2,c2;
    r1 = (*this).size_row();
    c1 = (*this).size_col();

    r2 = other.size_row();
    c2 = other.size_col();
    ElementType new_nm;
    ElementType nm_other;
    ElementType nm_this;
    TypedMatrix<ElementType> b(c2,r1);
    for(int i = 0; i< r1; i++){
        for(int j = 0 ; j<c2; j++){
            for(int k = 0 ; k<c1; k++){
                nm_other = other.get(k, i);
                nm_this = (*this).get(i, k);
                //new_nm += nm_other * nm_this;
                b.set(i,j, b.get(i, j)+(nm_other*nm_this));
            }  
        }
    }   
    return b;
}

template <typename ElementType>
bool TypedMatrix<ElementType>::operator==(const TypedMatrix& other)const{
    ElementType a,b;
    for(int i = 0; i< (*this).size_row(); i++){
        for(int j = 0 ; j<(*this).size_col(); j++){
            a = (*this).get(i, j);
            b = other.get(i, j);
           if( a != b ){
               return false;
           }
        }
    }
    return true;
}

template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator+(const TypedMatrix<ElementType>& other) {
    if (size_r != other.size_row() || size_c != other.size_col()) {
        throw std::range_error("false");
    }
    int r1,c1,r2,c2;
    r1 = size_r;
    c1 = size_c;

    r2 = other.size_row();
    c2 = other.size_col();
    ElementType nm_other;
    ElementType nm_this;
    TypedMatrix<ElementType> b(other.size_c, other.size_r);
    //std::cout<<"c = "<< b.size_r<<b.size_c;
    for(int i = 0; i< size_r; i++){
        for(int j = 0 ; j< size_c; j++){
            nm_other = other.get(i, j);
            nm_this = (*this).get(i, j);
            b.set(i, j,nm_other + nm_this);
        }
    }   
    return b;
}