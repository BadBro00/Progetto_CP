// Bozza somma blocchi
#pragma omp parallel private(sum),shared(k,totsum)
{
        //Ogni thread ha la sua somma privata, mentre la var totsum e' condivisa, perche' ogni thread deve saperne il valore al momento della somma
        sum = 0;
        totsum=0;
        k = 0;
        printf("|Blocco %d|\n",k);
        //Scorro il k-simo blocco
        for(int i=0;i<mtx_array->M;i++){
            for(int j=0;j<mtx_array->M;j++){
                //Aggiorno la somma del valore di mtx_array[i].mtx_ptr[i][j] (ovvero l'elemento di indici (i,j) del k-simo blocco
                sum += mtx_array[k].mtx_ptr[i][j];
            }
        }
        //La somma del k-simo blocco, contenuta in sum, viene sommata a totsum (che era inizializzata a 0)
        printf("Somma blocco = %d\n",sum);
        totsum += sum;
        printf("\t|Aggiungo la somma alla somma totale = %d|\n",totsum);
        k = k + 1; //Aumento k per impostarlo al successivo valore, che identifica il blocco successivo
}
