#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "utn.h"
int cliente_set_id(sCliente* this, int id)
{
  int r=-1;
  if(this!=NULL && cliente_isValid_id(id))
  {
	this->id=id;
	r=0;
  }
  return r;
}
int cliente_isValid_id(int id)
{
	int r=0;
	if(id>0)
	{
		r=1;
	}
	return r;
}
int cliente_set_nombre(sCliente* this, char* nombre)
{
  int r=-1;
  if(this!=NULL && cliente_isValid_nombre(nombre))
  {
	strcpy(this->nombre,nombre);
	r=0;
  }
  return r;
}
int cliente_isValid_nombre(char* nombre)
{
	int r=0;
	if(utn_soloLetras(nombre)!=-1)
	{
		r=1;
	}
	return r;
}
int cliente_set_apellido(sCliente* this, char* apellido)
{
  int r=-1;
  if(this!=NULL && cliente_isValid_apellido(apellido))
  {
	strcpy(this->apellido,apellido);
	r=0;
  }
  return r;
}
int cliente_isValid_apellido(char* apellido)
{
	int r=0;
	if(utn_soloLetras(apellido)!=-1)
	{
		r=1;
	}
	return r;
}
int cliente_set_cuit(sCliente* this, char* cuit)
{
  int r=-1;
  if(this!=NULL && cliente_isValid_cuit(cuit))
  {
	strcpy(this->cuit,cuit);
	r=0;
  }
  return r;
}
int cliente_isValid_cuit(char* cuit)
{
	int r=0;
	if(utn_esCuit(cuit)!=-1)
	{
		r=1;
	}
	return r;
}
sCliente* cliente_new()
{
	sCliente* nuevo=(sCliente*)malloc(sizeof(sCliente));
	return nuevo;
}
void cliente_delete(sCliente* this)
{
	free(this);
}
int cliente_get_id(sCliente* this)
{
  return this->id;
}
char* cliente_get_nombre(sCliente* this)
{
  return this->nombre;
}
char* cliente_get_apellido(sCliente* this)
{
  return this->apellido;
}
char* cliente_get_cuit(sCliente* this)
{
  return this->cuit;
}
sCliente* cliente_newConParametros(int id,char* nombre,char* apellido,char* cuit)
{
  int ok=1;
  sCliente* nuevo=cliente_new();
  if(nuevo!=NULL)
  {
	if(ok==1 && cliente_set_id(nuevo,id))
	{
		ok=0;
	}
	if(ok==1 && cliente_set_nombre(nuevo,nombre))
	{
		ok=0;
	}
	if(ok==1 && cliente_set_apellido(nuevo,apellido))
	{
		ok=0;
	}
	if(ok==1 && cliente_set_cuit(nuevo,cuit))
	{
		ok=0;
	}
 	if(ok!=1)
	{
		cliente_delete(nuevo);
		nuevo=NULL;
	}
  }
	return nuevo;
}
int cliente_imprimirUnElemento(sCliente* this)
{
	int r=-1;
	if(this!=NULL)
	{
		r=0;
		printf("%2d  %14s  %18s  %16s  \n",this->id,this->nombre,this->apellido,this->cuit);
	}
	return r;
}
int cliente_esCiertoId(void* this,void* this2)
{
	int r=0;
	int aux2=*((int*)this2);
	sCliente* aux=(sCliente*)this;
	if(this!=NULL)
	{
		if(aux->id == aux2)
		{
			r=1;
		}
	}
	return r;
}
int cliente_generarId(int ref)
{
	static int id=0;
	id=id+ref;
	id++;
	return id;
}
int cliente_imprimirUnElemento_conMap(void* this)
{
	int r=-1;
	if(this!=NULL)
	{
		r=0;
		printf("%2d  %14s  %18s  %16s  \n",((sCliente*)this)->id,((sCliente*)this)->nombre,((sCliente*)this)->apellido,((sCliente*)this)->cuit);
	}
	return r;
}
int cliente_esCuitX(void* this,void* this2)
{
	int r=0;
	sCliente* aux=(sCliente*)this;
	char* cuit=(char*)this2;
	if(this!=NULL && this2!=NULL)
	{
		if(strcmp(cliente_get_cuit(aux),cuit)==0)
		{
			r=1;
		}
	}
	return r;
}
int cliente_esIdX(void* this,void* this2)
{
	int r=0;
	sCliente* aux=(sCliente*)this;
	int aux2=*((int*)this2);
	if(this!=NULL && this2!=NULL)
	{
		if(cliente_get_id(aux)==aux2)
		{
			r=1;
		}
	}
	return r;
}

