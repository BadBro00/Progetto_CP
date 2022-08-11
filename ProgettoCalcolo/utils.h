#ifndef PROGETTOCALCOLO_UTILS_H
#define PROGETTOCALCOLO_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


struct matrix {
    int ** mtx_ptr;
    int M;
};


// Prints error_str on stderr and then terminate the process with exit_code.
void easy_stderr(const char * error_str, int exit_code);

// If main_argc (actual argc) < exp_argc (expected argc), then terminate the process.
void argcheck(int main_argc, int exp_argc);

// Returns matrix file descriptor.
int matrix_init(const char * matrix_path);

// Return 1D char array containing the whole matrix file.
char * matrix_read(int matrix_fd);

// Returns M if the matrix is square, 0 if it's not.
int matrix_check_square(char * file_buf, const char * delimit, const char * delimit2);

// Returns an empty 2D int array (dinamically allocated).
int ** alloc_2D_array(const int size);

// Builds the actual square matrix in mtx_ptr from file_buf
void matrix_build(int ** mtx_ptr, char * file_buf, const char * delimit, const char * delimit2);

// Prints a row x col matrix
void matrix_print(int ** mtx, int row, int col);

// Prints an MxM matrix
void matrix_square_print(int ** mtx, int m);

// Returns a 2D int array containing the matrix.
struct matrix * matrix_alloc(int main_matrix_fd);


#endif //PROGETTOCALCOLO_UTILS_H
