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
int publicacion_listar(sPublicacion* lista, int len)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{
		r=0;
		printf("      Nombre     tipo  direccion     precio de publicidad diario  ID");
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
int publicacion_generarId(void)
{
	static int id=0;
	id=id+1;
	return id;
}
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

int publicacion_imprimirUno(sPublicacion* publicacion)
{
	int r=-1;
	if(publicacion!=NULL)
	{
		r=0;
		printf("\n%4d\t%5d\t\t%2d   %s",publicacion->id,publicacion->idCliente,publicacion->numRubro,publicacion->textodeAviso);
	}
	return r;
}
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
