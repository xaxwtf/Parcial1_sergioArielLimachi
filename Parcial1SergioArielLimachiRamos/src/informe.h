/*
 * informe.h
 *
 *  Created on: 11 oct. 2020
 *      Author: roid
 */

#ifndef INFORME_H_
#define INFORME_H_
typedef struct{
	int isEmpty;
	int numRubro;
}sRubro;

void informar(sCliente* listaCte, int lenCte, sPublicacion* listaPub, int lenP);
int informe_buscarClienteconmasAvisos(sCliente* listCte, int lenCte, sPublicacion* listP, int lenP);
int informe_avisosPausados(sPublicacion* lista, int len);
int informe_avisosActivos(sPublicacion* lista, int len);
int rubro_init(sRubro* lista, int len);
int rubro_noEstaEnlaLista(sRubro* lista, int len, int rubro);
int informe_cargarListaRubro(sRubro* listaRubros, sPublicacion* listaP, int len);
int rubro_buscarLibreUocupado(sRubro * lista, int len, int estado);
int rubro_add(sRubro* lista, int len, int rubro);
int informe_rubroConMasAvisos(sPublicacion* lista, int len);
///publicar esta aca por que en publicacion.h me tira error
int publicar(sPublicacion* lista, int len, sCliente* listaCte, int lenCte);

#endif /* INFORME_H_ */
