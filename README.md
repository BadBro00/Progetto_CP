# L'utilizzo di questo codice e' vietata in tutte le forme

---

# Progetto per l'esame di "Calcolo Parallelo", all'Università degli Studi di Napoli "Parthenope"

- [Set-Up Ambiente](###Set-Up-ambiente-di-lavoro)
- [Descrizione WorkFlow](###Spiegazione)
- [Funzionamento](###Funzionamento)
- 
---

### Set-Up ambiente di lavoro

Questo progetto viene eseguito in **Docker**, runnato tramite *WSL*.\
Il `Dockerfile` e' scaricato dalla repo del docente [wget https://raw.githubusercontent.com/delucap/Docker_MPI/main/Dockerfile].

**Setting Ambiente di Lavoro**:\
 - `docker build -t cpd_mpi .`
 - `docker run -it -d -t cpd_mpi:latest`
 - `docker ps`
 - `docker start -i <id_istanza>`
Questo attivera' l'istanza di Docker contenente l'ambiente di lavoro.\

Successivamente si puo' eseguire, *per ogni istanza*, ciascuno dei seguenti comandi:
- `git clone https://github.com/delucap/Docker_MPI.git`
- `sh user.sh` *Crea l'utente cpd2021, la cui pw e' il nome utente*\
Per ogni nodo, eseguire `ifconfig` e segnare gli `IP` di ciascun nodo.\
Va eseguito poi `sh setup.sh <IP_1> <IP_2> <IP_3> <IP_4>` .

**Cambio Keys e Utenti**:\
- `su cpd2021.`
- `ssh-copy-id master`
- `ssh-copy-id node01`
- `ssh-copy-id node02`
- `ssh-copy-id node03`

**Connessione al nodo *MASTER* del cluster AWS**:\
`ssh -i cpd1.pem ubuntu@<master_node>`\
*Accesso all'utente*:
`su cpd1`

Tramite gedit,vi, o vim, aprire un file testo e digitare:\
`master slots=4`\
`node01 slots=4`\
`node02 slots=4`\
`node03 slots=4`\
Salvare tale file come `esercizio1.c`

**Compilazione**:\
`mpicc esercizio1.c -o esercizio1` [ oppure `mpicc esercizio1.c`, per poi eseguirlo come a.out ]

**Download script bash**:\
`wget https://github.com/delucap/CPD1-AWSTest/blob/master/employAWS.sh`

Eseguiamo quindi il file con `mpirun <nomefile>`

---

## Spiegazione:

### Generazione Matrice

Il file `mtxtxt.c` crea una matrice, tramite la funzione `file_matrix_build(matrix_file, (int) strtol((argv[2]), NULL, 10))`\
> [!NOTE]
> La matrice viene generata partendo da un file di testo `mtxtxt.txt` (contenente la matrice creata randomicamente), mediante la function `int matrix_file = matrix_rdwr_append_init(argv[1]);`.\

Il file `p21fun.c` fornisce un set di function utili al lavoro sulla matrice, come la function `void file_matrix_build(int matrix, int M)`, che *genera la matrice randomica MxM nel fd scelto* e `void matrix_build(int ** mtx_ptr, char * file_buf, const char * delimit, const char * delimit2)`, che converte un array di char in una matrice int.

Il progetto e' strutturato nel seguente modo:\
>[!NOTE]
>Implementare un programma pareallelo per l'ambiente multicore con npxnp unità processanti che impieghi OpenMP
1. Il core **Master** legge una matrice *MxM*
2. Ogni core deve estrarre un blocco, di dimensioni *(M/np)x(M/np)*, conservandone i valori in matrici
3. I core dovranno collaborare per calcolare la **somma** delle suddette matrici

---

### Funzionamento

Il programma segue questo flusso:\
1. Si estrae `np` dagli argument passati al main
2. Tramite `OMP`, si setta il numero di threads da utilizzare
3. Viene generata la matrice, e l'array di matrici (mediante `struct matrix * mtx_array = (struct matrix *) malloc(sizeof(struct matrix) * (np*np));`)
4. Ogni core, *in parallelo*,  estrae un blocco, in base al proprio **TID**, mediante `mtx_array[tid] = * matrix_block_extract(matrix, np, tid);`
5. Viene generata la matrice *sum*, che conterra' la matrice sommata dei vari blocchi
6. Viene effettuata la somma effettiva, mediante:
   ```
   for (int i = 0; i < nloc; ++i) {
            temp_sum = matrix_sum(temp_sum, &mtx_array[i + nloc * tid + step]);
        }

        #pragma omp critical
            sum_matrix = matrix_sum(sum_matrix, temp_sum);
   ```
  
>[!NOTE]
> L'istruzione ***critical*** fa eseguire l'istruzione *ad un thread alla volta*
7. L'istruzione finale e' la run del codice *in sequenziale*, per comparare i tempi d'esecuzione dell'algoritmo

---
