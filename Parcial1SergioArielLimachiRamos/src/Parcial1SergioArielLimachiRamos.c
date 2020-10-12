/*
 ============================================================================
 Name        : Parcial1SergioArielLimachiRamos.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "publicacion.h"
#include "informe.h"
#define TAM_ctes 100
#define TAM_pub 1000

int main(void) {
	sCliente clientes[TAM_ctes];
	sPublicacion publicaciones[TAM_pub];
	int opc=123;
	publicacion_init(publicaciones, TAM_pub);
	cliente_init(clientes, TAM_ctes);
	Cliente_forzar5elementos(clientes, TAM_ctes);
	do{
		utn_getInt("\n-----Parcial-----"
					"\n 1-Alta cliente"
					"\n 2-Modificar datos de Cliente"
					"\n 3-Baja de Cliente"
					"\n 4-Publicar"
					"\n 5-Pausar Publicacion"
					"\n 6-Reanudar Publicacion"
					"\n 7-Imprimir Clientes"
					"\n 8-Informar"
					"\n 0-salir", "error,la opcion indicada no es valido", &opc, 1, 8, 0);
			switch(opc)
			{
				case 1:
					cliente_alta(clientes, TAM_ctes);
					break;
				case 2:
					if(cliente_buscarLibreUocupado(clientes, TAM_ctes, 0)!=-1)
					{
						cliente_modificar(clientes, TAM_ctes);
					}
					else{
						printf("error, no hay datos Cargados");
					}
					break;
				case 3:
					if(cliente_buscarLibreUocupado(clientes, TAM_ctes, 0)!=-1)
					{
						cliente_baja(clientes, TAM_ctes, publicaciones, TAM_pub);
					}
					else{
						printf("error, no hay datos Cargados");
					}
					break;
				case 4:
					if(cliente_buscarLibreUocupado(clientes, TAM_ctes, 0)!=-1)
					{
						publicar(publicaciones, TAM_pub, clientes, TAM_ctes);
					}
					else{
						printf("\nerror, no hay datos Cargados");
					}
					break;
				case 5:
					if(publicacion_buscarLibreUocupado(publicaciones, TAM_pub, 0)!=-1)
					{
						publicacion_pausar(publicaciones, TAM_pub);
					}
					else{
						printf("\nError, no hay datos cargados");
					}
					break;
				case 6:
					if(publicacion_buscarLibreUocupado(publicaciones, TAM_pub, 0)!=-1)
					{
						publicacion_reanudar(publicaciones, TAM_pub);
					}
					else{
						printf("\nError, no hay datos cargados");
					}
					break;
				case 7:
					if(cliente_buscarLibreUocupado(clientes, TAM_ctes, 0)!=-1)
					{
						cliente_listar(clientes, TAM_ctes, publicaciones, TAM_pub);
					}
					else{
						printf("\n Error, no hay datos Cargados");
					}

					break;
				case 8:
					if(publicacion_buscarLibreUocupado(publicaciones, TAM_pub, 0)!=-1)
					{
						informar(clientes, TAM_ctes, publicaciones, TAM_pub);
					}
					else{
						printf("\nno hay datos Cargados");
					}

					break;
			}
	}while(opc!=0);
	return EXIT_SUCCESS;
}
