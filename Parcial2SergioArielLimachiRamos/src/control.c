/*
 * control.c
 *
 *  Created on: 22 nov. 2020
 *      Author: roid
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "cliente.h"
#include "afiche.h"
#include "control.h"
#include "parser.h"

#define tam_str_cte 60
#define tam_str_afiche 60

int control_alta_cliente(LinkedList* lista)
{
	int r=-1;
	int todoOk=1;
	sCliente aux;
	sCliente* nuevo;
	if(lista!=NULL)
	{
		if(todoOk==1 && (utn_pedir_cadena("\nindique Nombre: ", aux.nombre, tam_str_cte)||utn_soloLetras(aux.nombre)))
		{
				todoOk=0;
		}
		if(todoOk==1 && (utn_pedir_cadena("\nindique Apellido: ", aux.apellido, tam_str_cte)||utn_soloLetras(aux.apellido)))
		{
			todoOk=0;
		}
		if(todoOk==1 && (utn_pedir_cadena("\nindique Cuit en este formato con -(xx-xxxxxxxx-x): ", aux.cuit, tam_str_cte)||utn_esCuit(aux.cuit)||control_elCuitNoEstaRepedito(lista, aux.cuit)))
		{
			todoOk=0;
		}
		if(todoOk)
		{
			cliente_set_id(&aux,utn_generarID("clienteID.bin"));
			nuevo=cliente_newConParametros(aux.id, aux.nombre, aux.apellido, aux.cuit);
			if(nuevo!=NULL)
			{
				ll_add(lista, nuevo);
				printf("\ncliente cargado\n");
				r=0;
			}
		}
		else{
			printf("Error, no se ha podido Cargar el Usuario\n");
		}
	}
	return r;
}
int control_listar_clientes(LinkedList* lista)
{
	int r;
	printf(" ID        NOMBRE           APELLIDO             CUIT       \n");
	r=ll_map(lista, cliente_imprimirUnElemento_conMap);
	return r;
}

int control_vender_afiche(LinkedList* clientes, LinkedList* afiches)
{
	int r=-1;
	int todoOk=1;
	sAfiche aux;
	sAfiche* nuevo;
	if(clientes!=NULL && afiches!=NULL)
	{
		if(todoOk==1 && (utn_getInt("indique un ID usuario: ", "error,el numero ingresado no es valido\n", &aux.idCliente, 3, 99999999, 1)||control_afiche_idClienteEsta(clientes, aux.idCliente)))
		{
			printf("el id indicado no existe!!!\n");
			todoOk=0;
		}
		if(todoOk==1 && (utn_getInt("indique la cantidad de Afiches: ", "error, el numero ingresado no es valido", &aux.cantAfiches, 3, 99999999, 1)||!afiche_isValid_cantAfiches(aux.cantAfiches)))
		{
			todoOk=0;
		}
		if(todoOk==1 && (utn_pedir_cadena("\nindique Nombre del Archivo donde se encuentra la imagen del Afiche: ", aux.dirImagen, tam_str_cte)||!afiche_isValid_dirImagen(aux.dirImagen)))
		{
			todoOk=0;
		}
		if(todoOk==1 && (utn_pedir_cadena("\nindique la Zona en la que se pegaran los afiches ", aux.zona, tam_str_cte)||!afiche_isValid_zona(aux.zona)))
		{
			todoOk=0;
		}
		if(todoOk)
		{
			afiche_set_id(&aux, utn_generarID("ventasID.bin"));
			afiche_set_estado(&aux, 0);
			nuevo=afiche_newConParametros(aux.id, aux.idCliente, aux.cantAfiches, aux.dirImagen, aux.zona, aux.estado);
			if(nuevo!=NULL)
			{
				ll_add(afiches, nuevo);
				printf("\nVenta Cargada\n");
				r=0;
			}
		}
		else{
			printf("Error, no se ha podido Cargar el afiche\n");
		}
	}
	return r;
}
int control_elCuitNoEstaRepedito(LinkedList* lista,char* cuit)
{
	int r=-1;
	if(lista!=NULL)
	{
		if(ll_search(lista, cliente_esCuitX, cuit)==-1)
		{
			r=0;
		}
	}
	return r;
}

int control_afiche_idClienteEsta(LinkedList* lista,int idCte)
{
	int r=-1;
	if(lista!=NULL)
	{
		if(ll_search(lista,cliente_esIdX,&idCte)!=-1)
		{
			r=0;
		}
	}
	return r;
}
int control_listar_afiches(LinkedList* lista)
{
	int r;
	printf(" ID IDCLIENTE CANT-AFICHES N.ARCHIVO-IMG     ZONA     ESTADO\n");
	r=ll_map(lista, afiche_imprimirUnElemento_conMap);
	return r;
}
int control_modificar_ventaAfiche(LinkedList* afiches,LinkedList* clientes)
{
	int r=-1;
	int indice,opc;
	sAfiche aux,mod;
	sAfiche* pAfiche;
	if(afiches!=NULL && clientes!=NULL)
	{
		printf(" ID IDCLIENTE CANT-AFICHES N.ARCHIVO-IMG     ZONA     ESTADO\n");
		ll_map(afiches,afiche_imprimirUnElemento_conMap_soloSies_aCobrar);
		if(!utn_getInt("indique el id de la venta: ", "el ID ingresado no es valido", &aux.id, 3, 999999, 1))
		{
			indice=ll_search(afiches, afiche_esCiertoId, &aux.id);
			if(indice!=-1)
			{
				pAfiche=(sAfiche*)ll_get(afiches, indice);
				if(!afiche_get_estado(pAfiche))
				{
					aux=*pAfiche;
					do{
						printf("MODIFICAR AFICHE\n"
							"1-idCliente: %d\n"
							"2-cantidad de afiches: %d\n"
							"3-archivo de la imagen del afiche: %s\n"
							"4-zona: %s\n"
							"5-guardar Cambios y salir\n"
							"6-salir\n",aux.idCliente,aux.cantAfiches,aux.dirImagen,aux.zona);
						utn_getInt(" ", "error, la opcion indicada no es valida\n", &opc, 1, 6, 1);
						switch(opc)
						{
							case 1:
								if(!utn_getInt("indique el idCliente: \n", "error, el id ingresado no es valido\n", &mod.idCliente, 1, 99999999, 1)&&(ll_search(clientes, cliente_esCiertoId, &mod.idCliente)!=-1))
								{
									afiche_set_idCliente(&aux, mod.idCliente);
								}
								break;
							case 2:
								if(!utn_getInt("indique la cantidad de afiches: \n", "error, el numero ingresado no es valido\n", &mod.cantAfiches, 1, 99999999, 1))
								{
									afiche_set_cantAfiches(&aux, mod.cantAfiches);
								}
								break;
							case 3:
								if(!utn_pedir_cadena("indique el nombre del archivo de la imagen afiche:\n", mod.dirImagen, tam_str_afiche))
								{
									afiche_set_dirImagen(&aux, mod.dirImagen);
								}
								break;
							case 4:
								if(!utn_pedir_cadena("indique el nombre de la zona:\n", mod.zona, tam_str_afiche))
								{
									afiche_set_zona(&aux, mod.zona);
								}
								break;
							case 5:
								printf("La Venta ha sido modificada con exito\n");
								*pAfiche=aux;
								opc=-1;
								break;
							case 6:
								opc=-1;
								break;
						}
					}while(opc!=-1);
				}
				else{
					printf("error, no se puede modificar un afiche ya cobrado!!!\n");
				}
			}
			else{
				printf("el id de venta ingresado no existe!!!!!\n");
			}
		}
		r=0;
	}
	return  r;
}
int control_cobrar_ventaAfiche(LinkedList* afiches, LinkedList* clientes)
{
	int r=-1;
	int indice,id,opc;
	sCliente* pCliente;
	sAfiche* pAfiche;
	if(afiches!=NULL && clientes!=NULL)
	{
		ll_map(afiches,afiche_imprimirUnElemento_conMap_soloSies_aCobrar);
		utn_getInt("indique el numero de ID: ", "error, el numero ingresado no es valido", &id, 3, 9999999, 1);
		indice=ll_search(afiches, afiche_cobrar_buscandoxId,&id);
		if(indice!=-1)
		{
			pAfiche=(sAfiche*)ll_get(afiches,indice);
			if(afiche_get_estado(pAfiche)==0)
			{
				indice=ll_search(clientes, cliente_esCiertoId, &pAfiche->idCliente);
				pCliente=(sCliente*)ll_get(clientes, indice);
				printf("--COBRAR-- id Afiche nro: %d\n"
						"Apellido de Cliente: %s\n"
						"Nombre de Cliente: %s\n"
						"CUIT: %s\n",afiche_get_id(pAfiche),cliente_get_apellido(pCliente),cliente_get_nombre(pCliente),cliente_get_cuit(pCliente));
				utn_getInt("esta seguro que desea cobrar este afiche?... \n1-si\ningrese cualquier otro caracter en caso contrario\n", "la opcion indicada no es valida\n", &opc, 3, 999999, 1);
				switch(opc)
				{
					case 1:
						afiche_set_estado(pAfiche, 1);
						printf("se ha cobrado el afiche nro %d\n",afiche_get_id(pAfiche));
						break;
					default:
						printf("no se ha cobrado el afiche\n");
				}
			}
			else{
				printf("error, no se puede Cobrar un afiche ya cobrado!!!\n");
			}
		}
		else{
			printf("el id Ingresado no exite!!!!\n");
		}
	}
	return r;
}
int control_cargar_datosDesdeArchivo(LinkedList* afiches, char* patch,int(*pFunc)(FILE*,LinkedList*))
{
	int r=-1;
	FILE* pfile;
	if(afiches!=NULL)
	{
		pfile=fopen(patch,"r");
		if(pfile!=NULL)
		{
			pFunc(pfile, afiches);
			fclose(pfile);
			r=0;
		}
	}
	return r;
}
int control_guardar_clientesEnArchivoText(LinkedList* lista,char* patch)
{
	FILE* pFile;
	sCliente* aux;
	int r=-1;
	if(lista!=NULL)
	{
		pFile=fopen(patch,"w");
		if(pFile!=NULL)
		{
			fprintf(pFile,"id,nombre,apellido,cuit\n");
			for(int i=0;i<ll_len(lista);i++)
			{
				aux=(sCliente*)ll_get(lista, i);
				fprintf(pFile,"%d,%s,%s,%s\n",aux->id,aux->nombre,aux->apellido,aux->cuit);
			}
			fclose(pFile);
			r=0;
		}
	}
	return r;
}
int control_guardar_afichesEnArchivoText(LinkedList* lista,char* patch)
{
	FILE* pFile;
	sAfiche* aux;
	int r=-1;
	if(lista!=NULL)
	{
		pFile=fopen(patch,"w");
		if(pFile!=NULL)
		{
			fprintf(pFile,"id,idCliente,cantAfiches,nombrearchivodeImagen,zona,estado\n");
			for(int i=0;i<ll_len(lista);i++)
			{
				aux=(sAfiche*)ll_get(lista, i);
				fprintf(pFile,"%d,%d,%d,%s,%s,%d\n",aux->id,aux->idCliente,aux->cantAfiches,aux->dirImagen,aux->zona,aux->estado);
			}
			fclose(pFile);
			r=0;
		}
	}
	return r;
}
int control_generar_informeCobros(LinkedList* clientes,LinkedList* afiches,char* patch)
{
	int r=-1;
	int resultado;
	sCliente* aux;
	FILE* pFile=fopen(patch,"w");
	if(clientes!=NULL && afiches!=NULL&& pFile!=NULL)
	{
		fprintf(pFile,"id,nombre,apellido,cuit,cantdeAfichesCobrados\n");
		for(int i=0;i<ll_len(clientes);i++)
		{
			aux=(sCliente*)ll_get(clientes, i);
			ll_reduceIntII(afiches, afiche_esCiertoIdClienteYestaCobrado, &aux->id, &resultado);
			fprintf(pFile,"%d,%s,%s,%s,%d\n",aux->id,aux->nombre,aux->apellido,aux->cuit,resultado);
		}
		fclose(pFile);
	}

	return r;
}
int control_generar_informeDeudas(LinkedList* clientes,LinkedList* afiches,char* patch)
{
	int r=-1;
	int resultado;
	sCliente* aux;
	FILE* pFile=fopen(patch,"w");
	if(clientes!=NULL && afiches!=NULL&& pFile!=NULL)
	{
		fprintf(pFile,"id,nombre,apellido,cuit,cantdeAfichesaCobrar\n");
		for(int i=0;i<ll_len(clientes);i++)
		{
			aux=(sCliente*)ll_get(clientes, i);
			ll_reduceIntII(afiches, afiche_esCiertoIdClienteYesAcobrar, &aux->id, &resultado);
			fprintf(pFile,"%d,%s,%s,%s,%d\n",aux->id,aux->nombre,aux->apellido,aux->cuit,resultado);
		}
		fclose(pFile);
	}

	return r;
}

