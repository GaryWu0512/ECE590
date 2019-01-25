#ifndef SOLUTIONS_H
#define SOKUTIONS_H


typedef struct {
  double x, y, z;
} Point;

typedef struct{
	double *top;
	double *base;
} Stack;

typedef enum status
{ 
  OK, NOT_INITIALIZED_ERROR, POP_ERROR, NEGATE_ERROR, MULT_ERROR, ADD_ERROR, OVERFLOW_ERROR 
} Status;

int running_total ( int a );

void reverse_in_place ( int *x, int size );

int *reverse ( int *x, int size );

int num_instances (int *a, int length, int value);

int *to_set (int *a, int length, int *n);

Point negate (Point p);

Point *map (Point a [], int length, Point f (Point));

void rpn_init ();

Status rpn_error ();

double rpn_pop ();

void rpn_push(double value);

void rpn_negate();

void rpn_add ();

void rpn_multiply ();

void rpn_free ();

#endif