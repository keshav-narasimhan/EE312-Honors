// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Keshav Narasimhan
// kn9558
// Slip days used: 0
// Spring 2021
// Include the contents of this file at the top of every file that you submit, replacing the fields within <>.  Do not keep the <>.


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {

    int row = 0;
    int column = 0;
    int k_loop_ind = 0;
    double sum = 0.0;

    while (row < a_rows)        // loop through rows of 'a' matrix
    {
        column = 0;
        while (column < b_cols)     // loop through columns of 'b' matrix
        {
            sum = 0.0;
            k_loop_ind = 0;
            while (k_loop_ind < a_cols)     // inner k loop
            {
                sum += (a[row * a_cols + k_loop_ind] * b[b_cols * k_loop_ind + column]);    // calculate the value of element to go into c matrix
                k_loop_ind++;   // iterate through k loop
            }
            c[row * b_cols + column] = sum;     // put value of sum into the c matrix
            column++;       // go to next column in b matrix
        }
        row++;      // go to next row in a matrix
    }
        
    // https://en.wikipedia.org/wiki/Row-_and_column-major_order
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {

    double **matrix = (double**)malloc(sizeof(double*) * a_rows);       // initialize new matrix using double pointer
    for (int x = 0; x < a_rows; x++)
    {
        matrix[x] = (double*)malloc(sizeof(double) * b_cols);           // initialize each row pointer to hold 'b_cols' amount of doubles
    }

    int row = 0;
    int column = 0;
    int k_loop_ind = 0;
    double sum = 0.0;

    // effectively, do same calculation as previous method, except use 'matrix' instead of 'c'
    while (row < a_rows)        // loop through rows of 'a' matrix
    {
        column = 0;
        while (column < b_cols)     // loop through cols of 'b' matrix
        {
            sum = 0.0;
            k_loop_ind = 0;
            while (k_loop_ind < a_cols) // inner k loop
            {
                sum += (a[row][k_loop_ind] * b[k_loop_ind][column]);        // calculate value of element to go in 'matrix'
                k_loop_ind++;
            }
            matrix[row][column] = sum;      // place the 'sum' into the matrix
            column++;
        }
        row++;
    }

    return matrix;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {

    /*
    * initialize new matrix using double pointer to be a_cols x a_rows
    * each row pointer would point to an 'array' with the length of a_rows (since it's transposed)
    */ 
    double **matrix = (double**)malloc(sizeof(double*) * a_cols);
    for (int x = 0; x < a_cols; x++)
    {
        matrix[x] = (double*)malloc(sizeof(double) * a_rows);
    }

    for (int x = 0; x < a_rows; x++)
    {
        for (int y = 0; y < a_cols; y++)
        {
            matrix[y][x] = a[x][y];     // transpose the matrix
        }
    }
    return matrix;

}
