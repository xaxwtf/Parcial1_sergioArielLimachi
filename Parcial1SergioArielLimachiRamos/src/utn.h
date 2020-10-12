/*
 * utn.h
 *
 *  Created on: 7 sep. 2020
 *      Author: roid
 */

#ifndef UTN_H_
#define UTN_H_
int utn_getInt(char* msj, char* errormsj,int*numObtenido, int intentos, int max, int min);
int utn_getFloat(char* msj, char* errormsj,float*floatObtenido, int intentos, int max, int min);
int utn_getChar(char* msj, char* errormsj,char* caracterObt, int intentos);
int utn_array_calcular_max(int* array,int len,int* resultado);
int utn_array_calcular_min(int* array,int len,int* resultado);
int utn_array_calcular_prom(int* array,int len,float* resultado);
int utn_myGets(char* cadena, int len);
int utn_pedir_cadena(char* mensaje, char* cadena, int len);
int utn_soloLetras(char* vec);
int utn_esAlfanumerico(char *vec);
int utn_esCuit(char *vec);
int utn_pedirCadenadeUndeunDeterminadoTam(char* cadena,char* mensaje, int intentos, int tamMax, int tamMin);
void utn_cambiarCaracteresCuit(char* cuit);
void utn_cambiarLetrasString(char* algo ,int len);

#endif /* UTN_H_ */
