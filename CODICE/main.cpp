#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int M;
int **mat;
int *sums;
int fine = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void mat_init(){
    mat = malloc(M*sizeof(int*));
    for(int i=0;i<M;i++){
        mat[i]=malloc(M*sizeof(int));
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            mat[i][j] = rand()%256;
        }
    }
}

void prt_mat(){
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            printf(" %d ",mat[i][j]);
        }
        printf("\n");
    }
}

void* do_ops(void* args){
    int indice = *(int *)args;
    pthread_mutex_lock(&mutex);
    for(int idx=indice;idx<M/2;idx++){
        printf("TID: %lu, indice: %d, idx:%d\n",pthread_self(),indice,idx);
        printf("Sommo elemento (%d,%d) [%d] al vettore\n",indice,idx,mat[indice][idx]);
        sums[idx] += mat[indice][idx];
    }
    pthread_mutex_unlock(&mutex);
    if(indice == M)
        fine = 1;
    pthread_exit(NULL);
}
void* prt(void* args){
    for(int i=0;i<M;i++){
        printf("Sums[%d] = %d\n",i,sums[i]);
    }
    pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
    pthread_t tids[M];
    sums = malloc(M*sizeof(int));
    srand(time(NULL));
    if (argc != 2) {
        fprintf(stderr, "Uso: ./a.out <M>\n");
        exit(-1);
    }
    M = atoi(argv[1]);
    if (M <= 0) {
        fprintf(stderr, "Uso <M> > 1\n");
        exit(-2);
    }
    mat_init();
    printf("\t\t|MATRICE|\n");
    prt_mat();
    printf("\tCreo M thread\n");
    for (int i = 0; i < M; i++) {
        printf("Creo thread indice: %d\n",i);
        pthread_create(&tids[i], NULL, do_ops, (void *)&i);
    }
    for (int i = 0; i < M; i++) {
        pthread_join(tids[i], NULL);
    }
    pthread_t ultimo;
    if (fine = 1){
        pthread_create(&ultimo, NULL, prt, NULL);
    }
    pthread_join(ultimo,NULL);
}
