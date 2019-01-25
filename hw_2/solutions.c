#include "solutions.h"
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>

int running_total ( int a ) {
    static int x = 0;
    x = x+a;
  return x;
}

void reverse_in_place ( int *x, int size ){
    int i, temp;
    for ( i = 0 ; i < size/2 ; i++){
        temp = x[i];
        x[i] = x[size - i -1];
        x[size - i -1] = temp;
    }
}

int *reverse ( int *x, int size ){
    int i, temp;
    int * y = (int *) calloc(size,sizeof(int));
    for ( i = 0 ; i < size ; i++){
        y[i] = x[size - i -1];
    }
    return y;
}

int num_instances (int *a, int length, int value){
    int i, number = 0;
    for ( i = 0; i<length; i++ ){
        if ( a[i] == value){
            number++;
        }
    }
    return number;
}

int *to_set(int *a, int length, int *n){

    int *b = (int *) calloc(length, sizeof(int));
    int *num = n;
    int flag[1000] = { 0 };
    int new_arr_idx = 0;
    int i;
    for ( i = 0; i<length; i++ ){
        if ( flag[a[i]] == 0){
            b[new_arr_idx] = a[i];
            new_arr_idx++;
            flag[a[i]] = 1;
        }
    }
    *num = new_arr_idx+1;
    return b;
}

Point negate(Point p) {
    return (Point) { -p.x, -p.y, -p.z };
}


Point *map (Point a [], int length, Point f_ptr (Point)){
    Point * b = (Point *) calloc(length, sizeof(Point));
    int i;
    for ( i = 0; i < length; i++){
        b[i] = f_ptr( a[i] );
    }
    return b;
}
static Status error = NOT_INITIALIZED_ERROR;
static Stack ss;
static Stack *s = &ss;
void rpn_init (){
    //Stack ss;
    //Stack * s = &ss;
    if(!s->base)
        free(s->base);
    s->base = (double *)calloc(100, sizeof(double));
    s->top = s->base;
    error = OK;
}

Status rpn_error (){
   return error;
}

double rpn_pop (){
    double pn;
    if (error == OK){
        if (s->top == s->base){
            error = POP_ERROR;
            return 0.0;
        }else{
            pn = *--(s->top);
            return pn;
        }
    }else{
        return 0.0;
    }
}


void rpn_push ( double value ){
    static int s_nm;
    static int m_nm = 1;
    int expend_nm;
    if (error == OK){
        if ((value > DBL_MAX) || (value < -DBL_MAX)){
            error = OVERFLOW_ERROR;
        }else{
            *(s->top)=value;
            s->top++;
            s_nm++;
            //printf("s_nm =  %d", s_nm);
            if (s_nm >99){
                m_nm++;
                expend_nm = m_nm *100;
                s->base = (double *)realloc(s->base, expend_nm *sizeof(double));
                s_nm = 0;
                //printf("m_nm = %d expent to = %d",m_nm, expend_nm);
            }
        }  
    }
}


void rpn_negate (){
    double ng_nm;
    if (error == OK){
        if (s->top == s->base){
            error = NEGATE_ERROR;
        }else{
             ng_nm = rpn_pop();
             rpn_push(ng_nm*-1);
        }
    }  
}

void rpn_add (){
    double first,second;
    if(error == OK){
        if (s->top == s->base){
            error = ADD_ERROR;
        }else{
            first = rpn_pop ();
            second = rpn_pop ();
            if (((first+second) > DBL_MAX) || ((first+second) < -DBL_MAX)){
                error = OVERFLOW_ERROR;
            }else{
                rpn_push(first+second);
            }
        }
        
    }
}

void rpn_multiply (){
   double first,second;
    if(error == OK){
        if (s->top == s->base){
            error = MULT_ERROR;
        }else{
            first = rpn_pop ();
            second = rpn_pop ();
            if (((first*second) > DBL_MAX) || ((first*second) < -DBL_MAX)){
                error = OVERFLOW_ERROR;
            }else{
                rpn_push(first*second);
            }
        }
        
    }
}

void rpn_free (){
   free(s->base);
   error = NOT_INITIALIZED_ERROR;
}




