/* Implementare un programma pareallelo per l'ambiente multicore con
 * npxnp unità processanti che impieghi OpenMP.
 * Il programma deve essere organizzato come segue:
 * [FATTO] Il core master deve leggere una matrice di dimensioni MxM.
 * [FATTO] Ogni core deve estrarre un blocco di dimensioni (M/np)x(M/np),
 * [FATTO] conservandone i valori in npxnp matrici.
 * TODO: Infine, i core devono collaborare per calcolare la somma delle matrici.
 */


#include "p21fun.h"


/* Main arguments:
 * argv[1]: file containing the matrix
 * argv[2]: np
 */
int main(int argc, char * argv[]) {
    // Argument check
    argcheck(argc, 3);
    printf("[Core master]:\n"
           "file: %s\n"
           "np: %s\n\n",
           argv[1], argv[2]);


    // Argument conversion
    // np
    int np = (int) strtol(argv[2], NULL, 10);
    if (np < 1) easy_stderr("np should be at least 1!", -1);
    printf("npxnp: %d\n\n", np*np);

    // matrix
    struct matrix * matrix = matrix_alloc(matrix_init(argv[1]));
    printf("matrix of size %dx%d:\n", matrix->M, matrix->M);
    matrix_square_print(matrix->mtx_ptr, matrix->M);
    printf("\n");

    printf("[Core master]:\n"
           "RECAP:\n"
           "np: %d\n"
           "npxnp: %d\n"
           "M: %d\n"
           "block_size: %d\n"
           "block_no: %d\n\n",
           np, np*np, matrix->M, matrix->M/np, np*np);

    // Setting number of threads
    omp_set_num_threads(np*np);


    // Array of matrix pointers
    struct matrix * mtx_array = (struct matrix *) malloc(sizeof(struct matrix) * (np*np));


    // Block extraction
    #pragma omp parallel default(none), shared(matrix, np, mtx_array)
    {
        mtx_array[omp_get_thread_num()] = * matrix_block_extract(matrix, np, omp_get_thread_num());
    }


    // Printing all blocks
    for (int i = 0; i < np*np; ++i) {
        printf("[Block %d]:\n", i);
        matrix_square_print(mtx_array[i].mtx_ptr, mtx_array[0].M);
        printf("\n");
    }

    
    return 0;
}
