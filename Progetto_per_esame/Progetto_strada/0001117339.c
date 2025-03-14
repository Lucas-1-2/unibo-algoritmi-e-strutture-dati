/*
    Prati Lucas
    Matricola: 0001117339
    Classe A
    lucas.prati@studio.unibo.it
*/

/* Versione 2, gestione input nome file da riga di comando */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>


/* Coordinate di partenza */
#define X0 0
#define Y0 0

/* Lunghezza massima percorso file di input*/
#define MAX_RIGA 256    



typedef struct {
    int x, y;           /* coordinate del ndo */
    long int cost;      /* costo del nodo */
} Node;

typedef struct {
    int x, y;           /* coordinate di un punto */
} Coord;




int n, m;                               /* dimensioni matrice H */
int **H = NULL;                         /* matrice dinamica contenente i valori letti dal file */
unsigned int C_cell, C_height;          /* costo fisso di ogni cella, costo fisso tra celle adiacenti */
long int C_tot = 0;                     /* costo totale definitivo del percorso calcolato */

int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};      /* array per i movimenti possibili (su, giu, destra, sinistra) */
int cx, cy;                                                     /* coordinate del nodo corrente nella funzione Strada() */
long int total_cost;                                            /* Costo totale per il percorso minimo nella funzione Strada() */

/* Creazione indici per cicli */
int i, j;

/* File */
FILE *file;



/* Funzioni */
void Lettura_File(FILE *file1);
long Strada();
void stampaPercorso(Coord **path, int n, int m);
int ordina(const void *a, const void *b);




int main(int argc, char *argv[]) {
 
    /* Apertura file in lettura */
    file = fopen(argv[1], "r");
    assert(file);
    Lettura_File(file);
    /* Chiusura del file al termine della procedura */

    C_tot = Strada();
    printf("%ld\n", C_tot);

    /* Deallocazione della memoria della matrice H */
    for (i = 0; i < n; i++) {
        free(H[i]);
    }
    free(H);
    return 0;
}



/* Lettura del file specificato durante la funzione main() */
void Lettura_File(FILE *file1) {
    fscanf(file1, "%u", &C_cell);
    fscanf(file1, "%u", &C_height);
    fscanf(file1, "%d", &n);
    assert((n >= 5) && (n <= 250));
    fscanf(file1, "%d", &m);
    assert((m >= 5) && (m <= 250));

    /* Creazione dinamica della matrice H[n][m] con verifica */
    H = (int **)malloc(n * sizeof(int *));
    assert(H != NULL);

    for (i = 0; i < n; i++) {
        H[i] = (int *)malloc(m * sizeof(int));
        assert(H[i] != NULL);
    }

    /* Prelievo dal file di n righe contenenti m interi, riempimento della matrice H */
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            assert((fscanf(file1, "%d", &H[i][j])) != EOF);
        }
    }
    fclose(file1);
}



/* richiamato dalla funzione qsort(): ordina i puntatori a e b in ordine crescnte di costo */
int ordina(const void *primo, const void *secondo) {
    return ((Node *)primo)->cost - ((Node *)secondo)->cost;
}



/* Stampa il percorso trovato */
void stampaPercorso(Coord **path, int n, int m) {
    int x = n - 1, y = m - 1;                                       /* Coordinate correnti dutante la stampa del percorso */
    Coord *result = (Coord *)malloc(n * m * sizeof(Coord));         /* array dinamico per memorizzare il percorso inverso, dalla fine all'inizio */    
    int result_size = 0;                                            /* dimansione attuale dell'array result */
    Coord   prev,                                                   /* coordinata percedente del percorso */
            current;

    while (x != -1 && y != -1) {
        current.x = x;
        current.y = y;
        result[result_size++] = current;

        prev = path[x][y];                  /* coordinata percedente del percorso */
        x = prev.x;
        y = prev.y;
    }

    for (i = result_size - 1; i >= 0; i--) {
        printf("%d %d\n", result[i].x, result[i].y);
    }

    printf("-1 -1\n");
    free(result);
}



/* calcola il prcorso minimo e ikl costo totale */
long Strada() {
    long int **cost;      /* Matrice dinamica per costi minimi per raggiungere ogni cella */
    int **visited;        /* Matrice dinamica per celle visitate */
    Coord **path;         /* Matrice dinamica che memorizza il percorso */
    Node *pq;             /* array dinamico utilizzato come coda a prioritàper i nodi da visitare */
    int pq_size;          /* inizializzo a 0 la dimaensione totale della coda appena creata */

    /* Allocazione dinamica delle matrici e verifica */
    cost = (long int **)malloc(n * sizeof(long int *));
    visited = (int **)malloc(n * sizeof(int *));
    path = (Coord **)malloc(n * sizeof(Coord *));

    for (i = 0; i < n; i++) {
        cost[i] = (long int *)malloc(m * sizeof(long int));
        visited[i] = (int *)malloc(m * sizeof(int));
        path[i] = (Coord *)malloc(m * sizeof(Coord));
        for (j = 0; j < m; j++) {
            cost[i][j] = LONG_MAX;
            visited[i][j] = 0;
            path[i][j].x = -1;
            path[i][j].y = -1;
        }
    }

    cost[0][0] = C_cell;
    pq = (Node *)malloc(n * m * sizeof(Node));
    pq_size = 0;

    pq[pq_size].x = 0;
    pq[pq_size].y = 0;
    pq[pq_size].cost = cost[0][0];
    pq_size++;
    qsort(pq, pq_size, sizeof(Node), ordina);

    while (pq_size > 0) {
        Node current = pq[0];                           /* nodo corrente estratto dalla coda a priorità */
        pq[0] = pq[--pq_size];
        qsort(pq, pq_size, sizeof(Node), ordina);

        /* coordinate del nodo corrente */
        cx = current.x;
        cy = current.y;
        if (visited[cx][cy]) continue;
        visited[cx][cy] = 1;

        for (i = 0; i < 4; i++) {
            /* coordinete del nodo adiacente */
            int nx = cx + directions[i][0];
            int ny = cy + directions[i][1];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                /* Costo calcolato per il nodo adiacente */
                long int new_cost = cost[cx][cy] + C_cell + C_height * (H[cx][cy] - H[nx][ny]) * (H[cx][cy] - H[nx][ny]);
                if (new_cost < cost[nx][ny]) {
                    cost[nx][ny] = new_cost;
                    path[nx][ny].x = cx;
                    path[nx][ny].y = cy;
                    pq[pq_size].x = nx;
                    pq[pq_size].y = ny;
                    pq[pq_size].cost = new_cost;
                    pq_size++;
                    qsort(pq, pq_size, sizeof(Node), ordina);
                }
            }
        }
    }

    stampaPercorso(path, n, m);
    /* Costo totale per il percorso minimo */
    total_cost = cost[n-1][m-1];

    /* Libera memoria allocat dinamicamente */
    for (i = 0; i < n; i++) {
        free(cost[i]);
        free(visited[i]);
        free(path[i]);
    }
    free(cost);
    free(visited);
    free(path);
    free(pq);

    return total_cost;
}