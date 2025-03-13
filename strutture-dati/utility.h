#ifndef UTILITY_H
#define UTILITY_H

/* Stampa il contenuto di un vettore */
void print_vector( int *vector, int size );

/* Crea un vettore di 'size' elementi interi compresi tra 'lower' e 'upper' */
void create_random_vector( int **out_vect, int size, int lower, int upper );

/* Stampa un separatore in console */
void print_separator( void );

/* Scambia il contenuto di due variabili */
void swap( int *a, int *b );

#endif
