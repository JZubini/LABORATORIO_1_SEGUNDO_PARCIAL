/*
 * UTN_Ingreso.c
 *
 *  Created on: 6 oct. 2021
 *      Author: Julián Zubini
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "UTN_Ingreso.h"
#define VERDADERO 1
#define FALSO 0
#define TAM_BUFFER 1000

int myGets(char* pIngreso, int len)
{
	int retorno= FALSO;
	int indexFinal;
	//gets(pResultado); // NOOOOOOO
	//if(scanf("%s", pResultado)==1) // NOOOOOOO
	if(fgets(pIngreso,len,stdin)!=NULL)
	{
		// borro el \n del final
		indexFinal = strlen(pIngreso)-1;
		if(pIngreso[indexFinal] == '\n')
		{
			pIngreso[indexFinal] = '\0';
		}
		retorno = VERDADERO;
	}
	return retorno;
}

// VALIDACIONES

int UTN_validarNumeroEnteroIngresado(char* pIngreso){
	int retorno = VERDADERO;
	if(strlen(pIngreso) > 0){
		for(int i = 0;i< strlen(pIngreso);i++){
			if(isdigit(pIngreso[i]) == FALSO){
				if(i == 0){
					if(pIngreso[0] != '-'){
						retorno = FALSO;
						break;
					}
				}else{
					retorno = 0;
				}
			}
		}
	}else{
		retorno = FALSO;
	}
	return retorno;
}

int UTN_validarNumeroFlotanteIngresado(char* pIngreso){
	int contadorDeSignos = 0;
	int retorno = VERDADERO;
	if(strlen(pIngreso) > 0){
		for(int i = 0;i < strlen(pIngreso); i++){
			if(pIngreso[i] == '.' || pIngreso[i] == ','){
				contadorDeSignos++;
			}else{
				if(isdigit(pIngreso[i]) == 0){
					if(i == 0){
						if(pIngreso[0] != '-'){
							retorno = FALSO;
							break;
						}
					}else{
						retorno = FALSO;
						break;
					}
				}
			}
		}
		if(contadorDeSignos > 1){
			retorno = FALSO;
		}
	}else{
		retorno = FALSO;
	}
	return retorno;
}

int UTN_validarCaracterIngresado(char ingreso){
	int retorno = VERDADERO;
	if(isalpha(ingreso) == FALSO){
		retorno = FALSO;
	}
	return retorno;
}

int UTN_validarCadenaAlfabeticaIngresada(char ingreso[]){
	int retorno = VERDADERO;
	if(strlen(ingreso) > 0){
		for(int i = 0;i<strlen(ingreso);i++){
			if(isalpha(ingreso[i] == 0)){
				retorno = FALSO;
				break;
			}
		}
	}else{
		retorno = FALSO;
	}
	return retorno;
}

int UTN_validarCadenaAlfanumericaIngresada(char ingreso[]){
	int retorno = VERDADERO;
	if(strlen(ingreso) > 0){
		for(int i = 0;i<strlen(ingreso);i++){
			if(isalpha(ingreso[i] == 0) || isdigit(ingreso[i] == 0)){
				retorno = FALSO;
				break;
			}
		}
	}
	return retorno;
}

// FIN VALIDACIONES

// INGRESOS INT

int UTN_ingresoInt(char* variableTexto, char* textoError)
{
	char buffer[TAM_BUFFER];
	int retorno;
	if(variableTexto != NULL && textoError != NULL)
	{
		printf("%s",variableTexto);
		fflush(stdin);
		gets(buffer);
		while(UTN_validarNumeroEnteroIngresado(buffer) == FALSO){
			printf("%s",textoError);
			fflush(stdin);
			gets(buffer);
		}
		retorno = atoi(buffer);
	}
	return retorno;
}

int UTN_ingresoIntReintentos(int* pIngreso, char* variableTexto, char* textoError, int reintentos)
{
	char buffer[TAM_BUFFER];
	int retorno = FALSO;
	if(pIngreso != NULL && variableTexto != NULL && textoError != NULL && reintentos > 0)
	{
		printf("%s",variableTexto);
		fflush(stdin);
		gets(buffer);
		while(UTN_validarNumeroEnteroIngresado(buffer) == FALSO){
			if(reintentos == 0){
				printf("Demasiados intentos fallidos, reinicie el programa.");
				retorno = FALSO;
				break;
			}
			printf("%s",textoError);
			fflush(stdin);
			gets(buffer);
			reintentos--;

		}
		*pIngreso = atoi(buffer);
		retorno = VERDADERO;
	}
	return retorno;
}

int UTN_ingresoIntReintentosMinMax(int* pIngreso, char* variableTexto, char* textoError, int min, int max, int reintentos)
{
	char buffer[TAM_BUFFER];
	int retorno = FALSO;
	if(pIngreso != NULL && variableTexto != NULL && textoError != NULL && reintentos > 0 && min < max)
	{
		printf("%s",variableTexto);
		fflush(stdin);
		gets(buffer);
		while(UTN_validarNumeroEnteroIngresado(buffer) == FALSO || atoi(buffer) > max || atoi(buffer) < min){
			if(reintentos == 0){
				printf("Demasiados intentos fallidos");
				retorno = FALSO;
				break;
			}
			printf("%s",textoError);
			fflush(stdin);
			gets(buffer);
			reintentos--;
		}
		*pIngreso = atoi(buffer);
		retorno = VERDADERO;
	}
	return retorno;
}

// FIN INGRESOS INT

// INGRESOS FLOAT

float UTN_ingresoFloat(char* variableTexto, char* textoError){
	char buffer[TAM_BUFFER];
	float retorno;
	if(variableTexto != NULL && textoError != NULL){
			printf("%s",variableTexto);
			fflush(stdin);
			gets(buffer);
			while(UTN_validarNumeroFlotanteIngresado(buffer) == FALSO){
				printf("%s",textoError);
				fflush(stdin);
				gets(buffer);
			}
		retorno = atof(buffer);
	}
	return retorno;
}

float UTN_ingresoFloatReintentos(float* pIngreso, char* variableTexto, char* textoError, int reintentos){
	char buffer[TAM_BUFFER];
	int retorno = FALSO;
	if(pIngreso != NULL && variableTexto != NULL && textoError != NULL && reintentos > 0)
	{
		printf("%s",variableTexto);
		fflush(stdin);
		gets(buffer);
		while(UTN_validarNumeroFlotanteIngresado(buffer) == FALSO){
			if(reintentos == 0){
				printf("Demasiados intentos fallidos, reinicie el programa.");
				retorno = FALSO;
				break;
			}
			printf("%s",textoError);
			fflush(stdin);
			gets(buffer);
			reintentos--;
		}
		*pIngreso = atof(buffer);
		retorno = VERDADERO;
	}
	return retorno;
}

float UTN_ingresoFloatReintentosMinMax(float* pIngreso, char* variableTexto, char* textoError, float min, float max, int reintentos){
	char buffer[TAM_BUFFER];
	int retorno = FALSO;
	if(pIngreso != NULL && variableTexto != NULL && textoError != NULL && reintentos > 0 && min < max)
	{
		printf("%s",variableTexto);
		fflush(stdin);
		gets(buffer);
		while(UTN_validarNumeroFlotanteIngresado(buffer) == FALSO || atof(buffer) > max || atof(buffer) < min){
			if(reintentos == 0){
				printf("Demasiados intentos fallidos, reinicie el programa.");
				retorno = FALSO;
				break;
			}
			printf("%s",textoError);
			fflush(stdin);
			gets(buffer);
			reintentos--;
		}
		*pIngreso = atof(buffer);
		retorno = VERDADERO;
	}
	return retorno;
}

// FIN INGRESOS FLOAT

// INICIO INGRESO CHAR

char UTN_ingresoChar(char* variableTexto, char* textoError){
	char buffer;
	char retorno;
	if(variableTexto != NULL && textoError != NULL){
		printf("%s",variableTexto);
		fflush(stdin);
		buffer = getchar();
		while(UTN_validarCaracterIngresado(buffer) == FALSO){
			printf("%s",textoError);
			fflush(stdin);
			buffer = getchar();
		}
		retorno = buffer;
	}
	return retorno;
}

char UTN_ingresoCharReintentos(char* pIngreso,char* variableTexto, char* textoError,int reintentos){
	char buffer;
	char retorno = VERDADERO;
	if(variableTexto != NULL && textoError != NULL && reintentos > 0){
		printf("%s",variableTexto);
		fflush(stdin);
		buffer = getchar();
		while(UTN_validarCaracterIngresado(buffer) == FALSO){
			if(reintentos == 0){
				printf("Demasiados intentos fallidos, reinicie el programa.");
				retorno = FALSO;
				break;
			}
			printf("%s",textoError);
			fflush(stdin);
			buffer = getchar();
			reintentos--;
		}
		*pIngreso = buffer;
	}
	return retorno;
}

char UTN_ingresoCharReintentosMinMax(char* pIngreso,char* variableTexto, char* textoError, char min, char max, int reintentos){
	char buffer;
	char retorno = VERDADERO;
	if(variableTexto != NULL && textoError != NULL && reintentos > 0 && min < max){
		printf("%s",variableTexto);
		fflush(stdin);
		buffer = getchar();
		while(UTN_validarCaracterIngresado(buffer) == FALSO || buffer > max || buffer < min){
			if(reintentos == 0){
				printf("Demasiados intentos fallidos, reinicie el programa.");
				retorno = FALSO;
				break;
			}
			printf("%s",textoError);
			fflush(stdin);
			buffer = getchar();
			reintentos--;
		}
		*pIngreso = buffer;
	}
	return retorno;
}

int UTN_ingresoTextoReintentos(char pIngreso[],int tam, char* variableTexto, char* textoError, int reintentos){
	int retorno = VERDADERO;
	if(variableTexto != NULL && textoError != NULL){
		printf("%s",variableTexto);
		fflush(stdin);
		while(myGets(pIngreso,tam) == FALSO){
			if(reintentos == 0){
				retorno = FALSO;
				break;
			}
			printf("%s", textoError);
			printf("%s",variableTexto);
			fflush(stdin);
			reintentos--;
		}
	}
	return retorno;
}


