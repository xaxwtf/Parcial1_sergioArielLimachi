/*
 * informe.c
 *
 *  Created on: 26 nov. 2020
 *      Author: roid
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "cliente.h"
#include "afiche.h"
int informe_generar_Estadisticas(LinkedList* clientes,LinkedList* afiches)
{
	int r=-1;
	int max,min,aux,cantAMax,indice;
	sCliente* clienteAux;
	sAfiche* aficheAux;
	if(clientes!=NULL && afiches!=NULL)
	{
		r=0;
		informe_calcularCantidadMaxdeAfichesCobradosdeLalistaxCliente(clientes, afiches, &max);
		informe_calcularCantidadMindeAfichesCobradosdeLalistaxCliente(clientes, afiches, &min);
		informe_buscarCantidadMaximadeAfichesxVenta(afiches, &cantAMax);
		printf("\nCliente al que mas afiches se le ha cobrado   CANT. AFICHES: %d \n"
				"ID \tNOMBRE \t APELLIDO \tCUIT\n",max);
		for(int i=0;i<ll_len(clientes);i++)
		{
			clienteAux=(sCliente*)ll_get(clientes, i);
			ll_reduceIntII(afiches, afiche_esCiertoIdClienteYestaCobrado, &clienteAux->id, &aux);
			if(max==aux)
			{
				cliente_imprimirUnElemento(clienteAux);
			}
		}
		printf("\nCliente al que menos afiches se le ha cobrado   CANT. AFICHES: %d \n"
						"ID     NOMBRE       APELLIDO      CUIT\n",min);
		for(int i=0;i<ll_len(clientes);i++)
		{
			clienteAux=(sCliente*)ll_get(clientes, i);
			ll_reduceIntII(afiches, afiche_esCiertoIdClienteYestaCobrado, &clienteAux->id, &aux);
			if(min==aux)
			{
				cliente_imprimirUnElemento(clienteAux);
			}
		}
		printf("VENTA CON MAS AFICHES VENDIDOS: CANT. AFICHES: %d\n",cantAMax);
		for(int i=0;i<ll_len(afiches);i++)
		{
			aficheAux=(sAfiche*)ll_get(afiches, i);
			if(afiche_get_cantAfiches(aficheAux)==cantAMax)
			{
				indice=ll_search(clientes, cliente_esCiertoId, &aficheAux->idCliente);
				clienteAux=ll_get(clientes, indice);
				printf("id_Venta %d\n"
						"cuit_Cliente: %s\n"
						"\\\\\\\\\\\\\\\\\\\n",afiche_get_id(aficheAux),cliente_get_cuit(clienteAux));
			}
		}

	}
	return r;
}
int informe_calcularCantidadMaxdeAfichesCobradosdeLalistaxCliente(LinkedList* clientes, LinkedList* ventas ,int* resultado)
{
	int r=-1;
	sCliente* aux;
	int max,act;
	if(clientes!=NULL && ventas!=NULL)
	{
		aux=ll_get(clientes, 0);
		ll_reduceIntII(ventas, afiche_esCiertoIdClienteYestaCobrado,&aux->id, &max);
		for(int i=1;i<ll_len(clientes);i++)
		{
			aux=ll_get(clientes, i);
			ll_reduceIntII(ventas, afiche_esCiertoIdClienteYestaCobrado,&aux->id, &act);
			if(act>max)
			{
				max=act;
			}
		}
		*resultado=max;
		r=0;
	}
	return r;
}
int informe_calcularCantidadMindeAfichesCobradosdeLalistaxCliente(LinkedList* clientes, LinkedList* ventas ,int* resultado)
{
	int r=-1;
	sCliente* aux;
	int min,act;
	int noEncontreMin=1;
	if(clientes!=NULL && ventas!=NULL)
	{
		for(int i=0;i<ll_len(clientes);i++)
		{
			aux=ll_get(clientes, i);
			ll_reduceIntII(ventas, afiche_esCiertoIdClienteYestaCobrado,&aux->id, &act);
			if(noEncontreMin==1 && act>0)
			{
				noEncontreMin=0;
				min=act;
			}
			else if(noEncontreMin==0 && act<min && act>0)
			{
				min=act;
			}
		}
		*resultado=min;
		r=0;
	}
	return r;
}
int informe_buscarCantidadMaximadeAfichesxVenta(LinkedList* ventas, int* resultado)
{
	int r=-1;
	int max;
	sAfiche* pAfiche;
	if(ventas!=NULL)
	{
		pAfiche=(sAfiche*)ll_get(ventas, 0);
		max=afiche_get_cantAfiches(pAfiche);
		for(int i=1;i<ll_len(ventas);i++)
		{
			pAfiche=(sAfiche*)ll_get(ventas, i);
			if(afiche_get_cantAfiches(pAfiche)>max)
			{
				max=afiche_get_cantAfiches(pAfiche);
			}
		}
		*resultado=max;
		r=0;
	}
	return r;
}
