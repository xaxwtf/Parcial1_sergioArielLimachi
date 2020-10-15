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

/**
 * /brief imprime un menu de informes y imprime los resultados
 * /param sCliente* es el array de cliente
 * /param int es el tamaño del array de cliente
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
void informar(sCliente* listaCte, int lenCte, sPublicacion* listaPub, int lenP)
{
	int opc=123;
	do{
		utn_getInt("\nINFORMES"
				"\n1-Cliente con más avisos."
				"\n2-Cantidad de avisos pausados."
				"\n3-Rubro con mas avisos."
				"\n4-Cliente con más avisos Activos"
				"\n5-Cliente con más avisos Pausados."
				"\n6-Atras", "\nla opcion indicada no es valida", &opc, 1, 6, 1);
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
				case 4:
					informe_clienteConMasAvisosActivosUPausados(listaPub, lenP, listaCte, lenCte, 1);
					break;
				case 5:
					informe_clienteConMasAvisosActivosUPausados(listaPub, lenP, listaCte, lenCte, 0);
					break;
			}
	}while(opc!=6);

}
/**
 * /brief imprime al cliente Con mas avisos
 * /param sCliente* es el array de cliente
 * /param int es el tamaño del array de cliente
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
int informe_buscarClienteconmasAvisos(sCliente* listCte, int lenCte, sPublicacion* listP, int lenP)
{
	int r=-1;
	sCliente cteMasAvisos;
	int cantdePublicacionesMax,cantPublicaciones;
	if(listCte!=NULL && listP!=NULL && lenCte>0 &&lenP>0)
	{
		r=0;
		cteMasAvisos=listCte[0];
		cantdePublicacionesMax=publicacion_contarCantidadAvisosPausadosuActivoxCliente(listP, lenP, listCte[0].id, 3);
		for(int i=1;i<lenCte;i++)
		{
			if(!listCte[i].isEmpty)
			{
				cantPublicaciones=publicacion_contarCantidadAvisosPausadosuActivoxCliente(listP, lenP, listCte[0].id, 3);
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

/**
 * /brief imprime la cantidad de publicaciones en estado Pausado
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
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

/**
 * /brief imprime la cantidad de publicacion en estado Activa
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
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
/**
 * /brief imprime el Rubro con mas Avisos y la Cantidad de avisos
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
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
/**
 * /brief inicializa el array de rubro isEmpty(1)
 * /param sRubro* es el array de rubro
 * /param int es el tamaño del array
 *
 * /return (-1)error (0)OK
 *
 */
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
/**
 * /brief carga la lista de rubros
 * /param sRubro* ese el array de rubro
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 *
 * /return (-1)error (0)OK
 *
 */
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

/**
 * /brief valida si un rubro ya esta en la lista
 * /param sRubro* es el array de rubro
 * /param int es el tamaño del array
 * /param int es el rubro del cual se pregunta si esta o no en la lista
 *
 * /return (-1)NO esta (0)SI esta
 *
 */
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
/**
 * /brief busca una pocicion libre u ocupada en el array de rubros y lo retorna
 * /param sRubro* es el array de rubro
 * /param int es el tamaño del array
 * /param int es el lo que buscara en el array (1)libre (0)ocupado
 *
 * /return (-1)error (el indice en el cual encontro la 1ra ocurrencia)OK
 *
 */
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


/**
 * /brief agrega un rubro a al array
 * /param sRubro* es el array de rubro
 * /param int es el tamaño del array
 * /param int es el numero de rubro
 *
 * /return (-1)error (0)OK
 *
 */
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

/**
 * /brief realiza el alta de una publicacion
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 * /param sCliente* es el array de cliente
 * /param int es el tamaño del array de cliente
 *
 * /return (-1)error (0)OK
 *
 */
int publicar(sPublicacion* lista, int len, sCliente* listaCte, int lenCte)
{
	int r=-1;
	int todoOk=1;
	sPublicacion aux;
	if(lista!=NULL && len>0)
	{
		if(publicacion_buscarLibreUocupado(lista, len,1)!=-1)
		{
			cliente_listar(listaCte, lenCte, lista, len);
			if(todoOk==1 && (utn_getInt("\nindique un ID de algun Cliente","\nerror, el tipo no es valido", &aux.idCliente, 3, 1000, 1)|| cliente_buscarOcurrenciaId(listaCte, lenCte,aux.idCliente, &aux.numRubro)))
			{
				todoOk=0;
			}
			if(todoOk==1 && (utn_getInt("\nindique el Numero de Rubro:", "\nerror,rubro no valido", &aux.numRubro, 3, 999999999, 1)))
			{
				todoOk=0;
			}
			if(todoOk==1 && (utn_pedirCadenadeUndeunDeterminadoTam(aux.textodeAviso, "\nindique el Texto(no debe supera los 63 Caracteres):", 3, 63, 1)))
			{
				todoOk=0;
			}
			if(todoOk)
			{
				r=0;
				aux.id=publicacion_generarId();
				publicacion_add(lista, len,aux.id , aux.idCliente, aux.numRubro, aux.textodeAviso);
				printf("\n Su Numero de ID es: %d",aux.id);
			}
		}
		else{
			printf("\n !!!!Registro lleno, no se pueden cargar mas empleados");
		}
	}
	return r;
}

/**
 * /brief imprime al cliente con mas avisos pausados o activos y la cantidad de avisos que posee
 * /param sPublicacion* es el array de publicacion
 * /param int es el tamaño del array de publicacion
 * /param sCliente* es el array de cliente
 * /param int es el tamaño del array de cliente
 * /param int es lo que se busca y se querra imprimir (1)Activa (0)Pausada
 *
 * /return (-1)error (0)OK
 *
 */
int informe_clienteConMasAvisosActivosUPausados(sPublicacion* listaP,int lenP, sCliente* listaCte, int lenCte, int estadoAbuscar)
{
	int r=-1;
	int cantAvisosMax,cantAvisoAct;
	sCliente aux;
	if(listaP!=NULL&& listaCte!=NULL && lenCte>0 &&lenP && (estadoAbuscar==0 || estadoAbuscar==1))
	{
		r=0;
		aux=listaCte[0];
		cantAvisosMax=publicacion_contarCantidadAvisosPausadosuActivoxCliente(listaP, lenP, listaCte[0].id, estadoAbuscar);
		for(int i=1;i<lenCte;i++)
		{
			cantAvisoAct=publicacion_contarCantidadAvisosPausadosuActivoxCliente(listaP, lenP, listaCte[i].id, estadoAbuscar);
			if(cantAvisoAct>cantAvisosMax)
			{
				aux=listaCte[i];
				cantAvisosMax=cantAvisoAct;
			}
		}
		if(estadoAbuscar&& cantAvisosMax>0)
		{
			printf("\nel Cliente con mas Avisos Activos:   Cantidad De avisos %d",cantAvisosMax);
			cliente_imprimirUnCliente(&aux);
		}
		else if(cantAvisosMax>0){
			printf("\nel Cliente con mas Avisos Pausados:   Cantidad De avisos %d",cantAvisosMax);
			cliente_imprimirUnCliente(&aux);
		}
		else if(estadoAbuscar==1){
			printf("\nno hay Publicaciones Activas");
		}
		else{
			printf("\nno hay Publicaciones Pausadas");
		}
	}
	return r;
}
