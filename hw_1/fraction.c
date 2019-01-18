#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce ( Fraction a ) {
    if (a.num == 0 && a.den != 0){
        return (Fraction) {0,1};
    }
    
    else if (a.den == 0 && a.num != 0)
    {
        return (Fraction) {1,0};
    }

    else if (a.num == 0 && a.den == 0){
        return (Fraction) {0,0};
    }
    
    else{
        int num1, num2, c;
        if(a.num > a.den){
            num1 = a.num;
            num2 = a.den;
        }
        
        else {
            num1 = a.den;
            num2 = a.num;
        }

        while(num2>0){
            c = num1 % num2;
            num1 = num2;
            num2 = c;
        }

        return (Fraction) {a.num / num1, a.den / num1};
    }
    
}