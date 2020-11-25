#ifndef CLIENTE_H_
#define CLIENTE_H_
typedef struct{
	int id;
	char nombre[60];
	char apellido[60];
	char cuit[60];
}sCliente;
int cliente_set_id(sCliente* this, int id);
int cliente_isValid_id(int id);
int cliente_set_nombre(sCliente* this, char* nombre);
int cliente_isValid_nombre(char* nombre);
int cliente_set_apellido(sCliente* this, char* apellido);
int cliente_isValid_apellido(char* apellido);
int cliente_set_cuit(sCliente* this, char* cuit);
int cliente_isValid_cuit(char* cuit);
sCliente* cliente_new();
void cliente_delete(sCliente* this);
int cliente_get_id(sCliente* this);
char* cliente_get_nombre(sCliente* this);
char* cliente_get_apellido(sCliente* this);
char* cliente_get_cuit(sCliente* this);
sCliente* cliente_newConParametros(int id,char* nombre,char* apellido,char* cuit);
int cliente_imprimirUnElemento(sCliente* this);
int cliente_esCiertoId(void* this,void* this2);
int cliente_generarId(int ref);
int cliente_imprimirUnElemento_conMap(void* this);
int cliente_esCuitX(void* this,void* this2);
int cliente_esIdX(void* this,void* this2);


#endif /* CLIENTE_H_ */
