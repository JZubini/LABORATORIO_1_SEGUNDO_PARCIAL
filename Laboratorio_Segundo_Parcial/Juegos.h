/*
 * Juegos.h
 *
 *  Created on: 17 oct. 2021
 *      Author: Julián Zubini
 */

#ifndef JUEGOS_H_
#define JUEGOS_H_

#define TAM_NOMBRE_JUEGO 256

typedef struct{
	char nombreDelJuego[TAM_NOMBRE_JUEGO];
}Juego;

Juego* juegos_new();
void juegos_delete(Juego* this);
Juego* juegos_newParametros(char* nombreDelJuego);

int juegos_setNombreDelJuego(Juego* this,char* nombreDelJuego);
int juegos_getNombreDelJuego(Juego* this,char* nombreDelJuego);

#endif /* JUEGOS_H_ */
