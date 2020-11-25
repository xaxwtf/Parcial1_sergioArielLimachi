/*
 * control.h
 *
 *  Created on: 22 nov. 2020
 *      Author: roid
 */

#ifndef CONTROL_H_
#define CONTROL_H_
int control_alta_cliente(LinkedList* lista);
int control_listar_clientes(LinkedList* lista);
int control_elCuitNoEstaRepedito(LinkedList* lista,char* cuit);
int control_afiche_idClienteEsta(LinkedList* lista,int idCte);
int control_vender_afiche(LinkedList* clientes, LinkedList* afiches);

int control_listar_afiches(LinkedList* lista);
int control_modificar_ventaAfiche(LinkedList* afiches,LinkedList* clientes);
int control_cobrar_ventaAfiche(LinkedList* afiches, LinkedList* clientes);

int control_cargar_datosDesdeArchivo(LinkedList* afiches, char* patch,int(*pFunc)(FILE*,LinkedList*));
int control_guardar_clientesEnArchivoText(LinkedList* lista,char* patch);
int control_guardar_afichesEnArchivoText(LinkedList* lista,char* patch);

int control_generar_informeCobros(LinkedList* clientes,LinkedList* afiches,char* patch);
int control_generar_informeDeudas(LinkedList* clientes,LinkedList* afiches,char* patch);

int control_generar_Estadisticas(LinkedList* clientes,LinkedList* afiches);

int control_calcularCantidadMaxdeAfichesCobradosdeLalistaxCliente(LinkedList* clientes, LinkedList* ventas ,int* resultado);
int control_calcularCantidadMindeAfichesCobradosdeLalistaxCliente(LinkedList* clientes, LinkedList* ventas ,int* resultado);

int control_buscarCantidadMaximadeAfichesxVenta(LinkedList* ventas, int* resultado);

#endif /* CONTROL_H_ */
