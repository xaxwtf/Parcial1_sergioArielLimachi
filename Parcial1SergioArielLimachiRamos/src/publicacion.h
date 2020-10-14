/*
 * publicacion.h
 *
 *  Created on: 10 oct. 2020
 *      Author: roid
 */

#ifndef PUBLICACION_H_
#define PUBLICACION_H_
#include "cliente.h"

typedef struct{
	int id;
	int isEmpty;
	int idCliente;
	char textodeAviso[63];
	int numRubro;
	int estado;
}sPublicacion;

int publicacion_init(sPublicacion* lista, int len);
int publicacion_listar(sPublicacion* lista, int len);
int publicacion_generarId(void);
int publicacion_buscarOcurrenciaId(sPublicacion* lista, int len, int id, int* indice);
int publicacion_ordenarxNombre(sPublicacion* lista, int len, int order);
int publicacion_add(sPublicacion* list, int len, int id, int idCliente, int rubro,char* texto);
int publicacion_remove(sPublicacion* list, int len, int id);
int publicacion_buscarLibreUocupado(sPublicacion * lista, int len, int estado);
int publicacion_buscarLibreUocupadov2(sPublicacion * lista, int len, int estado, int* indice);
int publicacion_buscarOcurrenciaIdv2(sPublicacion* lista, int len, int id);
int publicacion_imprimirUno(sPublicacion* publicacion);
int publicacion_listarxCliente(sPublicacion* lista, int len, int idCte);
int publicacion_removertodaslasPublicacionesdeUnCliente(sPublicacion* lista, int len, int idCte);
int publicacion_contarCantidadAvisosxCliente(sPublicacion* lista, int len, int idCte);
int publicacion_pausar(sPublicacion* lista,int len);
int publicacion_reanudar(sPublicacion* lista,int len);
int publicacion_contarActivasOpausadas(sPublicacion* lista, int len, int estado);
int publicacion_contarRubroConMasAvisos(sPublicacion* lista, int len, int rubro);
void publicacion_forzarPublicacion(sPublicacion* lista, int len);

#endif /* PUBLICACION_H_ */
