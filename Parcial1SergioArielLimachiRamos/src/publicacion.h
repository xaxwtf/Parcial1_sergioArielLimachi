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

int publicacion_init(sPublicacion* lista[], int len);
int publicacion_listar(sPublicacion* lista[], int len);
int publicacion_generarId(void);
int publicacion_buscarOcurrenciaId(sPublicacion* lista[], int len, int id, int* indice);
int publicacion_ordenarxNombre(sPublicacion* lista, int len, int order);
int publicacion_add(sPublicacion* lista[],int len, sPublicacion* publicacion);
int publicacion_remove(sPublicacion* list[], int len, int id);
int publicacion_buscarLibreUocupado(sPublicacion * lista[], int len, int estado);
int publicacion_buscarLibreUocupadov2(sPublicacion * lista[], int len, int estado, int* indice);
int publicacion_buscarOcurrenciaIdv2(sPublicacion* lista[], int len, int id);
int publicacion_imprimirUno(sPublicacion* publicacion);
int publicacion_listarxCliente(sPublicacion* lista[], int len, int idCte);
int publicacion_removertodaslasPublicacionesdeUnCliente(sPublicacion* lista[], int len, int idCte);
int publicacion_contarCantidadAvisosPausadosuActivoxCliente(sPublicacion* lista[], int len, int idCte,int estadoAbuscar);
int publicacion_pausar(sPublicacion* lista[],int len);
int publicacion_reanudar(sPublicacion* lista[],int len);
int publicacion_contarActivasOpausadas(sPublicacion* lista[], int len, int estado);
int publicacion_contarRubroConMasAvisos(sPublicacion* lista[], int len, int rubro);
void publicacion_forzarPublicacion(sPublicacion* lista[], int len);
int ordenarx2criterios(sPublicacion* list, int len, int order);
sPublicacion* publicacion_new(int id, int idCte, char* txtAviso, int rubro, int estado);
int publicacion_set_id(sPublicacion* elemento, int id);
int publicacion_set_idCliente(sPublicacion* elemento, int idCliente);
int publicacion_set_numRubro(sPublicacion* elemento, int numRubro);
int publicacion_set_textodeAviso(sPublicacion* elemento, char* textodeAviso);
int publicacion_set_estado(sPublicacion* elemento, int estado);
int publicacion_get_id(sPublicacion* elemento);
int publicacion_get_idCte(sPublicacion* elemento);
int publicacion_get_textodeAviso(sPublicacion* elemento,char* textodeAviso);
int publicacion_get_numRubro(sPublicacion* elemento);
int publicacion_get_estado(sPublicacion* elemento);
int publicacion_delete(sPublicacion* elemento);

#endif /* PUBLICACION_H_ */
