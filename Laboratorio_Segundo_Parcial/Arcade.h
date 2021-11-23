/*
 * Arcade.h
 *
 *  Created on: 16 oct. 2021
 *      Author: Julián Zubini
 */

#ifndef ARCADE_H_
#define ARCADE_H_

#include "LinkedList.h"

#define TAM_DATOS 256

typedef struct{
	int IDArcade;
	char nacionalidadArcade[TAM_DATOS];
	int tipoDeSonidad;
	int cantidadDeJugadores;
	int capacidadMaximaDeFichas;
	char nombreDelSalon[TAM_DATOS];
	char nombreDelJuego[TAM_DATOS];
}Arcade;

Arcade* arcade_new();
void arcade_delete(Arcade* this);
Arcade* arcade_newParametros(char* idStr,char* nacionalidadStr,char* tipoDeSonidadStr, char* cantidadDeJugadoresStr, char* capacidadMaximaDeJugadoresStr, char* nombreDelSalonStr,char* nombreDelJuegoStr);

int arcade_setID(Arcade* this,int id);
int arcade_getID(Arcade* this,int* id);

int arcade_setNacionalidad(Arcade* this,char* nacionalidad);
int arcade_getNacionalidad(Arcade* this,char* nacionalidad);

int arcade_setTipoDeSonidad(Arcade* this,int tipoDeSonidad);
int arcade_getTipoDeSonidad(Arcade* this,int* tipoDeSonidad);

int arcade_setCantidadDeJugadores(Arcade* this,int cantidadDeJugadores);
int arcade_getCantidadDeJugadores(Arcade* this,int* cantidadDeJugadores);

int arcade_setCapacidadMaximaDeFichas(Arcade* this,int capacidadMaximaDeFichas);
int arcade_getCapacidadMaximaDeFichas(Arcade* this,int* capacidadMaximaDeFichas);

int arcade_setNombreDelSalon(Arcade* this,char* nombreDelSalon);
int arcade_getNombreDelSalon(Arcade* this,char* nombreDelSalon);

int arcade_setNombreDelJuego(Arcade* this,char* nombreDelJuego);
int arcade_getNombreDelJuego(Arcade* this,char* nombreDelJuego);

int arcade_findById(LinkedList* pArrayListArcade,int id, int* pIndice);


#endif /* ARCADE_H_ */
