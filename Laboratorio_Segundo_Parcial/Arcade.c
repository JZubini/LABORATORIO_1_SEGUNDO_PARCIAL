/*
 * Arcade.c
 *
 *  Created on: 20 nov. 2021
 *      Author: Julián Zubini
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UTN_Ingreso.h"
#include "Arcade.h"

#define TRUE 1
#define FALSE 0
#define MONO 0
#define ESTEREO 1

Arcade* arcade_new(){
	Arcade* pArcade = malloc(sizeof(Arcade));
	return pArcade;
}

void arcade_delete(Arcade* this){
	if(this != NULL){
		free(this);
	}
}

int arcade_setID(Arcade* this,int id){
	int retorno = FALSE;
	if(this != NULL && id >= 0){
		retorno = TRUE;
		this->IDArcade = id;
	}
	return retorno;
}

int arcade_getID(Arcade* this,int* id){
	int retorno = FALSE;
	if(this != NULL && id != NULL){
		retorno = TRUE;
		*id = this->IDArcade;
	}
	return retorno;
}

int arcade_setNacionalidad(Arcade* this,char* nacionalidad){
	int retorno = FALSE;
	if(this != NULL && nacionalidad != NULL){
		retorno = TRUE;
		strcpy(this->nacionalidadArcade,nacionalidad);
	}
	return retorno;
}

int arcade_getNacionalidad(Arcade* this,char* nacionalidad){
	int retorno = FALSE;
	if(this != NULL && nacionalidad != NULL){
		retorno = TRUE;
		strcpy(nacionalidad,this->nacionalidadArcade);
	}
	return retorno;
}

int arcade_setTipoDeSonidad(Arcade* this,int tipoDeSonidad){
	int retorno = FALSE;
	if(this != NULL && (tipoDeSonidad == 0 || tipoDeSonidad == 1)){
		retorno = TRUE;
		this->tipoDeSonidad = tipoDeSonidad;
	}
	return retorno;
}

int arcade_getTipoDeSonidad(Arcade* this,int* tipoDeSonidad){
	int retorno = FALSE;
	if(this != NULL && tipoDeSonidad != NULL){
		retorno = TRUE;
		*tipoDeSonidad = this->tipoDeSonidad;
	}
	return retorno;
}

int arcade_setCantidadDeJugadores(Arcade* this,int cantidadDeJugadores){
	int retorno = FALSE;
	if(this != NULL && cantidadDeJugadores > 0){
		retorno = TRUE;
		this->cantidadDeJugadores = cantidadDeJugadores;
	}
	return retorno;
}

int arcade_getCantidadDeJugadores(Arcade* this,int* cantidadDeJugadores){
	int retorno = FALSE;
	if(this != NULL && cantidadDeJugadores != NULL){
		retorno = TRUE;
		*cantidadDeJugadores = this->cantidadDeJugadores;
	}
	return retorno;
}

int arcade_setCapacidadMaximaDeFichas(Arcade* this,int capacidadMaximaDeFichas){
	int retorno = FALSE;
	if(this != NULL && capacidadMaximaDeFichas > 0){
		retorno = TRUE;
		this->capacidadMaximaDeFichas = capacidadMaximaDeFichas;
	}
	return retorno;
}

int arcade_getCapacidadMaximaDeFichas(Arcade* this,int* capacidadMaximaDeFichas){
	int retorno = FALSE;
	if(this != NULL && capacidadMaximaDeFichas != NULL){
		retorno = TRUE;
		*capacidadMaximaDeFichas = this->capacidadMaximaDeFichas;
	}
	return retorno;
}

int arcade_setNombreDelSalon(Arcade* this,char* nombreDelSalon){
	int retorno = FALSE;
	if(this != NULL && nombreDelSalon != NULL){
		retorno = TRUE;
		strcpy(this->nombreDelSalon,nombreDelSalon);
	}
	return retorno;
}

int arcade_getNombreDelSalon(Arcade* this,char* nombreDelSalon){
	int retorno = FALSE;
	if(this != NULL && nombreDelSalon != NULL){
		retorno = TRUE;
		strcpy(nombreDelSalon,this->nombreDelSalon);
	}
	return retorno;
}

int arcade_setNombreDelJuego(Arcade* this,char* nombreDelJuego){
	int retorno = FALSE;
	if(this != NULL && nombreDelJuego != NULL){
		retorno = TRUE;
		strcpy(this->nombreDelJuego,nombreDelJuego);
	}
	return retorno;
}

int arcade_getNombreDelJuego(Arcade* this,char* nombreDelJuego){
	int retorno = FALSE;
	if(this != NULL && nombreDelJuego != NULL){
		retorno = TRUE;
		strcpy(nombreDelJuego,this->nombreDelJuego);
	}
	return retorno;
}

int arcade_findById(LinkedList* pArrayListArcade,int id, int* pIndice){
	int retorno = FALSE;
	int tamanioLista;
	Arcade* pArcadeAuxiliar;
	if(pArrayListArcade != NULL && id >=0 && pIndice != NULL){
		tamanioLista = ll_len(pArrayListArcade);
		for(int i = 0;i < tamanioLista;i++){
			pArcadeAuxiliar = ll_get(pArrayListArcade,i);
			if(pArcadeAuxiliar->IDArcade == id){
				*pIndice = i;
				retorno = TRUE;
				break;
			}
		}
	}
	return retorno;
}


Arcade* arcade_newParametros(char* idStr,char* nacionalidadStr,char* tipoDeSonidadStr, char* cantidadDeJugadoresStr, char* capacidadMaximaDeFichasStr, char* nombreDelSalonStr,char* nombreDelJuegoStr){
	int auxID;
	int auxTipoDeSonidad;
	int auxCantidadDeJugadores;
	int auxCapacidadMaximaDeFichas;
	Arcade* retornoAuxArcade;
	if(idStr != NULL && nacionalidadStr != NULL && tipoDeSonidadStr != NULL && cantidadDeJugadoresStr != NULL && capacidadMaximaDeFichasStr != NULL && nombreDelSalonStr != NULL && nombreDelJuegoStr != NULL){
		if(UTN_validarNumeroEnteroIngresado(idStr) == TRUE &&
		   UTN_validarCadenaAlfabeticaIngresada(tipoDeSonidadStr) == TRUE &&
		   UTN_validarNumeroEnteroIngresado(cantidadDeJugadoresStr) == TRUE &&
		   UTN_validarNumeroEnteroIngresado(capacidadMaximaDeFichasStr) == TRUE &&
		   UTN_validarCadenaAlfanumericaIngresada(nombreDelSalonStr) == TRUE &&
		   UTN_validarCadenaAlfanumericaIngresada(nombreDelJuegoStr) == TRUE &&
		   UTN_validarCadenaAlfabeticaIngresada(nacionalidadStr) == TRUE){
				auxID = atoi(idStr);
				if((strcmp(tipoDeSonidadStr,"MONO") == 0)){
					auxTipoDeSonidad = MONO;
				}else{
					auxTipoDeSonidad = ESTEREO;
				}
				auxCantidadDeJugadores = atoi(cantidadDeJugadoresStr);
				auxCapacidadMaximaDeFichas = atoi(capacidadMaximaDeFichasStr);
				retornoAuxArcade = arcade_new();
				if(retornoAuxArcade != NULL){
					arcade_setID(retornoAuxArcade,auxID);
					arcade_setNacionalidad(retornoAuxArcade,nacionalidadStr);
					arcade_setTipoDeSonidad(retornoAuxArcade, auxTipoDeSonidad);
					arcade_setCantidadDeJugadores(retornoAuxArcade, auxCantidadDeJugadores);
					arcade_setCapacidadMaximaDeFichas(retornoAuxArcade, auxCapacidadMaximaDeFichas);
					arcade_setNombreDelSalon(retornoAuxArcade, nombreDelSalonStr);
					arcade_setNombreDelJuego(retornoAuxArcade, nombreDelJuegoStr);
				}
		}
	}
	return retornoAuxArcade;
}







