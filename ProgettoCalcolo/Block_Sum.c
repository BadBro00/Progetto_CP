// Bozza somma blocchi
#pragma omp parallel private(sum),shared(k,totsum)
    {
        sum = 0;
        totsum=0;
        k = 0;
        printf("|Blocco %d|\n",k);
        for(int i=0;i<mtx_array->M;i++){
            for(int j=0;j<mtx_array->M;j++){
                sum += mtx_array[k].mtx_ptr[i][j];
            }
        }
        printf("Somma blocco = %d\n",sum);
        totsum += sum;
        printf("\t|Aggiungo la somma alla somma totale = %d|\n",totsum);
        k = k + 1;
    }
