/*
 * UTN_Ingreso.h
 *
 *  Created on: 6 oct. 2021
 *      Author: Julián Zubini
 */


int UTN_validarNumeroEnteroIngresado(char *pIngreso);
int UTN_validarNumeroFlotanteIngresado(char *pIngreso);
int UTN_validadCaracterIngresado(char ingreso);
int UTN_validarCadenaAlfabeticaIngresada(char *pIngreso);
int UTN_validarCadenaAlfanumericaIngresada(char ingreso[]);

int UTN_ingresoInt(char* variableTexto, char* textoError);
float UTN_ingresoFloat(char* variableTexto, char* textoError);
char UTN_ingresoChar(char* variableTexto, char* textoError);
int UTN_ingresoTextoReintentos(char pIngreso[],int tam, char* variableTexto, char* textoError, int reintentos);


int UTN_ingresoIntReintentos(int* pIngreso, char* variableTexto, char* textoError, int reintentos);
float UTN_ingresoFloatReintentos(float* pIngreso, char* variableTexto, char* textoError, int reintentos);
char UTN_ingresoCharReintentos(char* pIngreso, char* variableTexto, char* textoError,int reintentos);


int UTN_ingresoIntReintentosMinMax(int* pIngreso, char* variableTexto, char* textoError, int min, int max, int reintentos);
float UTN_ingresoFloatReintentosMinMax(float* pIngreso, char* variableTexto, char* textoError, float min, float max,int reintentos);
char UTN_ingresoCharReintentosMinMax(char* pIngreso,char* variableTexto, char* textoError, char min, char max, int reintentos);
