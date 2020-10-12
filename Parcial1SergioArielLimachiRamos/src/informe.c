/*
 * informe.c
 *
 *  Created on: 11 oct. 2020
 *      Author: roid
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"
#include "publicacion.h"
#include "informe.h"

void informar(sCliente* listaCte, int lenCte, sPublicacion* listaPub, int lenP)
{
	int opc=123;
	do{
		utn_getInt("\nINFORMES"
				"\n1-Cliente con más avisos."
				"\n2-Cantidad de avisos pausados."
				"\n3-Rubro con mas avisos."
				"\n4-Salir", "\nla opcion indicada no es valida", &opc, 1, 4, 1);
		switch(opc)
			{
				case 1:
					informe_buscarClienteconmasAvisos(listaCte, lenCte, listaPub, lenP);
					break;
				case 2:
					informe_avisosPausados(listaPub, lenP);
					break;
				case 3:
					informe_rubroConMasAvisos(listaPub, lenP);
					break;
			}
	}while(opc!=4);

}
int informe_buscarClienteconmasAvisos(sCliente* listCte, int lenCte, sPublicacion* listP, int lenP)
{
	int r=-1;
	sCliente cteMasAvisos;
	int cantdePublicacionesMax,cantPublicaciones;
	if(listCte!=NULL && listP!=NULL && lenCte>0 &&lenP>0)
	{
		r=0;
		cteMasAvisos=listCte[0];
		cantdePublicacionesMax=publicacion_contarCantidadAvisosxCliente(listP, lenP, cteMasAvisos.id);
		for(int i=1;i<lenCte;i++)
		{
			if(!listCte[i].isEmpty)
			{
				cantPublicaciones=publicacion_contarCantidadAvisosxCliente(listP, lenP, listCte[i].id);
				if(cantdePublicacionesMax<cantPublicaciones)
				{
					cantdePublicacionesMax=cantPublicaciones;
					cteMasAvisos=listCte[i];
				}
			}

		}
		printf("CLIENTE CON MAS AVISOS  Cantidad de avisos: %d"
				"\n  ID\tlastName\t  Name\t\tCuit",cantdePublicacionesMax);
		cliente_imprimirUnCliente(&cteMasAvisos);
	}
	return r;
}
int informe_avisosPausados(sPublicacion* lista, int len)
{
	int r=-1;
	int cantAvisosPausados;
	if(lista!=NULL && len>0)
	{
		r=0;
		cantAvisosPausados=publicacion_contarActivasOpausadas(lista, len, 0);
		printf("\n la cantidad de Avisos Pausados es de: %d",cantAvisosPausados);
	}
	return r;
}
int informe_avisosActivos(sPublicacion* lista, int len)
{
	int r=-1;
	int cantAvisosActivos;
	if(lista!=NULL && len>0)
	{
		r=0;
		cantAvisosActivos=publicacion_contarActivasOpausadas(lista, len, 1);
		printf("\n la cantidad de Avisos Pausados es de: %d",cantAvisosActivos);
	}
	return r;
}
int informe_rubroConMasAvisos(sPublicacion* lista, int len)
{
	int r=-1;
	sRubro listRubros[len];
	sRubro aux;
	int rubroMas,rubroAct;
	rubro_init(listRubros, len);
	informe_cargarListaRubro(listRubros, lista, len);
	if(lista!=NULL && len>0)
	{
		r=0;
		aux=listRubros[0];
		rubroMas=publicacion_contarRubroConMasAvisos(lista, len, aux.numRubro);
		for(int i=1;i<len;i++)
		{
			if(listRubros[i].isEmpty==0)
			{
				rubroAct=publicacion_contarRubroConMasAvisos(lista, len, listRubros[i].numRubro);
				if(rubroMas<rubroAct)
				{
					rubroMas=rubroAct;
					aux=listRubros[i];
				}
			}
		}
		printf("\n RUBRO CON MAS AVISOS: %d      \nCANTIDAD DE AVISOS: %d",aux.numRubro,rubroMas);
	}
	return r;
}
int rubro_init(sRubro* lista, int len)
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
int informe_cargarListaRubro(sRubro* listaRubros, sPublicacion* listaP, int len)
{
	int r=-1;
	if(listaRubros!=NULL&& listaP!=NULL && len>0)
	{
		r=0;
		for(int i=0;i<len;i++)
		{
			if(rubro_noEstaEnlaLista(listaRubros, len, listaP[i].numRubro)&& listaP[i].isEmpty==0)
			{
				rubro_add(listaRubros, len, listaP[i].numRubro);
			}
		}
	}
	return r;
}
int rubro_noEstaEnlaLista(sRubro* lista, int len, int rubro)
{
	int r=-1;
	{
		for(int i=0;i<len;i++)
		{
			if(lista[i].numRubro==rubro)
			{
				r=0;
				break;
			}
		}
	}
	return r;
}
int rubro_buscarLibreUocupado(sRubro * lista, int len, int estado)
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
int rubro_add(sRubro* lista, int len, int rubro)
{
	int r=-1;
	int indice;
	if(lista!=NULL && len>0)
	{
		indice=rubro_buscarLibreUocupado(lista, len, 1);
		if(indice!=-1)
		{
			r=0;
			lista[indice].numRubro=rubro;
			lista[indice].isEmpty=0;
		}
	}
	return r;
}
