/*
 ============================================================================
 Name        : Parcial2SergioArielLimachiRamos.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "utn.h"
#include "control.h"
#include "parser.h"
int main(void) {
	int opc;
	LinkedList* clientes;
	LinkedList* afiches;
	clientes=ll_newLinkedList();
	afiches=ll_newLinkedList();
	control_cargar_datosDesdeArchivo(clientes, "clientes.csv", parser_clienteFromText);
	control_cargar_datosDesdeArchivo(afiches, "ventas.csv", parser_aficheFromText);
	do{
		utn_getInt("PARCIAL II\n"
				"1-Alta Usuario.\n"
				"2-Vender afiches\n"
				"3-Modificar venta\n"
				"4-Cobrar venta\n"
				"5-Generar informe de cobros\n"
				"6-Generar informe de deudas\n"
				"7-Generar estadísticas\n"
				"8-guardar los cambios en archivo", "Error,la opcion indicada no es valida", &opc, 1, 999, 1);
		switch(opc)
		{
			case 1:
				control_alta_cliente(clientes);
				//control_guardar_clientesEnArchivoText(clientes, "clientes.csv");
				break;
			case 2:
				if(ll_isEmpty(clientes))
				{
					printf("No hay cliente cargados!!!\n");
				}
				else{
					control_vender_afiche(clientes, afiches);
					//control_guardar_afichesEnArchivoText(afiches, "ventas.csv");
				}
				break;
			case 3:
				if(ll_isEmpty(afiches))
				{
					printf("no hay datos cargados!!!\n");
				}
				else{
					control_modificar_ventaAfiche(afiches, clientes);
					//control_guardar_afichesEnArchivoText(afiches, "ventas.csv");

				}
				break;
			case 4:
				if(ll_isEmpty(afiches))
				{
					printf("no hay datos cargados!!!\n");
				}
				else{
					control_cobrar_ventaAfiche(afiches, clientes);
					//control_guardar_afichesEnArchivoText(afiches, "ventas.csv");
				}

				break;
			case 5:
				if(ll_isEmpty(clientes))
				{
					printf("no hay datos cargados!!!\n");
				}
				else{
					control_generar_informeCobros(clientes, afiches, "Ventas_Cobradas.csv");
				}
				break;
			case 6:
				if(ll_isEmpty(clientes))
				{
					printf("no hay datos cargados!!!\n");
				}
				else{
					control_generar_informeDeudas(clientes, afiches, "Ventas_ACobrar.csv");
				}
				break;
			case 7:
				if(ll_isEmpty(clientes)||ll_isEmpty(afiches))
				{
					printf("no hay datos  suficientes cargados!!!\n");
				}
				else{
					control_generar_Estadisticas(clientes, afiches);
				}
				break;
			case 8:
				control_guardar_afichesEnArchivoText(afiches, "ventas.csv");
				control_guardar_clientesEnArchivoText(clientes, "clientes.csv");
				break;
			case 9:
				control_listar_clientes(clientes);
				break;

		}
	}while(opc!=0);
	return EXIT_SUCCESS;
}
