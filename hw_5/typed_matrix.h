#ifndef TYPED_MATRIX
#define TYPED_MATRIX

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <math.h>

using namespace std;
template <typename ElementType>

class TypedMatrix {
public:
    TypedMatrix();
    TypedMatrix(int n, int m);

    const ElementType& get(int i, int j)const;

    void set(int i, int j, ElementType value);

    TypedMatrix& operator=(const TypedMatrix& other);
    TypedMatrix& operator+=(const TypedMatrix& other);
    TypedMatrix& operator*=(const TypedMatrix& other);
    bool operator==(const TypedMatrix& other)const;
    TypedMatrix operator+(const TypedMatrix& other);
    TypedMatrix operator*(const TypedMatrix& other);

    TypedMatrix<double> read_matrix_csv(const string path);
    void write_matrix_csv(const TypedMatrix<double> &matrix);

    int rows()const;
    int cols()const;


private:
    vector<vector<ElementType>> matrix;
    int size_r;
    int size_c;
};

template <typename ElementType>
int TypedMatrix<ElementType>::rows()const {
     return size_r;
}

template <typename ElementType>
int TypedMatrix<ElementType>::cols()const {
     return size_c;
}

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix() {
    size_r = 1;
    size_c = 1;
    vector<ElementType> v;
    v.push_back(ElementType());
    matrix.push_back(v);
}

template <typename ElementType>
TypedMatrix<ElementType>::TypedMatrix(int n, int m){
    size_r = m;
    size_c = n;
    int i,j;
    vector<ElementType> v;
    for(i = 0; i<m; i++){
        for(j = 0 ; j<n; j++){
            v.push_back(ElementType());
        }
        matrix.push_back(v);
    }   
}

template <typename ElementType>
const ElementType &TypedMatrix<ElementType>::get(int i, int j)const{
    if (i < 0 || j < 0) {
        throw std::range_error("matric mOut of range index in matrix");
    }
    if ( i >= size_r || j >= size_c)  {
        throw std::range_error("matrix Out of range index in matrix");
    }
    
    return matrix[i][j];
}

template <typename ElementType>
void TypedMatrix<ElementType>::set(int i, int j, ElementType value) {
    if (i < 0 || j < 0) {
        throw std::range_error("Negative index in matrix");
    }
    matrix[i][j] = value;

    return;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator=(const TypedMatrix<ElementType>& other) {
    (*this).matrix = vector<vector<ElementType>>();
    //std::cout << other.matrix[0][0] << "  " << other.matrix[0][1] << "\n";
    //std::cout << (*this).matrix[0][0] << "  " << (*this).matrix[0][0]<< "\n";
    vector<ElementType> v;
    ElementType nm;
    for(int i = 0; i< other.rows(); i++){
        v.clear();
        for(int j = 0 ; j<other.cols(); j++){
            nm = other.matrix[i][j];
            //std::cout<<"nm = "<<nm<<"\n";
            v.push_back(nm);
            //std::cout<<v[j]<<"\n";
        }
        (*this).matrix.push_back(v);
    }
    (*this).size_r = other.size_r;
    (*this).size_c = other.size_c;  
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator+=(const TypedMatrix<ElementType>& other) {
    if ((*this).rows() != other.rows() || (*this).cols() != other.cols()) {
        throw std::range_error("false");
    }
    for(int i = 0; i< (*this).rows(); i++){
        for(int j = 0 ; j<(*this).cols(); j++){
            ElementType nm_other = other.get(i,j);
            ElementType nm_this = (*this).get(i,j);
            (*this).set(i,j,nm_other + nm_this);
        }
    }   
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType>& TypedMatrix<ElementType>::operator*=(const TypedMatrix<ElementType>& other) {
    if ((*this).rows() != other.rows() || (*this).cols() != other.cols()) {
        throw std::range_error("false");
    }
    for(int i = 0; i< (*this).rows(); i++){
        for(int j = 0 ; j<(*this).cols(); j++){
            ElementType nm_other = other.matrix[i][j];
            ElementType nm_this = (*this).get(i,j);
            (*this).set(i,j,nm_other * nm_this);
        }
    }   
    return *this;
}

template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator*(const TypedMatrix<ElementType>& other) {
    if ((*this).cols() != other.rows()) {
        throw std::range_error("false");
    }
    int r1,c1,r2,c2;
    r1 = (*this).rows();
    c1 = (*this).cols();
    std::cout<<r1<<c1<<"\n";
    r2 = other.rows();
    c2 = other.cols();
    std::cout<<r2<<c2<<"\n";
    ElementType new_nm;
    ElementType nm_other;
    ElementType nm_this;
    TypedMatrix<ElementType> b(c2,r1);
    for(int i = 0; i< r1; i++){
        for(int j = 0 ; j<c2; j++){
            ElementType temp = ElementType();
            for(int k = 0 ; k<c1; k++){
                //nm_other = other.matrix[k][i];
                //nm_this = (*this).get(i, k);
                //new_nm += nm_other * nm_this;
                //std::cout << nm_other << " * "<<nm_this<<"\n";
                //b.set(i,j, b.get(i, j)+(nm_other*nm_this));
                //std::cout<<b.get(i,j);
                temp +=  (*this).get(i, k) * other.matrix[k][j];
            } 
            b.set(i,j,temp);
             //std::cout << b.get(i,j) << "  ";
        }
    }   
    //std::cout << b.get() << "  " << other.matrix[0].size() << "\n";
    //std::cout << (*this).matrix.size() << "  " << (*this).matrix[0].size()<< "\n";
    return b;
}

template <typename ElementType>
bool TypedMatrix<ElementType>::operator==(const TypedMatrix& other)const{
    ElementType a,b;
    for(int i = 0; i< (*this).rows(); i++){
        for(int j = 0 ; j<(*this).cols(); j++){
            a = (*this).get(i, j);
            b = other.matrix[i][j];
           if( a != b ){
               return false;
           }
        }
    }
    return true;
}

template <typename ElementType>
TypedMatrix<ElementType> TypedMatrix<ElementType>::operator+(const TypedMatrix<ElementType>& other) {
    if (size_r != other.rows() || size_c != other.cols()) {
        throw std::range_error("false");
    }
    int r1,c1,r2,c2;
    r1 = size_r;
    c1 = size_c;

    r2 = other.rows();
    c2 = other.cols();
    ElementType nm_other;
    ElementType nm_this;
    TypedMatrix<ElementType> b(other.size_c, other.size_r);
    //std::cout<<"c = "<< b.size_r<<b.size_c;
    for(int i = 0; i< size_r; i++){
        for(int j = 0 ; j< size_c; j++){
            nm_other = other.matrix[i][j];
            nm_this = (*this).get(i, j);
            b.set(i, j,nm_other + nm_this);
        }
    }   
    return b;
}
/*
template <typename ElementType>
TypedMatrix<double> TypedMatrix<ElementType>::read_matrix_csv(const string path){
    TypedMatrix<ElementType> m;
    vector<vector<double>> k;
    vector<double> v;
    std::ifstream file;
    file.open(path);
    std::string line,val;
    int i,j =0;

    while(std::getline(file,line)){
        std::istringstream ss(line);
        v.clear();
        while (getline(ss,val,',')){
            double nm = 0;
            nm = std::stod(val);
            //m.set(i,j,nm);
            v.push_back(nm);
            //j++;
            //std::cout<<"v size ="<<v.size()<<"\n";
        }
        k.push_back(v);
        //i++;
        std::cout<<"k size ="<<k.size()<<"\n";
    }
    m.matrix = k;
    m.size_r = k.size();
    m.size_c = v.size();
    //std::cout<<"m size ="<<m.matrix.size()<<"\n";
    return m;
}

template <typename ElementType>
void TypedMatrix<ElementType>::write_matrix_csv(const TypedMatrix<double> &matrix){
    std::ofstream outfile;
    outfile.open("matrix.csv");
    int i,j;
    std::string s;
    for(i=0;i< size_r;i++)
	{
        s = std::to_string(matrix.get(i,0));
        outfile << matrix.get(i,0);
		for(j=1;j<size_c;j++)
		{
            s = std::to_string(matrix.get(i,j));
			outfile<<","<<s;
		}
        outfile << endl;
	}
	outfile.close();
}*/
#endif