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

    // printing data
    printf("[MASTER THREAD]:\n"
           "RECAP:\n"
           "np: %d\n"
           "npxnp: %d\n"
           "M: %d\n"
           "block_size: %d\n"
           "block_no: %d\n\n",
           np, np*np, matrix->M, matrix->M/np, np*np);


    // Setting number of threads for parallel region 1
    omp_set_num_threads(np*np);


    // Allocating array of matrix pointers
    struct matrix * mtx_array = (struct matrix *) malloc(sizeof(struct matrix) * (np*np));

    // Other useful data
    int tid;

    // [PARALLEL REGION 1]
    #pragma omp parallel default(none), shared(matrix, np, mtx_array), private(tid)
    {
        // Tid assignation
        tid = omp_get_thread_num();

        // Block extraction
        mtx_array[tid] = * matrix_block_extract(matrix, np, tid);
    }


    // Printing all blocks
    for (int i = 0; i < np*np; ++i) {
        printf("[Block %d]:\n", i);
        matrix_square_print(mtx_array[i].mtx_ptr, mtx_array[0].M);
        printf("\n");
    }


    // Setting number of threads for parallel region 2
    omp_set_num_threads(np);

    // Allocating and initializating sum matrix
    struct matrix * sum_matrix = initialize_sum_matrix(matrix->M/np);

    // Temp sum matrix pointer
    struct matrix * temp_sum;

    // Other useful data
    int nloc;
    int actual_threads_no;
    int reminder;
    int step;

    // [PARALLEL REGION 2]
    #pragma omp parallel default(none), shared(np, mtx_array, sum_matrix, reminder), private(tid, nloc, temp_sum, actual_threads_no, step)
    {
        // Initializing threads no, tid and other data
        actual_threads_no = omp_get_num_threads();
        tid = omp_get_thread_num();
        nloc = (np*np) / actual_threads_no;
        reminder = (np*np) % actual_threads_no;

        printf("[Core %d]: t_no = %d, nloc = %d, r = %d\n", tid, actual_threads_no, nloc, reminder);

        // Allocating temp sum matrix pointer
        temp_sum = initialize_sum_matrix(sum_matrix->M);

        // *** DEBUG *** printf("[Core %d]: sum_mtx:\n", tid); matrix_square_print(temp_sum->mtx_ptr, temp_sum->M);


        // Job subdivision
        if (tid < reminder) {
            nloc++;
            step = 0;
        }
        else {
            step = reminder;
        }


        // SUM ALGORITHM
        for (int i = 0; i < nloc; ++i) {
            temp_sum = matrix_sum(temp_sum, &mtx_array[i + nloc * tid + step]);
        }
        sum_matrix = matrix_sum(sum_matrix, temp_sum);
    }


    // Printing sum matrix
    printf("[Core %d]: Sum matrix: \n", omp_get_thread_num());
    matrix_square_print(sum_matrix->mtx_ptr, sum_matrix->M);


    return 0;
}
