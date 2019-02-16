#ifndef utilities
#define utilities

#include<math.h>
#include<iostream>
#include<vector>
#include<map>
#include<stdexcept>
#include<cstdlib>
#include <algorithm>
#include "typed_matrix.h"
using std::vector;

void sort_by_magnitude(vector<double> &a);

TypedMatrix<double> read_matrix_csv(const string path);

void write_matrix_csv(const TypedMatrix<double> &matrix, const string path);

std::map<string, int> occurence_map(const string path);

#endif