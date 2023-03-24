#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include "Globales.h"

#define MAX_DEP     5
#define VOL         4

//VOID PARA VOLTEAR LOS PANCAKES
void flip(char *x, int n){
    char c;
    int i, j, longs;
    if(n<2){
        return;
    }
    longs = strlen(x);//longs representa la cantidad de caracteres que tiene x
    if(n>longs){
        return;
    }
    for ( i = longs-n, j = longs-1 ; i<j ; i++,j-- ) {
		c = x[i];
		x[i] = x[j];
		x[j] = c;
	}
	/*Funcion que representa la manera en la que se voltean los pancakes, de manera que
	el flip intercambia la posicion del primer elemento con la del último, la del segundo
	con la del penultimo y así sucesivamente hasta llegar a la mitad de la cadena*/
}

void disorder(char *x, int n){
    int i, prevI;
    int L = strlen(x)-1;
	time_t t;

	srand((unsigned) time(&t));

	prevI = 0;
	for ( ; n>0 ; n--) {
            i = rand()%L + 2;
		if ( i == prevI ) {
			n++;
			continue;
		}
		printf("%d ",i);
		flip(x,i);
		prevI = i;
	}

}

bool iddfs(char *x, int prevNode){
    nodes++;

    if(!strncmp(x, Goal, sized)){
        solFound = true;
        if(solSize < bestSolSize){
            for(int i = 0; i < solSize; i++){
                bestSol[i] = actSol[i];
                bestSolSize = solSize;
                maxDepht = bestSolSize -1;
            }
        }
        return true;
    }

    if(maxDepht <= solSize){
        return false;
    }

    for(int i = 2; i <= sized; i++){
        if(i==prevNode)
            continue;
        flip(x, i);
        actSol[solSize++] = i;
        if(iddfs(x, i)){
            flip(x, i);
            return true;
        }
        flip(x, i);
        solSize--;
    }
    return false;
}

void BPI(char *x, int prevNode){
    bool iddfs( char *x, int prevNode);

    solFound = false;
    for(maxDepht = 1; !solFound; maxDepht++){
        solSize = 0;
        bestSolSize = MAX;
        if(iddfs(x, 0)){
            break;
        }
    }

}

int main()
{
    int i;
    int initDisorder = 20;
    char Pancakes[64], OriginalPancake[64];

    //VARIABLES
    maxDepht = MAX_DEP;
    solSize = 0;
    bestSolSize = MAX;
    nodes = 0;
    sized = VOL;
    strcpy(Goal, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strncpy(Pancakes, Goal, sized);
    Pancakes[sized] = '\0'; //establece el caracter nulo para indicar el final de la cadena

    puts("Los pancakes se están desordenando, espere");
	disorder(Pancakes, initDisorder);
	printf(": %s\n",Pancakes);
	strcpy(OriginalPancake, Pancakes);

	puts("\nResuelto por\t\t\tNodos\tSolucion");

	strcpy(Pancakes, OriginalPancake);
	printf("\nProfundidad iterativa\t\t");

    BPI(Pancakes, 0);
	printf("%ld\t", nodes);
	for ( i=0; i<bestSolSize ; i++ ){
            printf("%d ", bestSol[i]);
		}
}
