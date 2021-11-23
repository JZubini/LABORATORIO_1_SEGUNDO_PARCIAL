/*
 * Juegos.c
 *
 *  Created on: 17 oct. 2021
 *      Author: Julián Zubini
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Juegos.h"
#include "UTN_Ingreso.h"

#define FALSE 0
#define TRUE 1

Juego* juegos_new(){
	Juego* pJuego = malloc(sizeof(Juego));
	return pJuego;
}

void juegos_delete(Juego* this){
	if(this != NULL){
		free(this);
	}
}

int juegos_setNombreDelJuego(Juego* this,char* nombreDelJuego){
	int retorno = FALSE;
	if(this != NULL && nombreDelJuego != NULL){
		strcpy(this->nombreDelJuego,nombreDelJuego);
		retorno = TRUE;
	}
	return retorno;
}

int juegos_getNombreDelJuego(Juego* this,char* nombreDelJuego){
	int retorno = FALSE;
	if(this != NULL && nombreDelJuego != NULL){
		strcpy(nombreDelJuego,this->nombreDelJuego);
		retorno = TRUE;
	}
	return retorno;
}

Juego* juegos_newParametros(char* nombreDelJuego){
	Juego* retornoAuxArcade;
	if(nombreDelJuego != NULL){
		if(UTN_validarCadenaAlfanumericaIngresada(nombreDelJuego) == TRUE){
			retornoAuxArcade = juegos_new();
			if(retornoAuxArcade != NULL){
				juegos_setNombreDelJuego(retornoAuxArcade, nombreDelJuego);
			}
		}
	}
	return retornoAuxArcade;
}













