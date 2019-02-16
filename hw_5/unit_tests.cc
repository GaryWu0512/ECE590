#include "gtest/gtest.h"
#include "utilities.h"
#include "typed_matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>


namespace {

  using namespace std;

  TEST(TEACHER,TEST){
    vector<string> v = { "i", "am", "on", "a", "very", "bumpy", "flight" };
    for (string &s : v ) {
      //s.push_back('a');
      cout << s << "\n";
    }
    cout << v.size();

    for (string &s:v){
      s.push_back('a');
    }
    cout << v.size();


  }
  TEST(Vector,Vector) {
      vector<double> v;
      for (int i=0; i< 50; i++) {
        v.push_back(i);
      }

      for (double &i : v)
        i *= i;
      for (double &i : v)        
        std::cout << i << " "; 
    
      std::cout << "\n";

      std::cout << v.capacity() << "\n";

      v.shrink_to_fit();

      std::cout << v.capacity() << "\n";
      v.push_back(1);
      std::cout << v.capacity() << "\n";      

  }

  TEST(Vector,SimpleSortVector) {
      vector<double> v;
      for (int i=0; i< 50; i++) {
        v.push_back(i-50.5);
      }
      std::cout << "original: ";
      for (double &i : v)        
        std::cout << i << " "; 
      std::cout << "\n";
      vector<double> c;
      c = sort_by_magnitude(v);

      std::cout << "sorted: ";
      for (double &i : c)        
        std::cout << i << " "; 
      std::cout << "\n";

      for(int i=0; i< 50; i++){
        double value = -1.5-i;
        double result = c[i];
        EXPECT_EQ(result, value);
      }
  }

  TEST(File,ReadSimpleFile) {
      TypedMatrix<double> v;
      string path = "test.csv";
      v = read_matrix_csv(path);
      //std::cout << v << "\n";
      //std::cout<< v.get(0,0)<<v.get(0,1)<<v.get(0,2)<<v.get(0,3)<<"\n";
      //std::cout<< v.get(1,0)<<v.get(1,1)<<v.get(1,2)<<v.get(1,3)<<"\n";
      //std::cout<< v.get(2,0)<<v.get(2,1)<<v.get(2,2)<<v.get(2,3)<<"\n";
      for(int i=0; i< 3; i++){
        for(int j=0; j< 4; j++){
          double value = j+1;
          EXPECT_EQ(v.get(i,j), value);
          std::cout<<i<<j<<"\n";
        }
      }
  }

  TEST(File,WriteSimpleFile) {
      TypedMatrix<double> v(3,3);
      for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            v.set(i,j,i*j);
        }
      }
      string path = "matrix.csv";
      write_matrix_csv(v,path);

      TypedMatrix<double> v2;
      v2 = read_matrix_csv(path);
      std::cout<<"v size = "<<v2.size_row()<<v.size_col()<<"\n";
      //std::cout << v << "\n";

      for(int i=0; i< 3; i++){
        for(int j=0; j< 3; j++){
          double value = i*j;
          EXPECT_EQ(v2.get(i,j), value);
        }
      }
      
  }

  TEST(File,ReadToMap) {
      map<string, int> mp;
      mp = occurence_map("sentence.txt");
      
      for(auto const& pair: mp){
          std::cout << "{ " << pair.first << " , " << pair.second << "\n";
      }
  }
/*
  TEST(File,NotMatrixFormat) {
      vector<double> v;
      for (int i=0; i< 50; i++) {
        v.push_back(-i);
      }
      std::cout << "original: ";
      for (double &i : v)        
        std::cout << i << " "; 
      std::cout << "\n";
      functions f;
      f.sort_by_magnitude(v);
      
  }
*/


  TEST(TypedMatrix, Constuctor1){
      TypedMatrix<int> a;
      EXPECT_EQ(a.get(0,0), int());
  }

  TEST(TypedMatrix, Constuctor2){
      TypedMatrix<int> a(2,2);
      EXPECT_EQ(a.get(1,1), int());
  }

  TEST(TypedMatrix, Set_Get1){
      TypedMatrix<int> a(3,3);
      a.set(1, 1, 6);
      EXPECT_EQ(a.get(1,1), 6);
  }

  TEST(TypedMatrix, Set_Get2){
      TypedMatrix<int> a(3,5);
      EXPECT_EQ(a.get(4,2), int());
      //EXPECT_ANY_THROW(a.get(5,3));
      a.set(4, 2, 110 );
      EXPECT_EQ(a.get(4,2), 110);
  }

  TEST(TypedMatrix, Copy1){
      TypedMatrix<int> a(2,3);
      TypedMatrix<int> b;
      b = a;
      b.set(1,1,555);
      EXPECT_EQ(b.get(1,1), 555);
      EXPECT_EQ(a.get(1,1), int());
  }

  TEST(TypedMatrix, Copy2){
      TypedMatrix<int> a(5,6);
      TypedMatrix<int> b,c;
      b = a;
      b.set(3,2,11);
      c = b;
      c.set(3,2, 23);
      EXPECT_EQ(a.get(3,2), int());
      EXPECT_EQ(b.get(3,2), 11);
      EXPECT_EQ(c.get(3,2), 23);
  }

  TEST(TypedMatrix, Add_assign1){
      TypedMatrix<int> a(2, 1);
      TypedMatrix<int> b(2, 1);
      a.set(0, 0, 2);
      a.set(0, 1, 3);
      b.set(0, 0, -2);
      b.set(0, 1, -3);
      a+=b;
      EXPECT_EQ(a.get(0,0), 0);
      EXPECT_EQ(a.get(0,1), 0);
      EXPECT_EQ(b.get(0,0), -2);
      EXPECT_EQ(b.get(0,1), -3);
  }

  TEST(TypedMatrix, Add_assign2){
      TypedMatrix<int> a(1, 3);
      TypedMatrix<int> b(1, 3);
      a.set(0, 0, 1);
      a.set(1, 0, 2);
      a.set(2, 0, 3);
      b.set(0, 0, 5);
      b.set(1, 0, 5);
      b.set(2, 0, 5);
      a+=b;
      EXPECT_EQ(a.get(0,0), 6);
      EXPECT_EQ(a.get(1,0), 7);
      EXPECT_EQ(a.get(2,0), 8);
  }

  TEST(TypedMatrix, Mult_assign1){
      TypedMatrix<int> a(2,3);
      TypedMatrix<int> b(2,3);
      for(int i=0; i<3; i++){
          for(int j=0; j<2; j++){
              a.set(i,j,i*2+j);
              b.set(i,j,2);
          }
      }
      a*=b;
      for(int i=0; i<3; i++){
          for(int j=0; j<2; j++){
              EXPECT_EQ(a.get(i,j),2*(i*2+j));
          }
      }
      //TypedMatrix<int> c(2,4);
      //EXPECT_ANY_THROW(a*=c);
  }

  TEST(TypedMatrix, Mult_assign2){
      TypedMatrix<int> a(2,2);
      TypedMatrix<int> b(2,2);
      a.set(0, 0, 4);
      a.set(0, 1, 3);
      a.set(1, 0, 2);
      a.set(1, 1, 1);
      b.set(0, 0, 6);
      b.set(0, 1, 7);
      b.set(1, 0, 8);
      b.set(1, 1, 9);
      a*=b;
      EXPECT_EQ(a.get(0,0), 24);
      EXPECT_EQ(a.get(0,1), 21);
      EXPECT_EQ(a.get(1,0), 16);
      EXPECT_EQ(a.get(1,1), 9);
  }

  TEST(TypedMatrix, Equality1){
      TypedMatrix<int> a(2, 1);
      TypedMatrix<int> b(2, 1);
      TypedMatrix<int> c(2, 2);
      a.set(0, 0, 33);
      a.set(0, 1, 22);
      b.set(0, 0, 33);
      b.set(0, 1, 22);    
      EXPECT_TRUE(a==b);
      EXPECT_FALSE(a==c);
  }

  TEST(TypedMatrix, Equality2){
      TypedMatrix<int> a(1, 3);
      TypedMatrix<int> b(1, 3);
      TypedMatrix<int> c(1, 3);
      a.set(0, 0, 121);
      a.set(1, 0, 65);
      a.set(2, 0, 78);
      b.set(0, 0, 121);
      b.set(1, 0, 65);
      b.set(2, 0, 78);    
      c.set(0, 0, 121);
      c.set(1, 0, 65);
      c.set(2, 0, -78); 
      EXPECT_TRUE(a==b);
      EXPECT_FALSE(a==c);
  }

  TEST(TypedMatrix, Add1){
      TypedMatrix<int> a(2, 2);
      TypedMatrix<int> b(2, 2); 
      for(int i=0; i<2; i++){
          for(int j=0; j<2; j++){
              a.set(i,j,i*2+j+1);
              b.set(i,j,4-(i*2+j+1));
          }
      }     
      TypedMatrix<int> c;
      c = a+b; 
      EXPECT_EQ(c.get(0,0), 4);
      EXPECT_EQ(c.get(0,1), 4);
      EXPECT_EQ(c.get(1,0), 4);
      EXPECT_EQ(c.get(1,1), 4);
      //TypedMatrix<int> d(3,2);
      //EXPECT_ANY_THROW(c=a+d);
  }

  TEST(TypedMatrix, Add2){
      TypedMatrix<int> a(1, 3);
      TypedMatrix<int> b(1, 3);
      a.set(0, 0, 1);
      a.set(1, 0, 2);
      a.set(2, 0, 3);
      b.set(0, 0, 5);
      b.set(1, 0, 5);
      b.set(2, 0, 5);
      TypedMatrix<int> c;

      c = a+b;
      //std::cout<< a.get(1,0)<<"\n";
      //std::cout<< b.get(1,0)<<"\n";
      
      EXPECT_EQ(c.get(0,0), 6);
      EXPECT_EQ(c.get(1,0), 7);
      EXPECT_EQ(c.get(2,0), 8);
      EXPECT_EQ(a.get(0,0), 1);
      EXPECT_EQ(a.get(1,0), 2);
      EXPECT_EQ(a.get(2,0), 3);
  }

  TEST(TypedMatrix, Add3){
      TypedMatrix<int> a(3, 4);
      TypedMatrix<int> b(3, 4);
      for(int i=0; i<4; i++){
          for(int j=0; j<3; j++){
              a.set(i, j, i*5+j+2);
          }
      }

      for(int i=0; i<4; i++){
          for(int j=0; j<3; j++){
              b.set(i, j, i*3+j-8);
          }
      }
      TypedMatrix<int> c;
      c = a+b; 
      int ans[4][3];
      for(int i=0; i<4; i++){
          for(int j=0; j<3; j++){
              ans[i][j] = (i*5+j+2)+(i*3+j-8);
          }
      }
      for(int i=0; i<4; i++){
          for(int j=0; j<3; j++){
              EXPECT_EQ(c.get(i,j), ans[i][j]);
          }
      }
  }

  TEST(TypedMatrix, Mult1){
      TypedMatrix<int> a(2, 1);
      TypedMatrix<int> b(1, 2);
      a.set(0, 0, 3.0);
      a.set(0, 1, 4.0);
      b.set(0, 0, 3.0);
      b.set(1, 0, 4.0); 
      TypedMatrix<int> c;
      c = a*b; 
      //std::cout<<c<<std::endl;
      EXPECT_DOUBLE_EQ(c.get(0,0), 25.0);
      //EXPECT_ANY_THROW(c.get(0,1));
      //TypedMatrix<int> d(1,3);
      //EXPECT_ANY_THROW(a*d);
  }

  TEST(TypedMatrix, Mult2){
      TypedMatrix<int> a(3, 4);
      TypedMatrix<int> b(4, 3);
      for(int i=0; i<4; i++){
          for(int j=0; j<3; j++){
              a.set(i, j, i*5+j+2);
          }
      }

      for(int i=0; i<3; i++){
          for(int j=0; j<4; j++){
              b.set(i, j, i*3+j-8);
          }
      }
      //std::cout<<"a = "<<a.get(0,0)<<a.get(0,1)<<a.get(0,2)<<"\n";
      //std::cout<<"a = "<<a.get(1,0)<<a.get(1,1)<<a.get(1,2)<<"\n";
      //std::cout<<"a = "<<a.get(2,0)<<a.get(2,1)<<a.get(2,2)<<"\n";
      //std::cout<<"a = "<<a.get(3,0)<<a.get(3,1)<<a.get(3,2)<<"\n";
      TypedMatrix<int> c;
      c = a*b; 
      int ans[4][4];
      for(int i=0; i<4; i++){
          for(int j=0; j<4; j++){
              ans[i][j] = 0;
              for(int k=0; k<3; k++){
                  ans[i][j] += (i*5+k+2)*(k*3+j-8);
              }
          }
      }
      for(int i=0; i<4; i++){
          for(int j=0; j<4; j++){
              EXPECT_EQ(c.get(i,j), ans[i][j]);
          }
      }
  }

  TEST(TypedMatrix, Mult3){
      TypedMatrix<int> a(5, 7);
      TypedMatrix<int> b(7, 5);
      for(int i=0; i<7; i++){
          for(int j=0; j<5; j++){
              a.set(i, j, (i+3)*2-j+9 );
          }
      }

      for(int i=0; i<5; i++){
          for(int j=0; j<7; j++){
              b.set(i, j, (i+5)+j*4 );
          }
      }
      TypedMatrix<int> c;
      c = a*b; 
      int ans[7][7];
      for(int i=0; i<7; i++){
          for(int j=0; j<7; j++){
              ans[i][j] = 0;
              for(int k=0; k<5; k++){
                  ans[i][j] += ((i+3)*2-k+9) *((k+5)+j*4);
              }
          }
      }
      for(int i=0; i<4; i++){
          for(int j=0; j<4; j++){
              EXPECT_EQ(c.get(i,j), ans[i][j]);
          }
      }
  }

  TEST(TypedMatrix2, Add_assign){
      TypedMatrix<int> a(3, 3);
      TypedMatrix<int> b(3, 4);      
      EXPECT_ANY_THROW(a+=b);
  }

  TEST(TypedMatrix2, Mult_assign){
      TypedMatrix<int> a(3, 3);
      TypedMatrix<int> b(3, 4);      
      EXPECT_ANY_THROW(a*=b);
  }

  TEST(TypedMatrix2, Add){
      TypedMatrix<int> a(3, 3);
      TypedMatrix<int> b(3, 4);
      TypedMatrix<int> c;        
      EXPECT_ANY_THROW(c=a+b);
  }

  TEST(TypedMatrix2, Mult){
      TypedMatrix<int> a(3, 4);
      TypedMatrix<int> b(3, 4);
      TypedMatrix<int> c;        
      EXPECT_ANY_THROW(c=a*b);
  }

  TEST(TypedMatrix, Copy){
      TypedMatrix<int> a(3,2);
      TypedMatrix<int> b,c;
      b = a;
      b.set(1,1,11);
      c = b;
      c.set(1,1, 22);
      a = c;
      EXPECT_EQ(a.get(1,1), 22);
      EXPECT_EQ(b.get(1,1), 11);
      EXPECT_EQ(c.get(1,1), 22);
  }

}