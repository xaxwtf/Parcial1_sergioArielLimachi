/*
 * cliente.h
 *
 *  Created on: 10 oct. 2020
 *      Author: roid
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#include "publicacion.h"

typedef struct{
	int id;
	int isEmpty;
	char name[50];
	char lastName[50];
	char cuit[15];
}sCliente;

int cliente_init(sCliente* lista, int len);
int cliente_alta(sCliente* lista, int len);
int cliente_modificar(sCliente* lista,int len);
int cliente_generarId(void);
int cliente_buscarOcurrenciaId(sCliente* lista, int len, int id, int* indice);
int cliente_ordenarxNombre(sCliente* lista, int len, int order);
int cliente_add(sCliente* list, int len, int id,char* name,char* lastName, char* cuit);
int cliente_remove(sCliente* list, int len, int id);
int cliente_buscarLibreUocupado(sCliente * lista, int len, int estado);
int cliente_buscarLibreUocupadov2(sCliente * lista, int len, int estado, int* indice);
int cliente_buscarOcurrenciaIdv2(sCliente* lista, int len, int id);
int cliente_imprimirUnCliente(sCliente* cliente);
int cliente_baja(sCliente* lista, int len, sPublicacion* listP ,int lenP);
int cliente_listar(sCliente* lista, int len, sPublicacion* listaP, int lenP);
int publicacion_publicar(sPublicacion* lista, int len, sCliente* listaCte, int lenCte);
void Cliente_forzar5elementos(sCliente* lista, int len);
void cliente_generarUnCuit(char* cuit);

#endif /* CLIENTE_H_ */
