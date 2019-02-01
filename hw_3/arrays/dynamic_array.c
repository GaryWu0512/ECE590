#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_first(DynamicArray * da);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    DynamicArray * result = DynamicArray_copy(DynamicArray * da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

double DynamicArray_min(const DynamicArray * da){
    assert(DynamicArray_size(da) > 0);
    double min  = da->buffer[index_to_offset(da, 0);
    int i;
    for (i = 1; i<DynamicArray_size(da); i++){
        if ( da->buffer[index_to_offset(da, i)] < min ){
            min = da->buffer[index_to_offset(da, i)];
        }
    }
    return min;
}

double DynamicArray_max(const DynamicArray * da){
    assert(DynamicArray_size(da) > 0);
    double max  = da->buffer[index_to_offset(da, 0);
    int i;
    for (i = 1; i<DynamicArray_size(da); i++){
        if ( da->buffer[index_to_offset(da, i)] > max ){
            max = da->buffer[index_to_offset(da, i)];
        }
    }
    return max;
}

double DynamicArray_mean_(const DynamicArray * da){
    assert(DynamicArray_size(da) > 0);
    double mean, total = 0;
    int i ,b;
    for (i = 0; i<DynamicArray_size(da); i++){
        b = da->buffer[index_to_offset(da, i)];
        total = total + b;
    }
    mean = total / DynamicArray_size(da);
    return mean;
}

double DynamicArray_median(const DynamicArray * da){
    assert(DynamicArray_size(da) > 0);
    double median;
    int i  
    i = DynamicArray_size(da)/2;
    if ( DynamicArray_size(da)%2 == 0 ){
        median = da->buffer[index_to_offset(da, i-1)];
    }else{
        median = da->buffer[index_to_offset(da, i)];
    }
    return median;
}

double DynamicArray_sum(const DynamicArray * da){
    assert(DynamicArray_size(da) > 0);
    double total = 0;
    int i ,b;
    for (i = 0; i<DynamicArray_size(da); i++){
        b = da->buffer[index_to_offset(da, i)];
        total = total + b;
    }
    return total;
}

double DynamicArray_last(const DynamicArray * da){
    assert(DynamicArray_size(da) > 0);
    double last;
    last = DynamicArray_get(da, DynamicArray_size(da)-1);
    return last;
}

double DynamicArray_first(const DynamicArray * da){
    assert(DynamicArray_size(da) > 0);
    double first;
    first = DynamicArray_get(da, 0);
    return first;
}

DynamicArray * DynamicArray_copy(const DynamicArray * da) {
    DynamicArray * db = (DynamicArray *) malloc(sizeof(DynamicArray));
    db->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    db->buffer = (double *) calloc ( db->capacity, sizeof(double) ); 
    db->origin = db->capacity / 2;
    db->end = db->origin;
    int i;
    for (i = 0; i<i<DynamicArray_size(da); i++){
        db->buffer[index_to_offset(db, i)] = da->buffer[index_to_offset(da, i)]
    }
    return db;
}

DynamicArray * DynamicArray_range(double c, double d, double step){
    DynamicArray * a = DynamicArray_new();
    int i;
    int times = (d-c)/step+1;
    for (i = 0; i < times ; i++){
        DynamicArray_push(a,c+(i*step);
    }
    return a;
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ){
    DynamicArray * c = DynamicArray_new();
    int i,j;
    double nm_a, nm_b;
    for (i = 0;i<DynamicArray_size(a);i++){
        nm_a = a->buffer[index_to_offset(a, i)];
        DynamicArray_push(c,nm);
    }
    for (j = 0;i<DynamicArray_size(a);i++){
        nm_b = b->buffer[index_to_offset(b, j)];
        DynamicArray_push(c,nm_b);
    }
}

double * DynamicArray_take(const DynamicArray * a, int b){
    space = abs(b)
    double *s = (double *) calloc(space, sizeof(double));
    int i;
    if (b>0){
        for (i = 0; i<space; i++){
            if (a->buffer[index_to_offset(a, i)] != 0 ){
                s[i] = a->buffer[index_to_offset(a, i)];
            }else{
                s[i] = 0;
            }            
        }
    }else{
        for (i = 0; i<space; i++){
            if (a->buffer[index_to_offset(a, DynamicArray_size(a)-1-i)] != 0 ){
                s[i] = a->buffer[index_to_offset(a, DynamicArray_size(a)-1-i)];
            }else{
                s[i] = 0;
            }            
        }
    }
    return s;
}
