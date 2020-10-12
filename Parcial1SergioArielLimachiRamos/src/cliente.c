/*
 * cliente.c
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
#define tam_string 50

/**
 * /brief imprime todos los clientes del array
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param sPublicacion* es el array de publicaciones
 * /param int es el tamaño del array de publicaciones
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_listar(sCliente* lista, int len, sPublicacion* listaP, int lenP)
{
	int r=-1;
	if(lista!=NULL && len>0)
	{
		r=0;
		printf("\n  ID\tlastName\t  Name\t\tCuit\t\tNumero de avisos Publicados");
		for(int i=0;i<len;i++)
			{
				if(!lista[i].isEmpty)
				{
					cliente_imprimirUnCliente(&lista[i]);
					printf("\t\t%d",publicacion_contarCantidadAvisosxCliente(listaP, lenP,lista[i].id));
				}
			}
	}
	return r;
}
/**
 * /brief inicializa el array de cliente
 * /param sCliente* es el array de cliente
 * /param int es el tamaño del array de cliente
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_init(sCliente* lista, int len)
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
 * /brief da de alta Un cliente
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_alta(sCliente* lista, int len)
{
	int r=-1;
	int todoOk=1;
	sCliente aux;
	if(lista!=NULL && len>0)
	{
		if(cliente_buscarLibreUocupado(lista, len,1)!=-1)
		{

			if(todoOk==1 && (utn_pedir_cadena("\nindique Nombre: ", aux.name, tam_string)||utn_soloLetras(aux.name)))
			{
				todoOk=0;
			}
			if(todoOk==1 && (utn_pedir_cadena("\nindique Apellido: ", aux.lastName, tam_string)||utn_soloLetras(aux.lastName)))
			{
				todoOk=0;
			}
			if(todoOk==1 && (utn_pedir_cadena("\nindique Cuit en este formato con -(xx-xxxxxxxx-x): ", aux.cuit, 15)||utn_esCuit(aux.cuit)))
			{
				printf("\n no se cargo!!!!!!!!!!!!!!!!!");
				todoOk=0;
			}
			if(todoOk)
			{
				r=0;
				cliente_add(lista, len, cliente_generarId(), aux.name, aux.lastName, aux.cuit);
			}
		}
		else{
			printf("\n !!!!Registro lleno, no se pueden cargar mas clientes");
		}
	}
	return r;
}

/**
 * /brief modifica los datos de un cliente
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_modificar(sCliente* lista,int len)
{
	int r=-1;
	sCliente aux,mod;
	int indice,opc;
	int ok=1;
	if(lista!=NULL && len>0)
	{
		if(!utn_getInt("\nindique el ID:", "\nError, el iD es invalido",&aux.id , 3, len, 1))
		{
			if(!cliente_buscarOcurrenciaId(lista, len, aux.id, &indice))
			{
				r=0;
				aux=lista[indice];
				do{
					printf("\n-----MODIFICAR CLIENTE-----ID= %d "
							"\n 1-Name:  %s"
							"\n 2-LastName: %s"
							"\n 3-Cuit: %s"
							"\n 4-salir y descartar modificaciones"
							"\n 5-salir y guardar",aux.id,aux.name,aux.lastName,aux.cuit);
					utn_getInt(" " ,"\nerror, la Opcion indicada no es valida", &opc, 1, 5, 1);
					switch(opc){
					case 1:
						if(utn_pedir_cadena("\nnew Name: ", mod.name, tam_string)||utn_soloLetras(mod.name))
						{
							printf("\nerror, indique solo letras");
						}
						else{
							strncpy(aux.name,mod.name,tam_string);
						}
						break;
					case 2:
						if(utn_pedir_cadena("\nnew Apeliido: ", mod.lastName, tam_string)||utn_soloLetras(mod.name))
						{
							printf("\nerror, indique solo letras");
						}
						else{
							strncpy(aux.lastName,mod.lastName,tam_string);
						}
						break;
					case 3:
						if(utn_pedir_cadena("\nnuevo Cuit (xx-xxxxxxxx-x): ", mod.cuit, tam_string)||utn_esCuit(mod.cuit))
						{
							printf("\nerror. el cuit ingresado no es valido");
						}
						else{
							strncpy(aux.cuit,mod.cuit,tam_string);
						}
						break;
					case 4:
						ok=0;
						break;
					case 5:
						ok=0;
						lista[indice]=aux;
						break;
					}
				}while(ok);
			}
		}
	}
	return r;
}

/**
 * /brief da de Baja a un cliente
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param sPublicacion* es el array de publicaciones
 * /param int es el tamaño del array de publicaciones
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_baja(sCliente* lista, int len,sPublicacion* publicaciones, int lenP)
{
	int r=-1;
		sCliente aux;
		int indice,opc;
		int ok=1;
		if(lista!=NULL && len>0)
		{
			if(!utn_getInt("\nindique el numero de ID:", "\nError, el ID indicado esta fuera de rango",&aux.id , 3, 999999, 1))
			{
				if(!cliente_buscarOcurrenciaId(lista, len, aux.id, &indice))
				{
					printf("  ID	IDcliente     Rubro Texto");
					publicacion_listarxCliente(publicaciones, lenP, aux.id);
					r=0;
					aux=lista[indice];
					do{
						printf("\n-----CONFIRMAR BAJA DE CLIENTE-----ID=%d "
								"\n Name:  %s "
								"\n Apellido: %s"
								"\n Cuit: %s"
								"\n 1-SI"
								"\n 2-NO",aux.id,aux.name,aux.lastName,aux.cuit);
						utn_getInt(" ", "la opcion indicada no es valida", &opc, 1, 2, 1);
							switch(opc){
							case 1:
								cliente_remove(lista, len, aux.id);
								publicacion_removertodaslasPublicacionesdeUnCliente(publicaciones, lenP, aux.id);
								ok=0;
								break;
							case 2:
								ok=0;
								break;
							}
						}while(ok);
				}
				else{
					printf("\nEl cliente Indicado no existe:");
				}
			}
		}
		return r;
}
/**
 * /brief genera un id Unico para la estructura cliente
 * /param
 *
 * /return el ID generado
 *
 */
int cliente_generarId(void)
{
	static int id=0;
	id=id+1;
	return id;
}

/**
 * /brief Busca un determinado Id en el array de Cliente
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param int es el ID que se buscara en el array de cliente
 * /param int* es la dirrecion de memoria donde guardara el indice donde encontro el ID
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_buscarOcurrenciaId(sCliente* lista, int len, int id, int* indice)
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
 * /brief Busca un determinado Id en el array de Cliente
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param int es el ID que se buscara en el array de cliente
 * /param
 *
 * /return (-1)error (el indice de la pocicion donde encontro el ID)OK
 *
 */
int cliente_buscarOcurrenciaIdv2(sCliente* lista, int len, int id)
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
 * /brief Ordena el Array de Cliente por el Nombre
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param int es el Orden por el cual Ordenara El array 1(acendente) 0(decendente)
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_ordenarxNombre(sCliente* lista, int len, int order)
{
	int r=-1;
	int flagSwap=1;
	sCliente aux;
	if(lista!=NULL && len>0 && (order==0|| order==1))
	{
		r=0;
		do{
			flagSwap=0;
			for(int i=0;i<len;i++)
			{
				if((order==1 && strncmp(lista[i].name,lista[i+1].name,50)>0)
						||
					(order==0 && strncmp(lista[i].name,lista[i+1].name,50)>0))
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
int cliente_add(sCliente* list, int len, int id,char* name,char* lastName, char* cuit)
{
	int r=-1;
	int indice;
	if(list!=NULL && len>0 && id>0 && name!=NULL && lastName!=NULL && cuit!=NULL)
	{
		cliente_buscarLibreUocupadov2(list, len, 1, &indice);
		list[indice].id=id;
		list[indice].isEmpty=0;
		strncpy(list[indice].name,name,tam_string);
		strncpy(list[indice].lastName,lastName,tam_string);
		strncpy(list[indice].cuit,cuit,13);
		r=0;
	}
 return r;
}

/**
 * /brief busca y remueve un cliente de la lista buscandolo por ID
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param int es el ID de referencia con el que se buscara el cliente
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_remove(sCliente* list, int len, int id)
{
	int r=-1;
	if(list!=NULL && len>0 && id>0)
	{
		list[cliente_buscarOcurrenciaIdv2(list, len, id)].isEmpty=1;
		r=0;
	}
 return r;
}
/**
 * /brief Realiza una busqueda de la 1ra pocicion Libre(1) u Ocupada(0) del array y la retorna
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param int es el estado del isEmpty que buscara (1)Libre  u 0(Ocupado)
 *
 * /return (-1)error (el indice en donde econtro la 1ra concidencia)OK
 *
 */
int cliente_buscarLibreUocupado(sCliente * lista, int len, int estado)
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
 * /brief Realiza una busqueda de la 1ra pocicion Libre(1) u Ocupada(0) del array y la guarda por referencia
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 * /param int es el estado del isEmpty que buscara (1)Libre  u 0(Ocupado)
 * /param int* es la dirrecion de memoria donde guardara el Indice Obtenido
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_buscarLibreUocupadov2(sCliente * lista, int len, int estado, int* indice)
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
 * /brief Imprime todos los datos de Un cliente
 * /param sCliente* es la direccion de memoria de un cliente
 *
 * /return (-1)error (0)OK
 *
 */
int cliente_imprimirUnCliente(sCliente* cliente)
{
	int r=-1;
	if(cliente!=NULL)
	{
		r=0;
		printf("\n%4d\t%8s\t%8s\t%s",cliente->id,cliente->lastName,cliente->name,cliente->cuit);
	}
	return r;
}


/**
 * /brief Realiza la carga de 5 clientes
 * /param sCliente* es el array de clientes
 * /param int es el tamaño del array de clientes
 *
 * /return
 *
 */
void Cliente_forzar5elementos(sCliente* lista, int len)
{
	char name[50]="aaaaaaa";
	char apellido[50]="aaaaaaa";
	char cuit[14]="00-00000000-0";

	for(int i=0;i<5;i++)
	{
		utn_cambiarLetrasString(name, 7);
		utn_cambiarLetrasString(apellido, 7);
		utn_cambiarCaracteresCuit(cuit);
		cliente_add(lista, len, cliente_generarId(), name, apellido, cuit);
	}
}
