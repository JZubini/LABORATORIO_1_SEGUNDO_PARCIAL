#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Arcade.h"
#include "parser.h"
#include "UTN_Ingreso.h"
#include <string.h>
#include <conio.h>
#include "Juegos.h"

#define TRUE 1
#define FALSE 0
#define TAM 128
#define REINTENTOS 5
#define MONO 0
#define ESTEREO 1
#define MIN_MOD_MENU 1
#define MAX_MOD_MENU 3
#define MIN_ARCADES 1
#define MIN_MENU 1
#define MAX_MENU 9

int controller_saveArcadesAsText(char* path , LinkedList* pArrayListArcade);

									/*---------------------AUXILIARES---------------------*/

/** \brief La función se encarga de contar la cantidad de datos en los archivos para llevar un control de cual es la última ID registrada.
 *
 * \param pArrayListArcade lista de punteros
 * \return int Devuelve el contador de datos registrados en el archivo.
 *
 */

int controller_dataCount(LinkedList* pArrayListArcade){
	static int contador;
	FILE* file = fopen("arcades.csv","r");
	char id[TAM_DATOS];
	char nacionalidad[TAM_DATOS];
	char tipoDeSonidad[TAM_DATOS];
	char cantidadDeJugadores[TAM_DATOS];
	char capacidadMaximaDeFichas[TAM_DATOS];
	char nombreDelSalon[TAM_DATOS];
	char nombreDelJuego[TAM_DATOS];
	if(pArrayListArcade != NULL){
		fscanf(file,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,nacionalidad,tipoDeSonidad,cantidadDeJugadores,capacidadMaximaDeFichas,nombreDelSalon,nombreDelJuego);
		do{
			if(fscanf(file,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,nacionalidad,tipoDeSonidad,cantidadDeJugadores,capacidadMaximaDeFichas,nombreDelSalon,nombreDelJuego) == 7){
				contador++;
			}
		}while(feof(file) == 0);
	}
	return contador;
}

/** \brief La función se encarga de imprimir el arcade según el índice pasado por parámetro.
 *
 * \param pArrayListArcades lista de punteros
 * \param indice numero de indice al arcade que se desea imprimir
 * \return void
 *
 */

void controller_listArcadeByIndex(LinkedList* pArrayListArcades,int indice){
	Arcade* pAuxiliarArcades = ll_get(pArrayListArcades,indice);
	printf("-----------------------------------\n");
	printf("ID arcade: %d\n",pAuxiliarArcades->IDArcade);
	printf("Nacionalidad: %s\n",pAuxiliarArcades->nacionalidadArcade);
	if(pAuxiliarArcades->tipoDeSonidad == MONO){
		printf("Tipo de sonido: MONO\n");
	}else{
		printf("Tipo de sonido: ESTEREO\n");
	}
	printf("Cantidad de jugadores: %d\n",pAuxiliarArcades->cantidadDeJugadores);
	printf("Capacidad maxima de fichas: %d\n",pAuxiliarArcades->capacidadMaximaDeFichas);
	printf("Nombre salon: %s\n",pAuxiliarArcades->nombreDelSalon);
	printf("Nombre del juego: %s\n",pAuxiliarArcades->nombreDelJuego);
	puts("-----------------------------------\n");
}

								/*---------------------1---------------------*/

///** \brief Carga los datos de los arcades desde el archivo arcades.csv (modo texto).
// *
// * \param path nombre del archivo donde se guardaran los datos
// * \param pArrayListArcade lista de arcades
// * \return int
// *
// */
int controller_loadFromText(char* path , LinkedList* pArrayListArcade)
{
	int retorno = FALSE;
	if(path != NULL && pArrayListArcade != NULL){
		FILE* file = fopen(path,"r");
		if(file != NULL){
			parser_ArcadeFromText(file, pArrayListArcade);
			fclose(file);
			retorno = TRUE;
		}else{
			printf("ERROR, no se ha podido abrir el archivo %s\n",path);
		}
	}
	return retorno;
}

///** \brief Verifica si el nombre del juego pasado por parámetro ya se encuentra en la lista de juegos.
// *
// * \param pArrayListGame lista de punteros de juegos
// * \param nombreDelJuego dato nombre del juego
// * \return int (-1) En caso de algún nulo en los parámetros
//				 (FALSE | 0) En caso de que los parámetros sean correctos y el nombre no se encuentra en la lista
//				 (TRUE | 1) En caso de que el nombre del juego ya se encuentre en la lista.
// *
// */

int verificarNombreRepetido(LinkedList* pArrayListGame,char* nombreDelJuego){
	int retorno = -1;
	int tamanioLista = ll_len(pArrayListGame);
	Juego* pAuxJuego;
	if(pArrayListGame != NULL && nombreDelJuego != NULL){
		retorno = FALSE;
		for(int i = 0;i<tamanioLista;i++){
			pAuxJuego = ll_get(pArrayListGame,i);
			if(strcmp(pAuxJuego->nombreDelJuego,nombreDelJuego) == 0){
				retorno = TRUE;
				break;
			}
		}
	}
	return retorno;
}

///** \brief Carga todos los nombres de los juegos en la lista de juegos.
// *
// * \param pArrayListGame lista de punteros de juegos
// * \param pArrayListArcades lista de punteros de arcades
// * \return int (FALSE | 0) En caso de algún nulo en los parámetros
//				 (TRUE | 1) En caso de que logre guardar algún nombre.
// *
// */

int controller_loadGames(LinkedList* pArrayListGames,LinkedList* pArrayListArcades){
	int retorno = FALSE;
	int tamanioLista = ll_len(pArrayListArcades);
	static int banderaPrimerIngreso;
	Arcade* pArcadeAuxiliar;
	Juego* pJuegoAuxiliar;
	if(pArrayListGames != NULL && pArrayListArcades != NULL){
		for(int i = 0;i<tamanioLista;i++){
			if(banderaPrimerIngreso != FALSE){
				pArcadeAuxiliar = ll_get(pArrayListArcades,0);
				pJuegoAuxiliar = juegos_newParametros(pArcadeAuxiliar->nombreDelJuego);
				if(pJuegoAuxiliar != NULL){
					ll_add(pArrayListGames,pJuegoAuxiliar);
					retorno = TRUE;
					banderaPrimerIngreso = FALSE;
				}
			}else{
				pArcadeAuxiliar = ll_get(pArrayListArcades,i);
				if(verificarNombreRepetido(pArrayListGames, pArcadeAuxiliar->nombreDelJuego) == FALSE){
					pJuegoAuxiliar = juegos_newParametros(pArcadeAuxiliar->nombreDelJuego);
					if(pJuegoAuxiliar != NULL){
						ll_add(pArrayListGames,pJuegoAuxiliar);
						retorno = TRUE;
					}
				}
			}
		}
	}
	return retorno;
}

										/*---------------------2---------------------*/

///** \brief Alta de un arcade
// *
// * \param pArrayListGame lista de punteros de juegos
// * \param pArrayListArcades lista de punteros de arcades
// * \return int (FALSE | 0) En caso de algún nulo en los parámetros
//				 (TRUE | 1) En caso de que logre guardar los datos.
// *
// */

int controller_addArcade(char* path, LinkedList* pArrayListArcade,LinkedList* pArrayListGames)
{
	int retorno = FALSE;
	static int incrementador = 1;
	int auxiliarID;
	char nuevaID[TAM];
	char auxiliarNacionalidad[TAM];
	char auxTipoDeSonidad[TAM];
	char auxCantidadDeJugadores[TAM];
	char auxCapacidadMaximaDeFichas[TAM];
	char auxNombreDelSalon[TAM];
	char auxNombreDelJuego[TAM];
	int estadoIngresoNacionalidad;
	int estadoIngresoTipoDeSonidad;
	int estadoIngresoCantidadDeJugadores;
	int estadoIngresoCantidadMaximaDeFichas;
	int estadoIngresoNombreDelSalon;
	int estadoIngresoNombreDelJuego;
	Arcade* pArcadeAuxiliar;
	Juego* pJuegoAuxiliar;
	if(pArrayListArcade != NULL){
		auxiliarID = controller_dataCount(pArrayListArcade) + incrementador;
		incrementador++;
		sprintf(nuevaID,"%d",auxiliarID);
		printf("------------------------ ID: %d ------------------------\n" ,auxiliarID);
		estadoIngresoNacionalidad = UTN_ingresoTextoReintentos(auxiliarNacionalidad, TAM, "Ingrese la nacionalidad del arcade a continuacion: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS);
		estadoIngresoTipoDeSonidad = UTN_ingresoTextoReintentos(auxTipoDeSonidad,TAM, "Ingrese el tipo de sonidad (0 - MONO | 1 - ESTEREO): ","ERROR, el valor ingresado es incorrecto, reingrese: ",REINTENTOS);
		estadoIngresoCantidadDeJugadores = UTN_ingresoTextoReintentos(auxCantidadDeJugadores,TAM, "Ingrese la cantidad de jugadores: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS);
		estadoIngresoCantidadMaximaDeFichas = UTN_ingresoTextoReintentos(auxCapacidadMaximaDeFichas,TAM, "Ingrese la cantidad maxima de fichas: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS);
		estadoIngresoNombreDelSalon = UTN_ingresoTextoReintentos(auxNombreDelSalon,TAM, "Ingrese el nombre del salón al que pertenece: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS);
		estadoIngresoNombreDelJuego = UTN_ingresoTextoReintentos(auxNombreDelJuego,TAM, "Ingrese el nombre del juego que contiene: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS);
		if(estadoIngresoNacionalidad == TRUE && estadoIngresoTipoDeSonidad == TRUE && estadoIngresoCantidadDeJugadores == TRUE && estadoIngresoCantidadMaximaDeFichas == TRUE && estadoIngresoNombreDelSalon == TRUE && estadoIngresoNombreDelJuego == TRUE){
			pArcadeAuxiliar = arcade_newParametros(nuevaID, auxiliarNacionalidad, auxTipoDeSonidad, auxCantidadDeJugadores,auxCapacidadMaximaDeFichas,auxNombreDelSalon,auxNombreDelJuego);
			if(verificarNombreRepetido(pArrayListGames, auxNombreDelJuego) == FALSE){
				pJuegoAuxiliar = juegos_newParametros(auxNombreDelJuego);
				if(pJuegoAuxiliar != NULL){
					ll_add(pArrayListGames,pJuegoAuxiliar);
				}
			}
			if(pArcadeAuxiliar != NULL){
				ll_add(pArrayListArcade,pArcadeAuxiliar);
				retorno = TRUE;
				puts("¡Exito en la operacion!\n");
			}else{
				puts("Ha ocurrido un error inesperado en la carga de datos, vuelva al menú e intentelo nuevamente.\n");
			}
		}else{
			puts("Ha ocurrido un error inesperado en el ingreso de datos, vuelva al menú y cargue los datos nuevamente.");
		}
	}
	return retorno;
}

												/*---------------------3---------------------*/

///** \brief Lista los arcades cargados
// *
// * \param pArrayListArcades lista de punteros de arcades
// * \return int (FALSE | 0) En caso de algún nulo en los parámetros
//				 (TRUE | 1) En caso de que logre imprimir los datos.
// *
// */

int controller_ListArcades(LinkedList* pArrayListArcades)
{
	int retorno = FALSE;
	int tamanoLista;
	if(pArrayListArcades != NULL){
		tamanoLista = ll_len(pArrayListArcades);
		for(int i = 0;i<tamanoLista;i++){
			Arcade* pAuxiliarArcades = ll_get(pArrayListArcades,i);
			printf("-----------------------------------\n");
			printf("ID arcade: %d\n",pAuxiliarArcades->IDArcade);
			printf("Nacionalidad: %s\n",pAuxiliarArcades->nacionalidadArcade);
			if(pAuxiliarArcades->tipoDeSonidad == MONO){
				printf("Tipo de sonido: MONO\n");
			}else{
				printf("Tipo de sonido: ESTEREO\n");
			}
			printf("Cantidad de jugadores: %d\n",pAuxiliarArcades->cantidadDeJugadores);
			printf("Capacidad maxima de fichas: %d\n",pAuxiliarArcades->capacidadMaximaDeFichas);
			printf("Nombre salon: %s\n",pAuxiliarArcades->nombreDelSalon);
			printf("Nombre del juego: %s\n",pAuxiliarArcades->nombreDelJuego);
			puts("-----------------------------------\n");
			retorno = TRUE;
		}
	}
	return retorno;
}

///** \brief Edita el nombre del juego o la cantidad de jugadores.
// *
// * \param respuestaUsuario Contiene la respuesta del usuario sobre cúal de los dos datos desea modificar.
// * \param pElementMod puntero a elemento que contiene el dato a modificar.
// * \return int (FALSE | 0) En caso de algún nulo en los parámetros
//				 (TRUE | 1) En caso de que los parámetros sean correctos y logre modificar el dato.
// *
// */

int controller_editArcade(int respuestaUsuario,void* pElementMod){
	int auxCantidadDeJugadores;
	char auxNombreDelJuego[TAM];
	int estadoIngresoCantidadDeJugadores;
	int estadoIngresoNombreDelJuego;
	int retorno = FALSE;
	if(respuestaUsuario > 0 && pElementMod != NULL){
		switch(respuestaUsuario){
			case 1:
				estadoIngresoNombreDelJuego = UTN_ingresoTextoReintentos(auxNombreDelJuego, TAM, "Ingrese el nuevo nombre del juego: ", "El valor ingresado es incorrecto, reingrese: ", REINTENTOS);
				if(estadoIngresoNombreDelJuego == TRUE){
					arcade_setNombreDelJuego(pElementMod, auxNombreDelJuego);
					puts("¡Exito en la operación!\n");
					retorno = TRUE;
				}else{
					puts("Hubo un error inesperado en la modificación, vuelva al menu e intentelo nuevamente.\n");
				}
				break;
			case 2:
				estadoIngresoCantidadDeJugadores = UTN_ingresoIntReintentos(&auxCantidadDeJugadores, "Ingrese la nueva cantidad de jugadores: ", "El valor ingresado es incorrecto, reingrese: ",REINTENTOS);
				if(estadoIngresoCantidadDeJugadores == TRUE){
					arcade_setCantidadDeJugadores(pElementMod, auxCantidadDeJugadores);
					puts("¡Exito en la operación!\n");
					retorno = TRUE;
				}else{
					puts("Hubo un error inesperado en la modificación, vuelva al menu e intentelo nuevamente.\n");
				}
				break;
		}
	}
	return retorno;
}

/** \brief Menú para modificar dato del arcade.
 *
 * \param pArrayListArcade lista de arcades
 * \return int (FALSE | 0) En caso de algún nulo en los parámetros
			   (TRUE | 1) En caso de que los parámetros sean correctos y se logre ingresar correctamente.
 *
 */
int controller_modMenu(LinkedList* pArrayListArcade)
{
	int retorno = FALSE;
	int modID;
	int maximoArcadesCargados;
	int respuestaUsuario;
	int indiceMod;
	void* arcadeMod;
	if(pArrayListArcade != NULL){
		maximoArcadesCargados = controller_dataCount(pArrayListArcade);
		puts("--------------------- MENU DE MODIFICACIONES ---------------------\n");
		puts("Bienvenido al menu de modificaciones.\n");
		if(UTN_ingresoIntReintentosMinMax(&modID, "Ingrese la id del arcade a modificar:", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_ARCADES, maximoArcadesCargados, REINTENTOS) == TRUE){
			arcade_findById(pArrayListArcade, modID,&indiceMod);
			if(indiceMod != -1){
				arcadeMod = ll_get(pArrayListArcade,indiceMod);
				if(arcadeMod != NULL){
					do{
						printf("--------------------- ID seleccionada: %d ---------------------\n" ,modID);
						puts("Seleccione una de las siguientes opciones:\n");
						puts("\t1 - Modificar el nombre del juego");
						puts("\t2 - Modificar la cantidad maxima de fichas.");
						puts("\t3 - Salir del menu de modificaciones.");
						if(UTN_ingresoIntReintentosMinMax(&respuestaUsuario, "Ingrese su respuesta: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_MOD_MENU, MAX_MOD_MENU, REINTENTOS) == TRUE){
							controller_editArcade(respuestaUsuario,arcadeMod);
							retorno = TRUE;
						}else{
							puts("Demasiados intentos en el ingreso de opción, vuelva al menú e intentelo nuevamente\n");
						}
					}while(respuestaUsuario != 3);
				}
			}else{
				puts("No se ha podido encontrar la ID solicitada, vuelva al menú e intentelo nuevamente\n");
			}
		}else{
			puts("Ha ocurrido un error en el ingreso de ID, vuelva al menú e intentelo nuevamente\n");
		}
	}
    return retorno;
}

										/*---------------------4---------------------*/

/** \brief Guarda los arcades en el archivo.
 *
 * \param pArrayListArcade lista de arcades
 * \param path nombre del archivo donde se escribiran los datos.
 * \return int (FALSE | 0) En caso de algún nulo en los parámetros
			   (TRUE | 1) En caso de que los parámetros sean correctos y se logre guardar por lo menos un dato del tipo Arcade.
 *
 */

int controller_saveArcadesAsText(char* path , LinkedList* pArrayListArcade)
{
	  FILE* file = fopen(path,"w");
	  Arcade* pArcadeAuxiliar;
	  int tamanoLista;
	  int retorno = FALSE;
	  char auxTipoDeSonidad[TAM_DATOS];
	  if(path != NULL && pArrayListArcade != NULL){
		  if(file != NULL)
		  {
			  fprintf(file,"id,nacionalidad,tipo_sonido,cant_jug,fichas_max,salon,game\n");
			  tamanoLista = ll_len(pArrayListArcade);
			  for(int i=0; i<tamanoLista; i++)
			  {
				  pArcadeAuxiliar = ll_get(pArrayListArcade,i);
				  if(pArcadeAuxiliar->tipoDeSonidad == 0){
					  strcpy(auxTipoDeSonidad,"MONO");
				  }
				  if(pArcadeAuxiliar->tipoDeSonidad == 1){
				  	  strcpy(auxTipoDeSonidad,"STEREO");
				  }
				  if(fprintf(file,"%d,%s,%s,%d,%d,%s,%s\n",
						  pArcadeAuxiliar->IDArcade,
						  pArcadeAuxiliar->nacionalidadArcade,
						  auxTipoDeSonidad,
						  pArcadeAuxiliar->cantidadDeJugadores,
						  pArcadeAuxiliar->capacidadMaximaDeFichas,
						  pArcadeAuxiliar->nombreDelSalon,
						  pArcadeAuxiliar->nombreDelJuego) > 0){
					  retorno = TRUE;
				  }
			  }
			  fclose(file);
		  }
	  }
    return retorno;
}

///** \brief Baja de arcade
// *
// * \param path nombre del archivo donde se escribiran los datos.
// * \param pArrayListArcade lista de arcades
// * \return int (FALSE | 0) En caso de algún nulo en los parámetros
// *			 (TRUE | 1) En caso de que los parámetros sean correctos y, se logre remover el arcade y guardarlo en su archivo.
// */
int controller_removeArcade(LinkedList* pArrayListArcade,char* path)
{
	int retorno = FALSE;
	int bajaID;
	int maximoArcadesCargados;
	int indiceBaja;
	int respuestaUsuario;
	maximoArcadesCargados = controller_dataCount(pArrayListArcade);
	if(pArrayListArcade != NULL){
		if(UTN_ingresoIntReintentosMinMax(&bajaID, "Ingrese la ID del arcade del que desea dar de baja:", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_ARCADES, maximoArcadesCargados, REINTENTOS) == TRUE){
			arcade_findById(pArrayListArcade, bajaID,&indiceBaja);
			if(indiceBaja > -1){
				controller_listArcadeByIndex(pArrayListArcade, indiceBaja);
				if(UTN_ingresoIntReintentosMinMax(&respuestaUsuario, "¿Esta seguro de eliminar este arcade? (1 - SI | 2 - NO): ", "ERROR, el valor ingresado es incorrecto, reingrese: ", 1, 2, REINTENTOS) == TRUE){
					if(respuestaUsuario == 1){
						ll_remove(pArrayListArcade,indiceBaja);
						controller_saveArcadesAsText(path, pArrayListArcade);
						puts("¡Exito en la operacion!\n");
						retorno = TRUE;
					}else{
						puts("Operacion cancelada.");
					}
				}else{
					puts("Error en el ingreso de su respuesta, la operación se ha cancelado. Vuelva al menú e intentelo nuevamente");
				}
			}else{
				puts("No se ha podido encontrar el arcade con la ID solicitada, vuelva al menú e intentelo nuevamente.\n");
			}
		}else{
			puts("Demasiados intentos fallidos en el ingreso del ID, vuelva al menú e intentelo nuevamente");
		}
	}
    return retorno;
}


											/*---------------------5---------------------*/

///** \brief Compara dos nombres.
// *
// * \param pAuxArcadeUno puntero al primer elemento que se desea comparar
// * \param pAuxArcadeDos puntero al segundo elemento que se desea comparar de arcades
// * \return int (1) En caso de que el primer símbolo no igual del primer elemento sea más chico que el del segundo elemento.
// *			 (-1) En caso de que el primer símbolo no igual del primer elemento sea más grande que el del segundo elemento.
// */

int compararNombres(Arcade* pAuxArcadeUno, Arcade* pAuxArcadeDos){
	int retorno;
	if(strcmp(pAuxArcadeUno->nombreDelJuego,pAuxArcadeDos->nombreDelJuego) == 1){
		retorno = 1;
	}
	if(strcmp(pAuxArcadeUno->nombreDelJuego,pAuxArcadeDos->nombreDelJuego) == -1){
		retorno = -1;
	}
	return retorno;
}


///** \brief Ordena los arcades por nombre de juego
// *
// * \param pArrayListArcade lista de arcades
// * \return (FALSE) En caso de que haya un nulo en el parámetro.
// *		 (TRUE) En caso de que se ingrese correctamente la respuesta del usuario y se logre ordenar los arcades.
// */
//
int controller_sortArcadesByGame(LinkedList* pArrayListArcade)
{
	int retorno = FALSE;
	void* pCriterio = compararNombres;
	int respuestaUsuario;
	if(UTN_ingresoIntReintentosMinMax(&respuestaUsuario, "¿En que orden desea ordenar los arcades? (1 - Descendente | 0 - Ascendente)","ERROR, el valor ingresado es incorrecto, reingrese: ", 0, 1, REINTENTOS) == TRUE){
		ll_sort(pArrayListArcade,pCriterio,respuestaUsuario);
		retorno = TRUE;
	}else{
		puts("Demasiados intentos fallidos en el ingreso, vuelva al menu e intentelo nuevamente.");
	}
    return retorno;
}

											/*---------------------6---------------------*/

///** \brief Guarda los juegos en el archivo.
// *
// * \param pArrayListGames lista de juegos
// * \param path Nombre del archivo donde se guardaran los datos
// * \return (FALSE) En caso de que haya un nulo en alguno de los parámetros.
// *		 (TRUE) En caso de que los parámetros seán correctos y logre por lo menos guardar un nombre.
// */
//

int controller_saveGamesAsText(char* path , LinkedList* pArrayListGames)
{
	  FILE* file = fopen(path,"w");
	  int tamanioLista;
	  int retorno = FALSE;
	  Juego* pJuegoAuxiliar;
	  if(path != NULL && pArrayListGames != NULL){
		  if(file != NULL)
		  {
			  fprintf(file,"Nombre del juego\n");
			  tamanioLista = ll_len(pArrayListGames);
			  for(int i=0; i<tamanioLista; i++)
			  {
				  pJuegoAuxiliar = ll_get(pArrayListGames,i);
			  	  if(fprintf(file,"%s\n",pJuegoAuxiliar->nombreDelJuego) > 0){
			  		 retorno = TRUE;
			  	  }
			  }
			 fclose(file);
		  }
	  }
    return retorno;
}

										/*---------------------7---------------------*/

///** \brief Verifica si el arcade es multijugador.
// *
// * \param pElemento puntero al elemento que se desea verificar
// * \return (FALSE) En caso de que haya un nulo en el parámetro o en caso de que el arcade no sea multijugador.
// *		 (TRUE) En caso de que el arcade sea multijugador.
// */
//

int controller_verificarArcadesMultiplayer(Arcade* pElemento){
	int retorno = FALSE;
	if(pElemento != NULL){
		if(pElemento->cantidadDeJugadores > 1){
			retorno = TRUE;
		}
	}
	return retorno;
}

///** \brief Guarda los arcades multiplayer en el archivo.
// *
// * \param path nombre del archivo donde se guardarán los datos.
// * \param pArrayListArcade lista de arcades
// * \return (FALSE) En caso de que haya un nulo en el parámetro.
// *		 (TRUE) En caso de que por lo menos se haya guardado un dato del tipo Arcade.
// */
//

int controller_saveMultiplayerArcadesAsText(char* path , LinkedList* pArrayListArcade){
	int retorno = FALSE;
	FILE* file = fopen(path,"w");
	Arcade* pArcadeAuxiliar;
	int tamanioLista;
	char auxTipoDeSonidad[TAM_DATOS];
	if(path != NULL && pArrayListArcade != NULL){
		void* criterio = controller_verificarArcadesMultiplayer;
		LinkedList* listaFiltrada = ll_filter(pArrayListArcade,criterio);
		tamanioLista = ll_len(listaFiltrada);
		fprintf(file,"Arcades multiplayer\n");
		fprintf(file,"id,nacionalidad,tipo_sonido,cant_jug,fichas_max,salon,game\n");
		for(int i = 0;i<tamanioLista;i++){
			pArcadeAuxiliar = ll_get(listaFiltrada,i);
			if(pArcadeAuxiliar->tipoDeSonidad == 0){
				 strcpy(auxTipoDeSonidad,"MONO");
			}
			if(pArcadeAuxiliar->tipoDeSonidad == 1){
				strcpy(auxTipoDeSonidad,"STEREO");
			 }
			if(fprintf(file,"%d,%s,%s,%d,%d,%s,%s\n",
				 pArcadeAuxiliar->IDArcade,
				 pArcadeAuxiliar->nacionalidadArcade,
				 auxTipoDeSonidad,
				 pArcadeAuxiliar->cantidadDeJugadores,
				 pArcadeAuxiliar->capacidadMaximaDeFichas,
				 pArcadeAuxiliar->nombreDelSalon,
				 pArcadeAuxiliar->nombreDelJuego) > 0){
				 retorno = TRUE;
			}
		}
		fclose(file);
	}
	return retorno;
}

											/*---------------------8---------------------*/

///** \brief Dobla el valor de "capacidadMaximaDeFichas" mediante el elemento
// * \param pElement puntero al elemento donde vamos a modificar el dato.
// * \return (FALSE) En caso de que haya un nulo en el parámetro.
// *		 (TRUE) En caso de que los parámetros sean correctos.
// */
//

int doblarCantidadDeFichasMaximas(Arcade* pElement){
	int retorno = FALSE;
	if(pElement != NULL){
		pElement->capacidadMaximaDeFichas *= 2;
	}
	return retorno;
}

											/*---------------------MENÚ---------------------*/

void mainMenu(void){
	LinkedList* listaArcades = ll_newLinkedList();
	LinkedList* listaJuegos = ll_newLinkedList();
	int respuestaUsuario;
	int banderaCargaDatosTexto = FALSE;
	void* criterio;
	do{
		puts("----------------------------------------------------------------------------------\n");
		printf("Bienvenido al menú, seleccione una de las siguientes opciones:\n");
		puts("\t1 - Cargar los datos de los arcade desde el archivo arcades.csv (modo texto).");
		puts("\t2 - Alta de arcade.");
		puts("\t3 - Modificar arcade");
		puts("\t4 - Baja de arcade");
		puts("\t5 - Imprimir arcades ordenados por nombre de juego");
		puts("\t6 - Generar archivo con JUEGOS");
		puts("\t7 - Generar un archivo con arcades Multijugador");
		puts("\t8 - Actualizar cantidad de fichas");
		puts("\t9 - Salir del programa");
			UTN_ingresoIntReintentosMinMax(&respuestaUsuario,"Ingrese una opción del menu: ","ERROR, el valor ingresado es incorrecto, reingrese: ",MIN_MENU,MAX_MENU,REINTENTOS);
			switch(respuestaUsuario) {
				case 1:
					if(controller_loadFromText("arcades.csv", listaArcades) == TRUE){
						controller_loadGames(listaJuegos, listaArcades);
						puts("¡Exito en la operacion!");
						banderaCargaDatosTexto = TRUE;
					}
					break;
				case 2:
					if(banderaCargaDatosTexto == TRUE){
						controller_addArcade("arcades.csv",listaArcades,listaJuegos);
						controller_saveArcadesAsText("arcades.csv", listaArcades);
					}
					break;
				case 3:
					if(banderaCargaDatosTexto == TRUE){
						controller_ListArcades(listaArcades);
						controller_modMenu(listaArcades);
						controller_saveArcadesAsText("arcades.csv", listaArcades);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;

				case 4:
					if(banderaCargaDatosTexto == TRUE){
						controller_ListArcades(listaArcades);
						controller_removeArcade(listaArcades,"arcades.csv");
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;

				case 5:
					if(banderaCargaDatosTexto == TRUE){
						controller_sortArcadesByGame(listaArcades);
						controller_ListArcades(listaArcades);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;

				case 6:
					if(banderaCargaDatosTexto == TRUE){
						controller_saveGamesAsText("Juegos.txt",listaJuegos);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 7:
					controller_saveMultiplayerArcadesAsText("multijugador.csv",listaArcades);
					break;
				case 8:
					if(banderaCargaDatosTexto == TRUE){
						criterio = doblarCantidadDeFichasMaximas;
						ll_map(listaArcades,criterio);
					}else{
						puts("Todavía no se ha realizado la carga de datos por archivo, vuelva al menu");
					}
					break;
				case 9:
					puts("Fin del programa.");
					break;
			}
	} while (respuestaUsuario != 9);
}




