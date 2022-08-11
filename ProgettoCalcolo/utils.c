#include "utils.h"


void easy_stderr(const char * error_str, const int exit_code) {
    fprintf(stderr, "%s\n", error_str);
    fflush(stderr);

    exit(exit_code);
}


void argcheck(const int main_argc, const int exp_argc) {
    // Checking if arguments are passed correctly.
    if (main_argc < exp_argc)
        easy_stderr("invalid arguments number!", -1);
}


int matrix_init(const char * matrix_path) {
    int fd;

    // If matrix's file can't be opened, error.
    if ((fd = open(matrix_path, O_RDONLY, 0777)) < 1 )
        easy_stderr("matrix's file can't be opened or does not exists!", -1);

    // *** DEBUG *** printf("matrix on fd %d\n", fd);

    return fd;
}


char * matrix_read(const int matrix_fd) {
    // Getting matrix's file size and creating a char buffer.
    off_t tot_bytes = lseek(matrix_fd, 0, SEEK_END);
    char * file_buf_to_return = (char *) malloc(sizeof(char) * tot_bytes);

    // Resetting fd offset.
    lseek(matrix_fd, 0, SEEK_SET);

    // Reading whole matrix file on file_buf.
    int read_bytes = 0;
    if ((read_bytes = read(matrix_fd, file_buf_to_return, tot_bytes)) <= 0)
        return NULL;

    // *** DEBUG *** printf("tot_bytes %lld, read_bytes %d\n\n", tot_bytes, read_bytes);

    return file_buf_to_return;
}


int matrix_check_square(char * file_buf, const char * delimit, const char * delimit2) {
    // Vars for strtok_r
    char * tok, * tok2;
    tok = tok2 = NULL;
    char * last, * last2;
    last = last2 = NULL;

    // Vars to count rows and columns.
    int row_count = 0;
    int col_count = 0;
    int last_col_count = 0;

    // Outermost for iterating on row (counting rows). Innermost for iterating on cols (counting cols).
    for (tok = strtok_r(file_buf, delimit, &last); tok; tok = strtok_r(NULL, delimit, &last)) {
        col_count = 0; // Counting elements on the row for each iteration.
        row_count++;

        for (tok2 = strtok_r(tok, delimit2, &last2); tok2; tok2 = strtok_r(NULL, delimit2, &last2))
            col_count++;

        // No col_count and last_col_count comparison needed on the first iteration.
        // If col_count != last_col_count the matrix isn't square.
        if (row_count > 1 && col_count != last_col_count)
            return 0;

        // *** DEBUG *** printf("row: %d, col %d, last %d\n\n", row_count, col_count, last_col_count);

        last_col_count = col_count;
    }

    // Check if the matrix is square by comparing row and col number.
    if (col_count != row_count) {
        return 0;
    }

    // Either last_col_count and row_count can be returned because it's a square matrix
    return last_col_count;
}


int ** alloc_2D_array(const int size) {
    int ** matrix_out_ptr = (int **) malloc(sizeof(int *) * size);
    for (int i = 0; i < size; ++i)
        matrix_out_ptr[i] = (int *) malloc(sizeof (int) * size);

    return matrix_out_ptr;
}

void matrix_build(int ** mtx_ptr, char * file_buf, const char * delimit, const char * delimit2) {
    // Vars for strtok_r
    char * tok, * tok2;
    tok = tok2 = NULL;
    char * last, * last2;
    last = last2 = NULL;

    int row_index, col_index;
    row_index = col_index = 0;
    for (tok = strtok_r(file_buf, delimit, &last); tok; tok = strtok_r(NULL, delimit, &last)) {
        col_index = 0;
        for (tok2 = strtok_r(tok, delimit2, &last2); tok2; tok2 = strtok_r(NULL, delimit2, &last2)) {
            mtx_ptr[row_index][col_index] = (int) strtol(tok2, NULL, 10);
            col_index++;
        }
        row_index++;
    }
}


void matrix_print(int ** mtx, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("[%d] ", mtx[i][j]);
        }
        printf("\n");
    }
}


void matrix_square_print(int ** mtx, int m) {
    matrix_print(mtx, m, m);
}


struct matrix * matrix_alloc(const int main_matrix_fd) {
    // Reading the whole matrix file in a 1D char array.
    char * file_buf;
    if ((file_buf = matrix_read(main_matrix_fd)) == NULL)
        easy_stderr("matrix was not read on file_buf!", -1);

    // *** DEBUG *** printf("%s\n", file_buf);


    // Checking if the matrix is square.
    char delimit[] = "\n";
    char delimit2[] = " ";
    int M; // Size of the square matrix

    // We need to pass a copy of file_buf because strtok_r modifies it.
    char * buf_to_pass = (char *) malloc(sizeof(char) * strlen(file_buf));
    if ((M = matrix_check_square(strcpy(buf_to_pass, file_buf), delimit, delimit2)) == 0) {
        free(file_buf);
        free(buf_to_pass);
        easy_stderr("the matrix is not square!", -1);
    }


    // Creating the actual C int matrix (dinamically allocated).
    int ** matrix_ptr = alloc_2D_array(M);


    // Building the actual matrix.
    matrix_build(matrix_ptr, strcpy(buf_to_pass, file_buf), delimit, delimit2);


    // *** DEBUG *** matrix_print(matrix_ptr, M, M);


    // Creating the return struct
    struct matrix * to_return = (struct matrix *) malloc(sizeof(struct matrix));
    to_return->mtx_ptr = matrix_ptr;
    to_return->M = M;

    return to_return;
}
