#include "utils.h"

int main(int argc, char * argv[]) {

    argcheck(argc, 2);
    struct matrix * matrix = matrix_alloc(matrix_init(argv[1]));

    matrix_square_print(matrix->mtx_ptr, matrix->M);
    
    return 0;
}
