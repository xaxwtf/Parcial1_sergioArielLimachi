/*
 * informe.h
 *
 *  Created on: 26 nov. 2020
 *      Author: roid
 */

#ifndef INFORME_H_
#define INFORME_H_

int informe_generar_Estadisticas(LinkedList* clientes,LinkedList* afiches);

int informe_calcularCantidadMaxdeAfichesCobradosdeLalistaxCliente(LinkedList* clientes, LinkedList* ventas ,int* resultado);
int informe_calcularCantidadMindeAfichesCobradosdeLalistaxCliente(LinkedList* clientes, LinkedList* ventas ,int* resultado);

int informe_buscarCantidadMaximadeAfichesxVenta(LinkedList* ventas, int* resultado);



#endif /* INFORME_H_ */
