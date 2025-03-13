#ifndef UTILITY_H
#define UTILITY_H

/* Struct per contenere una matrice di interi */
typedef struct IntMatrix {
    int rows;
    int cols;
    int **values;
} IntMatrix;

/* Inizializza una matrice di interi con valori random compresi tra 'lower' e 'upper' */
void init_matrix( IntMatrix *matrix, int lower, int upper );

/* Stampa il contenuto di una matrice */
void print_matrix( IntMatrix *matrix ); 

/* Stampa il contenuto di un vettore */
void print_vector( int *vector, int size );

/* Crea un vettore di 'size' elementi interi compresi tra 'lower' e 'upper' */
void create_random_vector( int **out_vect, int size, int lower, int upper );

/* Stampa un separatore in console */
void print_separator( void );

/* Scambia il contenuto di due variabili */
void swap( int *a, int *b );

/* Genera un numero random compreso tra 'lower' e 'upper'  */
int rnd_number( int lower, int upper );

#endif
