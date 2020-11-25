#ifndef AFICHE_H_
#define AFICHE_H_

typedef struct{
	int id;
	int idCliente;
	int cantAfiches;
	char dirImagen[60];
	char zona[60];
	int estado;
}sAfiche;
int afiche_set_id(sAfiche* this, int id);
int afiche_isValid_id(int id);
int afiche_set_idCliente(sAfiche* this, int idCliente);
int afiche_isValid_idCliente(int idCliente);
int afiche_set_cantAfiches(sAfiche* this, int cantAfiches);
int afiche_isValid_cantAfiches(int cantAfiches);
int afiche_set_dirImagen(sAfiche* this, char* dirImagen);
int afiche_isValid_dirImagen(char* dirImagen);
int afiche_set_zona(sAfiche* this, char* zona);
int afiche_isValid_zona(char* zona);
int afiche_set_estado(sAfiche* this, int estado);
int afiche_isValid_estado(int estado);
sAfiche* afiche_new();
void afiche_delete(sAfiche* this);
int afiche_get_id(sAfiche* this);
int afiche_get_idCliente(sAfiche* this);
int afiche_get_cantAfiches(sAfiche* this);
char* afiche_get_dirImagen(sAfiche* this);
char* afiche_get_zona(sAfiche* this);
int afiche_get_estado(sAfiche* this);
sAfiche* afiche_newConParametros(int id,int idCliente,int cantAfiches,char* dirImagen,char* zona,int estado);
int afiche_imprimirUnElemento(sAfiche* this);
int afiche_generarId(int ref);
int afiche_imprimirUnElemento_conMap(void* this);
int afiche_esCiertoId(void* this, void* this2);
int afiche_cobrar_buscandoxId(void* this,void* this2);
int afiche_imprimirUnElemento_conMap_soloSies_aCobrar(void* this);
int afiche_esCiertoIdCliente(void* this,void* this2);
int afiche_esCiertoIdClienteYestaCobrado(void* this,void* this2);
int afiche_esCiertoIdClienteYesAcobrar(void* this,void* this2);




#endif /* AFICHE_H_ */
