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

vector<double> sort_by_magnitude(vector<double> &v);

TypedMatrix<double> read_matrix_csv(const string path);

void write_matrix_csv(const TypedMatrix<double> &matrix, const string path);

std::map<string, int> occurrence_map(const string path);

#endif