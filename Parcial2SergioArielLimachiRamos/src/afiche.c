#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "afiche.h"
int afiche_set_id(sAfiche* this, int id)
{
  int r=-1;
  if(this!=NULL && afiche_isValid_id(id))
  {
	this->id=id;
	r=0;
  }
  return r;
}
int afiche_isValid_id(int id)
{
	int r=0;
	if(id>0)
	{
		r=1;
	}
	return r;
}
int afiche_set_idCliente(sAfiche* this, int idCliente)
{
  int r=-1;
  if(this!=NULL && afiche_isValid_idCliente(idCliente))
  {
	this->idCliente=idCliente;
	r=0;
  }
  return r;
}
int afiche_isValid_idCliente(int idCliente)
{
	int r=0;
	if(idCliente>0)
	{
		r=1;
	}
	return r;
}
int afiche_set_cantAfiches(sAfiche* this, int cantAfiches)
{
  int r=-1;
  if(this!=NULL && afiche_isValid_cantAfiches(cantAfiches))
  {
	this->cantAfiches=cantAfiches;
	r=0;
  }
  return r;
}
int afiche_isValid_cantAfiches(int cantAfiches)
{
	int r=0;
	if(cantAfiches>0)
	{
		r=1;
	}
	return r;
}
int afiche_set_dirImagen(sAfiche* this, char* dirImagen)
{
  int r=-1;
  if(this!=NULL && afiche_isValid_dirImagen(dirImagen))
  {
	strcpy(this->dirImagen,dirImagen);
	r=0;
  }
  return r;
}
int afiche_isValid_dirImagen(char* dirImagen)
{
	return 1;
}
int afiche_set_zona(sAfiche* this, char* zona)
{
  int r=-1;
  if(this!=NULL && afiche_isValid_zona(zona))
  {
	strcpy(this->zona,zona);
	r=0;
  }
  return r;
}
int afiche_isValid_zona(char* zona)
{
	int r=0;
	if(zona!=NULL)
	{
		if(strcmp(zona,"CABA")==0||strcmp(zona,"ZONA SUR")==0|| strcmp(zona,"ZONA OESTE")==0)
		{
			r=1;
		}
	}
	return r;
}
int afiche_set_estado(sAfiche* this, int estado)
{
  int r=-1;
  if(this!=NULL && afiche_isValid_estado(estado))
  {
	this->estado=estado;
	r=0;
  }
  return r;
}
int afiche_isValid_estado(int estado)
{
	int r=0;
	if(estado==1 || estado==0)
	{
		r=1;
	}
	return r;
}
sAfiche* afiche_new()
{
	sAfiche* nuevo=(sAfiche*)malloc(sizeof(sAfiche));
	return nuevo;
}
void afiche_delete(sAfiche* this)
{
	free(this);
}
int afiche_get_id(sAfiche* this)
{
  return this->id;
}
int afiche_get_idCliente(sAfiche* this)
{
  return this->idCliente;
}
int afiche_get_cantAfiches(sAfiche* this)
{
  return this->cantAfiches;
}
char* afiche_get_dirImagen(sAfiche* this)
{
  return this->dirImagen;
}
char* afiche_get_zona(sAfiche* this)
{
  return this->zona;
}
int afiche_get_estado(sAfiche* this)
{
  return this->estado;
}
sAfiche* afiche_newConParametros(int id,int idCliente,int cantAfiches,char* dirImagen,char* zona,int estado)
{
  int ok=1;
  sAfiche* nuevo=afiche_new();
  if(nuevo!=NULL)
  {
	if(ok==1 && afiche_set_id(nuevo,id))
	{
		ok=0;
	}
	if(ok==1 && afiche_set_idCliente(nuevo,idCliente))
	{
		ok=0;
	}
	if(ok==1 && afiche_set_cantAfiches(nuevo, cantAfiches))
	{
		ok=0;
	}
	if(ok==1 && afiche_set_dirImagen(nuevo,dirImagen))
	{
		ok=0;
	}
	if(ok==1 && afiche_set_zona(nuevo,zona))
	{
		ok=0;
	}
	if(ok==1 && afiche_set_estado(nuevo,estado))
	{
		ok=0;
	}
 	if(ok!=1)
	{
		afiche_delete(nuevo);
		nuevo=NULL;
	}
  }
	return nuevo;
}
int afiche_imprimirUnElemento(sAfiche* this)
{
	int r=-1;
	if(this!=NULL)
	{
		if(this->estado==0)
		{
			printf(" %d  %5d      %6d   %13s  %10s    A cobrar  ",this->id,this->idCliente,this->cantAfiches,this->dirImagen,this->zona);
		}
		else{
			printf(" %d  %5d      %6d   %13s  %10s    Cobrado  ",this->id,this->idCliente,this->cantAfiches,this->dirImagen,this->zona);
		}
		r=0;

	}
	return r;
}
int afiche_generarId(int ref)
{
	static int id=0;
	id=id+ref;
	id++;
	return id;
}
int afiche_imprimirUnElemento_conMap(void* this)
{
	int r=-1;
	if(this!=NULL)
	{
		r=0;
		if(((sAfiche*)this)->estado==0)
		{
			printf(" %d  %5d      %6d   %13s  %10s    A cobrar  \n",((sAfiche*)this)->id,((sAfiche*)this)->idCliente,((sAfiche*)this)->cantAfiches,((sAfiche*)this)->dirImagen,((sAfiche*)this)->zona);
		}
		else{
			printf(" %d  %5d      %6d   %13s  %10s    COBRADO  \n",((sAfiche*)this)->id,((sAfiche*)this)->idCliente,((sAfiche*)this)->cantAfiches,((sAfiche*)this)->dirImagen,((sAfiche*)this)->zona);

		}
	}
	return r;
}
int afiche_esCiertoId(void* this, void* this2)
{
	int r=0;
	sAfiche* aux=(sAfiche*)this;
	int id=*((int*)this2);
	if(this!=NULL && this2!=NULL)
	{
		if(afiche_get_id(aux)==id)
		{
			r=1;
		}
	}
	return  r;
}
int afiche_cobrar_buscandoxId(void* this,void* this2)
{
	int r=0;
	sAfiche* aux=(sAfiche*)this;
	int id=*((int*)this2);
	if(this!=NULL && this2!=NULL)
	{
		if(afiche_get_id(aux)==id)
		{
			r=1;
		}
	}
	return  r;
}
int afiche_imprimirUnElemento_conMap_soloSies_aCobrar(void* this)
{
	int r=-1;
	if(this!=NULL && (((sAfiche*)this)->estado)==0)
	{
		r=0;
		printf(" %d  %5d      %6d   %13s  %10s    A cobrar  \n",((sAfiche*)this)->id,((sAfiche*)this)->idCliente,((sAfiche*)this)->cantAfiches,((sAfiche*)this)->dirImagen,((sAfiche*)this)->zona);
	}
	return r;
}
int afiche_esCiertoIdCliente(void* this,void* this2)
{
	int r=0;
	sAfiche* aux=(sAfiche*)this;
	int id=*((int*)this2);
	if(this!=NULL && this2!=NULL)
	{
		if(afiche_get_idCliente(aux)==id)
		{
			r=1;
		}
	}
	return  r;
}
int afiche_esCiertoIdClienteYestaCobrado(void* this,void* this2)
{
	int r=0;
	sAfiche* aux=(sAfiche*)this;
	int id=*((int*)this2);
	if(this!=NULL && this2!=NULL)
	{
		if(afiche_get_idCliente(aux)==id&& afiche_get_estado(aux)==1)
		{
			r=afiche_get_cantAfiches(aux);
		}
	}
	return  r;
}
int afiche_esCiertoIdClienteYesAcobrar(void* this,void* this2)
{
	int r=0;
	sAfiche* aux=(sAfiche*)this;
	int id=*((int*)this2);
	if(this!=NULL && this2!=NULL)
	{
		if(afiche_get_idCliente(aux)==id&& afiche_get_estado(aux)==0)
		{
			r=1;
		}
	}
	return  r;
}
