/*
 * publicacion.c
 *
 *  Created on: 10 oct. 2020
 *      Author: roid
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"
#include "publicacion.h"

#define activa 1
#define pausada 0
#define tam_txt 63

/**
 * /brief imprime toda la publicacion del array
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_listar(sPublicacion* lista, int len)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{
		r=0;
		printf("  ID	IDcliente     Rubro   Estado  Texto");
		for(int i=0;i<len;i++)
			{
				if(!lista[i].isEmpty)
				{
					publicacion_imprimirUno(&lista[i]);
				}
			}
	}
	return r;
}

/**
 * /brief inicializa el array de publicacion(isEmpty =1)
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_init(sPublicacion* lista, int len)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{
		r=0;
		for(int i=0;i<len;i++)
		{
			lista[i].isEmpty=1;
		}
	}
	return r;
}

/**
 * /brief cambia el estado de una publicacion a "pausada(0)"
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_pausar(sPublicacion* lista,int len)
{
	int r=-1;
	sPublicacion aux;
	int indice,opc;
	int ok=1;
	if(lista!=NULL && len>0)
	{
		if(!utn_getInt("\nindique el ID de la publicacion:", "\nError, el iD es invalido",&aux.id , 3, 99999999, 1))
		{
			if(!publicacion_buscarOcurrenciaId(lista, len, aux.id, &indice))
			{
				r=0;
				aux=lista[indice];
				if(aux.estado==activa)
				{
					do{
						printf("\n-----Pausar Publicacion-----ID= %d "
							"\n -IDCliente : %d"
							"\n -Rubro: %d"
							"\n -Estado: Activa"
							"\n -Texto de Aviso: %s"
							"\n 1-SI"
							"\n 2-NO",aux.id,aux.idCliente,aux.numRubro,aux.textodeAviso);
						utn_getInt(" " ,"\nerror, la Opcion indicada no es valida", &opc, 1, 2, 1);
						switch(opc){
							case 1:
								ok=0;
								aux.estado=pausada;
								lista[indice]=aux;
								break;
							case 2:
								ok=0;
								break;
						}
					}while(ok);
				}
				else{
					printf("\nla Publicacion ya esta Pausada");
				}

			}
		}
	}
	return r;
}
/**
 * /brief cambia el estado de una publicacion a "activa(0)"
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_reanudar(sPublicacion* lista,int len)
{
	int r=-1;
	sPublicacion aux;
	int indice,opc;
	int ok=1;
	if(lista!=NULL && len>0)
	{
		if(!utn_getInt("\nindique el ID de la publicacion:", "\nError, el iD es invalido",&aux.id , 3, 99999999, 1))
		{
			if(!publicacion_buscarOcurrenciaId(lista, len, aux.id, &indice))
			{
				r=0;
				aux=lista[indice];
				if(aux.estado==pausada)
				{
					do{
						printf("\n-----Reanudar Publicacion-----ID= %d "
							"\n -IDCliente : %d"
							"\n -Rubro: %d"
							"\n -Estado: Pausada"
							"\n -Texto de Aviso: %s"
							"\n 1-SI"
							"\n 2-NO",aux.id,aux.idCliente,aux.numRubro,aux.textodeAviso);
						utn_getInt(" " ,"\nerror, la Opcion indicada no es valida", &opc, 1, 2, 1);
						switch(opc){
							case 1:
								ok=0;
								aux.estado=activa;
								lista[indice]=aux;
								break;
							case 2:
								ok=0;
								break;
						}
					}while(ok);
				}
				else{
					printf("\nerror la Publicacion esta Activa");
				}

			}
		}
	}
	return r;
}
/**
 * /brief genera un Id unico para una publicacion y la retorna
 *
 * /return (-1)error (el ID generado)OK
 *
 */
int publicacion_generarId(void)
{
	static int id=0;
	id=id+1;
	return id;
}
/**
 * /brief busca una publicacion por ID en el array y guarda la pocicion donde la encontro
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 * /param int es el Id que que se usara de referencia al buscar
 * /param int* es la direcion de memoria donde guardara el indice
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_buscarOcurrenciaId(sPublicacion* lista, int len, int id, int* indice)
{
	int r=-1;
	if(lista!=NULL && len>0 && id>0 && indice!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			if(id==lista[i].id)
			{
				r=0;
				*indice=i;
				break;
			}
		}
	}
	return r;
}
/**
 * /brief ordena el array de publicacion por nombre
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 * /param int es el orden por el cual ordenara
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_ordenarxNombre(sPublicacion* lista, int len, int order)
{
	int r=-1;
	int flagSwap=1;
	sPublicacion aux;
	if(lista!=NULL && len>0 && (order==0|| order==1))
	{
		r=0;
		do{
			flagSwap=0;
			for(int i=0;i<len;i++)
			{
				if((order==1 && strncmp(lista[i].textodeAviso,lista[i+1].textodeAviso,tam_txt)>0)
						||
					(order==0 && strncmp(lista[i].textodeAviso,lista[i+1].textodeAviso,tam_txt)>0))
				{
					aux=lista[i];
					lista[i]=lista[i+1];
					lista[i+1]=aux;
					flagSwap=1;
				}
			}
		}while(flagSwap);
	}
	return r;
}
/**
 * /brief agrega una publicacion al array
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 * /param int es el Id de la publicacion
 * /param int es el IdCLiente de la publicacion
 * /param int es el rubro de la publicacion
 * /param char* es el texto de la publicacion
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_add(sPublicacion* list, int len, int id, int idCliente, int rubro,char* texto)
{
	int r=-1;
	int indice;
	if(list!=NULL && len>0 && id>0 && idCliente>0 && texto!=NULL)
	{
		publicacion_buscarLibreUocupadov2(list, len, 1,&indice);
		list[indice].id=id;
		list[indice].isEmpty=0;
		list[indice].estado=activa;
		list[indice].idCliente=idCliente;
		list[indice].numRubro=rubro;
		strncpy(list[indice].textodeAviso,texto,tam_txt);
		r=0;
	}
 return r;
}
/**
 * /brief remueve una publicacion del array buscandola por iD
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 * /param int es el Id de la publicacion a remover
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_remove(sPublicacion* list, int len, int id)
{
	int r=-1;
	if(list!=NULL && len>0 && id>0)
	{
		list[publicacion_buscarOcurrenciaIdv2(list, len, id)].isEmpty=1;
		r=0;
	}
 return r;
}

/**
 * /brief imprime los datos de una publicacion
 * /param sPublicacion* es la direcion de memoria de una publicacion
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_imprimirUno(sPublicacion* publicacion)
{
	int r=-1;
	if(publicacion!=NULL)
	{
		r=0;
		if(publicacion->estado==pausada)
		{
			printf("\n%4d\t%5d\t\t%2d PAUSADA  %s",publicacion->id,publicacion->idCliente,publicacion->numRubro,publicacion->textodeAviso);
		}
		else{
			printf("\n%4d\t%5d\t\t%2d  ACTIVA  %s",publicacion->id,publicacion->idCliente,publicacion->numRubro,publicacion->textodeAviso);
		}
	}
	return r;
}

/**
 * /brief busca una pocicion libre u ocupada en el array y la retorna
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es el estado del isEmpty que buscara (1)libre (0) Ocupado
 *
 * /return (-1)error (el indice donde encontro la 1ra ocurrencia)OK
 *
 */
int publicacion_buscarLibreUocupado(sPublicacion * lista, int len, int estado)
{
	int r=-1;
		if(lista!=NULL && len>0&& (estado==1 || estado==0))
		{
			for(int i=0;i<len;i++)
			{
				if(lista[i].isEmpty==estado)
				{
					r=i;
					break;
				}
			}
		}
	return r;
}

/**
 * /brief busca una pocicion libre u ocupada en el array y la guarda
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es el estado del isEmpty que buscara (1)libre (0) Ocupado
 * /param int* es la direccion de memoria donde guardara el indice obtenido
 *
 * /return (-1)error (el indice donde encontro la 1ra ocurrencia)OK
 *
 */
int publicacion_buscarLibreUocupadov2(sPublicacion * lista, int len, int estado, int* indice)
{
	int r=-1;
		if(lista!=NULL && len>0&& (estado==1 || estado==0))
		{

			for(int i=0;i<len;i++)
			{
				if(lista[i].isEmpty==estado)
				{
					r=0;
					*indice=i;
					break;
				}
			}
		}
	return r;
}

/**
 * /brief busca una pocicion libre u ocupada en el array y la guarda
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es el estado del isEmpty que buscara (1)libre (0) Ocupado
 * /param int* es la direccion de memoria donde guardara el indice obtenido
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_buscarOcurrenciaIdv2(sPublicacion* lista, int len, int id)
{
	int r=-1;
	if(lista!=NULL && len>0 && id>0)
	{
		for(int i=0;i<len;i++)
		{
			if(id==lista[i].id)
			{
				r=i;
				break;
			}
		}
	}
	return r;
}

/**
 * /brief imprime todas las publicaciones de un cliente
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es id del Cliente
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_listarxCliente(sPublicacion* lista, int len, int idCte)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{

		for(int i=0;i<len;i++)
		{
			if(lista[i].idCliente==idCte&& lista[i].isEmpty==0)
			{
				r=0;
				publicacion_imprimirUno(&lista[i]);
			}
		}
	}
	return r;
}
/**
 * /brief remueve todas las publicaciones de un cliente
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es id del Cliente
 *
 * /return (-1)error (0)OK
 *
 */
int publicacion_removertodaslasPublicacionesdeUnCliente(sPublicacion* lista, int len, int idCte)
{
	int r=-1;
	if(lista!=NULL &&len>0)
	{

		for(int i=0;i<len;i++)
		{
			if(lista[i].idCliente==idCte)
			{
				r=0;
				lista[i].isEmpty=1;
			}
		}
	}
	return r;
}

/**
 * /brief realiza un conteo todas las publicaciones de un cliente y retorna la cantidad
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es id del Cliente
 *
 * /return (-1)error (la cantidad de publicacion de dichi cliente)OK
 *
 */
int publicacion_contarCantidadAvisosxCliente(sPublicacion* lista, int len, int idCte)
{
	int r=-1;
	if(lista!=NULL&& len>0)
	{
		r=0;
		for(int i=0;i<len;i++)
		{
			if(lista[i].idCliente==idCte && lista[i].isEmpty==0)
			{
				r++;
			}
		}
	}
	return r;
}

/**
 * /brief reliaza un conteo  todas las publicaciones en estado activo(1) u pausado(0) y retorna la cantidad
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es el estado que buscara 1(activa) 0(pausada)
 *
 * /return (-1)error (la cantidad de publicacion en ese estado)OK
 *
 */
int publicacion_contarActivasOpausadas(sPublicacion* lista, int len, int estado)
{
	int r=-1;
	if(lista!=NULL && len>0 && (estado==1||estado==0))
	{
		r=0;
		for(int i=0;i<len;i++)
		{
			if(lista[i].estado==estado &&lista[i].isEmpty==0)
			{
				r++;
			}
		}
	}
	return r;
}

/**
 * /brief realiza un conteo de publicacion segun un determinado rubro y lo retorna
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array
 * /param int es el rubro que se buscara
 *
 * /return (-1)error (la cantidad de publicaciones de ese rubro)OK
 *
 */
int publicacion_contarRubroConMasAvisos(sPublicacion* lista, int len, int rubro)
{
	int r=-1;
		if(lista!=NULL && len>0 && rubro>0)
		{
			r=0;
			for(int i=0;i<len;i++)
			{
				if(lista[i].numRubro==rubro&& lista[i].isEmpty==0)
				{
					r++;
				}
			}
		}
		return r;
}
void publicacion_forzarPublicacion(sPublicacion* lista, int len)
{
	publicacion_add(lista, len, publicacion_generarId(), 1, 2530,"algo 1");
	publicacion_add(lista, len, publicacion_generarId(), 1, 2530,"algo 2");
	publicacion_add(lista, len, publicacion_generarId(), 1, 2525,"algo 3");
	publicacion_add(lista, len, publicacion_generarId(), 2, 2530,"algo 4");
	publicacion_add(lista, len, publicacion_generarId(), 2, 2530,"algo 5");
	publicacion_add(lista, len, publicacion_generarId(), 2, 2530,"algo 6");
	publicacion_add(lista, len, publicacion_generarId(), 2, 2530,"algo 7");
	publicacion_add(lista, len, publicacion_generarId(), 3, 2530,"algo 8");
	publicacion_add(lista, len, publicacion_generarId(), 3, 2525,"algo 9");
	publicacion_add(lista, len, publicacion_generarId(), 3, 2530,"algo 10");
	publicacion_add(lista, len, publicacion_generarId(), 4, 3100,"algo 11");
	publicacion_add(lista, len, publicacion_generarId(), 4, 3100,"algo 12");
}
