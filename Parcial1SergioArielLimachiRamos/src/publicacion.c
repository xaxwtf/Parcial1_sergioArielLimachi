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
int publicacion_listar(sPublicacion* lista[], int len)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{
		r=0;
		printf("  ID	IDcliente     Rubro   Estado  Texto");
		for(int i=0;i<len;i++)
			{
				if(lista[i]!=NULL)
				{
					publicacion_imprimirUno(lista[i]);
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
int publicacion_init(sPublicacion* lista[], int len)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{
		r=0;
		for(int i=0;i<len;i++)
		{
			lista[i]=NULL;
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
int publicacion_pausar(sPublicacion* lista[],int len)
{
	int r=-1;
	int indice,opc,id;
	int ok=1;
	if(lista!=NULL && len>0)
	{
		if(!utn_getInt("\nindique el ID de la publicacion:", "\nError, el iD es invalido",&id , 3, 99999999, 1))
		{
			if(!publicacion_buscarOcurrenciaId(lista, len, id, &indice))
			{
				r=0;
				if(publicacion_get_estado(lista[indice])==activa)
				{
					do{
						printf("\n-----Pausar Publicacion-----ID= %d "
							"\n -IDCliente : %d"
							"\n -Rubro: %d"
							"\n -Estado: Activa"
							"\n -Texto de Aviso: %s"
							"\n 1-SI"
							"\n 2-NO",lista[indice]->id,lista[indice]->idCliente,lista[indice]->numRubro,lista[indice]->textodeAviso);
						utn_getInt(" " ,"\nerror, la Opcion indicada no es valida", &opc, 1, 2, 1);
						switch(opc){
							case 1:
								ok=0;
								publicacion_set_estado(lista[indice], pausada);
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
int publicacion_reanudar(sPublicacion* lista[],int len)
{
	int r=-1;
	int indice,opc,id;
	int ok=1;
	if(lista!=NULL && len>0)
	{
		if(!utn_getInt("\nindique el ID de la publicacion:", "\nError, el iD es invalido",&id , 3, 99999999, 1))
		{
			if(!publicacion_buscarOcurrenciaId(lista, len, id, &indice))
			{
				r=0;
				if(publicacion_get_estado(lista[indice])==pausada)
				{
					do{
						printf("\n-----Reanudar Publicacion-----ID= %d "
							"\n -IDCliente : %d"
							"\n -Rubro: %d"
							"\n -Estado: Pausada"
							"\n -Texto de Aviso: %s"
							"\n 1-SI"
							"\n 2-NO",lista[indice]->id,lista[indice]->idCliente,lista[indice]->numRubro,lista[indice]->textodeAviso);
						utn_getInt(" " ,"\nerror, la Opcion indicada no es valida", &opc, 1, 2, 1);
						switch(opc){
							case 1:
								ok=0;
								publicacion_set_estado(lista[indice], activa);
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
int publicacion_buscarOcurrenciaId(sPublicacion* lista[], int len, int id, int* indice)
{
	int r=-1;
	if(lista!=NULL && len>0 && id>0 && indice!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			if(id==publicacion_get_id(lista[i]))
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
int publicacion_add(sPublicacion* lista[],int len, sPublicacion* publicacion)
{
	int r=-1;
	int indice;
	if(lista!=NULL && publicacion!=NULL)
	{
		if(publicacion_buscarLibreUocupadov2(lista, len, 1,&indice)!=-1)
		{
			lista[indice]=publicacion;
			r=0;
		}
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
int publicacion_remove(sPublicacion* list[], int len, int id)
{
	int r=-1;
	int indice;
	if(list!=NULL && len>0 && id>0)
	{
		if(publicacion_buscarOcurrenciaId(list, len, id, &indice)!=-1)
		{
			publicacion_delete(list[indice]);
			list[indice]=NULL;
			r=0;
		}
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
int publicacion_buscarLibreUocupado(sPublicacion * lista[], int len, int estado)
{
	int r=-1;
		if(lista!=NULL && len>0&& (estado==1 || estado==0))
		{
			for(int i=0;i<len;i++)
			{
				if((estado==1 && lista[i]==NULL)|| (estado==0 && lista[i]!=NULL))
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
int publicacion_buscarLibreUocupadov2(sPublicacion * lista[], int len, int estado, int* indice)
{
	int r=-1;
		if(lista!=NULL && len>0&& (estado==1 || estado==0))
		{

			for(int i=0;i<len;i++)
			{
				if((estado==1 && lista[i]==NULL)|| (estado==0 && lista[i]!= NULL))
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
int publicacion_buscarOcurrenciaIdv2(sPublicacion* lista[], int len, int id)
{
	int r=-1;
	if(lista!=NULL && len>0 && id>0)
	{
		for(int i=0;i<len;i++)
		{
			if(id==publicacion_get_id(lista[i]))
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
int publicacion_listarxCliente(sPublicacion* lista[], int len, int idCte)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{

		for(int i=0;i<len;i++)
		{
			if(publicacion_get_idCte(lista[i])==idCte)
			{
				r=0;
				publicacion_imprimirUno(lista[i]);
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
int publicacion_removertodaslasPublicacionesdeUnCliente(sPublicacion* lista[], int len, int idCte)
{
	int r=-1;
	if(lista!=NULL &&len>0)
	{

		for(int i=0;i<len;i++)
		{
			if(publicacion_get_idCte(lista[i])==idCte)
			{
				publicacion_delete(lista[i]);
				lista[i]=NULL;
				r=0;
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
 * /param int es el estado que buscara (1)activa (0)pausada (3)no discrimina ninguno
 *
 * /return (-1)error (la cantidad de publicacion de dichi cliente)OK
 *
 */
int publicacion_contarCantidadAvisosPausadosuActivoxCliente(sPublicacion* lista[], int len, int idCte,int estadoAbuscar)
{
	int r=-1;
	if(lista!=NULL&& len>0 &&(estadoAbuscar==activa || estadoAbuscar==pausada || estadoAbuscar==3))
	{
		r=0;
		for(int i=0;i<len;i++)
		{
			if((estadoAbuscar==0 || estadoAbuscar==1) && publicacion_get_idCte(lista[i])==idCte && publicacion_get_estado(lista[i])==estadoAbuscar)
			{
				r++;
			}
			else if(estadoAbuscar==3 && publicacion_get_idCte(lista[i])==idCte)
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
int publicacion_contarActivasOpausadas(sPublicacion* lista[], int len, int estado)
{
	int r=-1;
	if(lista!=NULL && len>0 && (estado==1||estado==0))
	{
		r=0;
		for(int i=0;i<len;i++)
		{
			if(publicacion_get_estado(lista[i])==estado)
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
int publicacion_contarRubroConMasAvisos(sPublicacion* lista[], int len, int rubro)
{
	int r=-1;
		if(lista!=NULL && len>0 && rubro>0)
		{
			r=0;
			for(int i=0;i<len;i++)
			{
				if(publicacion_get_numRubro(lista[i])==rubro)
				{
					r++;
				}
			}
		}
		return r;
}
void publicacion_forzarPublicacion(sPublicacion* lista[], int len)
{
	sPublicacion* nuevo;
	nuevo=publicacion_new(publicacion_generarId(), 1, "algo 1", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 1, "algo 2", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 1, "algo 3", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 1, "algo 4", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 2, "algo 5", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 2, "algo 6", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 2, "algo 7", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 3, "algo 8", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 3, "algo 9", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 3, "algo 10", 2130, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 4, "algo 11", 2320, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}
	nuevo=publicacion_new(publicacion_generarId(), 4, "algo 12", 2530, 1);
	if(nuevo!=NULL)
	{
		publicacion_add(lista, len, nuevo);
	}

}
int ordenarx2criterios(sPublicacion* list, int len, int order)
{
	int r=-1;
	sPublicacion aux;
	int flagSwap=1;
		if(list!=NULL && len > 0 && (order==0|| order==1))
		{
			r=0;
			do{
				flagSwap=0;
				for(int i=0;i<len;i++)
				{
					if((order==1 && (list[i].isEmpty==0 && list[i+1].isEmpty==0) && (strncmp(list[i].textodeAviso,list[i+1].textodeAviso,tam_txt)>0
																||
									(strncmp(list[i].textodeAviso,list[i+1].textodeAviso,tam_txt)==0 && list[i].numRubro > list[i+1].numRubro)))
						||
					(order==0 && (list[i].isEmpty==0 && list[i+1].isEmpty==0) && (strncmp(list[i].textodeAviso,list[i+1].textodeAviso,tam_txt)<0
																||
								(strncmp(list[i].textodeAviso,list[i+1].textodeAviso,tam_txt)==0 && list[i].numRubro<list[i+1].numRubro))))
					{
						aux= list[i];
						list[i]=list[i+1];
						list[i+1]=aux;
						flagSwap=1;
					}
				}
			}while(flagSwap);
		}
		return r;
 return 0;
}
sPublicacion* publicacion_new(int id, int idCte, char* txtAviso, int rubro, int estado)
{
	sPublicacion* nuevo= (sPublicacion*)malloc(sizeof(sPublicacion));
	if(nuevo!=NULL)
	{
		if(!(publicacion_set_id(nuevo, id)!=-1 &&
				publicacion_set_idCliente(nuevo, idCte)!=-1&&
				publicacion_set_textodeAviso(nuevo, txtAviso)!=-1&&
				publicacion_set_numRubro(nuevo, rubro)!=-1 &&
				publicacion_set_estado(nuevo, estado)!=-1))
		{
			publicacion_delete(nuevo);
			nuevo=NULL;
		}
	}
	return nuevo;
}
int publicacion_set_id(sPublicacion* elemento, int id)
{
	int r=-1;
	if(elemento!=NULL && id>0)
	{
		elemento->id=id;
		r=0;
	}
	return r;
}
int publicacion_set_idCliente(sPublicacion* elemento, int idCliente)
{
	int r=-1;
	if(elemento!=NULL && idCliente>0)
	{
		elemento->idCliente=idCliente;
		r=0;
	}
	return r;
}
int publicacion_set_numRubro(sPublicacion* elemento, int numRubro)
{
	int r=-1;
	if(elemento!=NULL && numRubro>0)
	{
		elemento->numRubro=numRubro;
		r=0;
	}
	return r;
}
int publicacion_set_textodeAviso(sPublicacion* elemento, char* textodeAviso)
{
	int r=-1;
	if(elemento!=NULL && strlen(textodeAviso)<=63)
	{
		strcpy(elemento->textodeAviso,textodeAviso);
		r=0;
	}
	return r;
}
int publicacion_set_estado(sPublicacion* elemento, int estado)
{
	int r=-1;
	if(elemento!=NULL && (estado==0||estado==1))
	{
		elemento->estado=estado;
		r=0;
	}
	return r;
}
int publicacion_get_id(sPublicacion* elemento)
{
	int r=-1;
	if(elemento!=NULL)
	{
		r=elemento->id;
	}
	return r;
}
int publicacion_get_idCte(sPublicacion* elemento)
{
	int r=-1;
	if(elemento!=NULL)
	{
		r=elemento->idCliente;
	}
	return r;
}
int publicacion_get_textodeAviso(sPublicacion* elemento,char* textodeAviso)
{
	int r=-1;
	if(elemento!=NULL)
	{
		strcpy(textodeAviso,elemento->textodeAviso);
		r=0;
	}
	return r;
}
int publicacion_get_numRubro(sPublicacion* elemento)
{
	int r=-1;
	if(elemento!=NULL)
	{
		r=elemento->numRubro;
	}
	return r;
}
int publicacion_get_estado(sPublicacion* elemento)
{
	int r=-1;
	if(elemento!=NULL)
	{
		r=elemento->estado;
	}
	return r;
}
int publicacion_delete(sPublicacion* elemento)
{
	int r=-1;
	if(elemento!=NULL)
	{
		free(elemento);
		r=0;
	}
	return r;
}
