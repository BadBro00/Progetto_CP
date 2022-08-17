\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\utils.h
void create_submatrix(int M);

void mat_init();
void prt_mat();
int getDimension(struct matrix *matri);
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\utils.c
int **mat;
int dimension;

void mat_init(){
    mat = malloc(dimension*sizeof(int*));
    for(int i=0;i<dimension;i++){
        mat[i] = malloc(dimension*sizeof(int));
    }
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            mat[i][j] = rand()%256;
        }
    }
}
void prt_mat(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            printf(" [%d] ",mat[i][j]);
        }
        printf("\n");
    }
}
int getDimension(struct matrix * Matrix){
    int cnt = 0;
    for(int i=0;i<Matrix->M;i++){
        cnt++;
    }
    return cnt;
}
void create_submatrix(int M){
    int id_thread,num_thread;
    int newdim;
    int **v;
    #pragma omp parallel private(id_thread),shared(M,num_thread,v,newdim)
    {
        id_thread = omp_get_thread_num();
        num_thread = omp_get_num_threads();
        newdim = M/num_thread+1;
        printf("Dimensione sottomatrici = %d\n",newdim);
        v = malloc(newdim*sizeof(int*));
        for(int i=0;i<newdim;i++){
            v[i] = malloc(newdim*sizeof(int));
        }
        for(int i=id_thread;i<newdim;i++){
            for(int k=0;k<newdim;k++){
                printf("mat(%d,%d) : %d\n",i,k,mat[i][k]);
                v[i][k] = mat[i][k];
            }
        }
        printf("\tIl thread %d/%d ha copiato la sua parte di matrice\n",id_thread,num_thread);
        for(int i=0;i<newdim;i++){
            for(int j=0;j<newdim;j++){
                printf(" [%d] ",v[i][j]);
            }
            printf("\n");
        }
    }
}
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\main.c
#include "utils.h"

int main(int argc, char * argv[]) {
    argcheck(argc, 2);
    struct matrix* matrix = matrix_alloc(matrix_init(argv[1]));
    matrix_square_print(matrix->mtx_ptr, matrix->M);
    printf("ESTRAZIONE SOTTOMATRICI\n");
    matrix_init(argv[1]);
    prt_mat();
    create_submatrix(getDimension(matrix));
    return 0;
}
