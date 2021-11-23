#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Arcade.h"
#include "parser.h"
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MONO 0
#define ESTEREO 1

/** \brief Parsea los datos los datos de los empleados desde el archivo arcades.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListArcade LinkedList*
 * \return int
 *
 */
int parser_ArcadeFromText(FILE* pFile , LinkedList* pArrayListArcade){

	int retorno = FALSE;
	if(pFile != NULL && pArrayListArcade != NULL){
		char id[TAM_DATOS];
		char nacionalidad[TAM_DATOS];
		char tipoDeSonidad[TAM_DATOS];
		char cantidadDeJugadores[TAM_DATOS];
		char capacidadMaximaDeFichas[TAM_DATOS];
		char nombreDelSalon[TAM_DATOS];
		char nombreDelJuego[TAM_DATOS];
		if(pFile!=NULL){
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,nacionalidad,tipoDeSonidad,cantidadDeJugadores,capacidadMaximaDeFichas,nombreDelSalon,nombreDelJuego);
			do{
				if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,nacionalidad,tipoDeSonidad,cantidadDeJugadores,capacidadMaximaDeFichas,nombreDelSalon,nombreDelJuego) == 7){
					Arcade* pArcadeAuxiliar = arcade_newParametros(id,nacionalidad,tipoDeSonidad,cantidadDeJugadores,capacidadMaximaDeFichas,nombreDelSalon,nombreDelJuego);
					if(pArcadeAuxiliar != NULL){
						ll_add(pArrayListArcade,pArcadeAuxiliar);
						retorno = TRUE;
					}else{
						arcade_delete(pArcadeAuxiliar);
					}
				}
			}while(feof(pFile) == 0);
		}
	}
    return retorno;
}


