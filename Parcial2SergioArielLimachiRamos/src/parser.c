#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "cliente.h"
#include "afiche.h"

/** \brief Parsea los datos los datos de los clientes desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_clienteFromText(FILE* pFile , LinkedList* pArray)
{
	sCliente* nuevo;
	char aux1[900],aux2[900],aux3[900],aux4[900];
	int r=0;
	if(pFile!=NULL && pArray!=NULL)
	{
		fscanf(pFile,"%[^\n]\n",aux1);
		do{
			r=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",aux1,aux2,aux3,aux4);
			if(r==4)
			{
				nuevo=cliente_newConParametros(atoi(aux1), aux2, aux3, aux4);
				if(nuevo!=NULL)
				{
					ll_add(pArray, nuevo);
				}
				else{
					printf("error al guardar\n");
				}
			}
		}while(feof(pFile)==0);
		r=1;
	}
    return r;
}
int parser_aficheFromText(FILE* pFile , LinkedList* pArray)
{
	sAfiche* nuevo;
	char aux1[900],aux2[900],aux3[900],aux4[900],aux5[900],aux6[900];
	int r=0;
	if(pFile!=NULL && pArray!=NULL)
	{
		fscanf(pFile,"%[^\n]\n",aux1);
		do{
			r=fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",aux1,aux2,aux3,aux4,aux5,aux6);
			if(r==6)
			{
				nuevo=afiche_newConParametros(atoi(aux1), atoi(aux2), atoi(aux3), aux4, aux5, atoi(aux6));
				if(nuevo!=NULL)
				{
					ll_add(pArray, nuevo);
				}
				else{
					printf("error al guardar\n");
				}
			}
		}while(feof(pFile)==0);
		r=1;
	}
    return r;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
/*int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	sEnvio* nuevo;
	int r=-1;

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		do{
			nuevo=envio_new();
			if(nuevo!=NULL && fread(nuevo,sizeof(sEnvio),1,pFile)==1)
			{
				ll_add(pArrayListEmployee,nuevo);
			}
			else{
				envio_delete(nuevo);
			}
		}while(feof(pFile)==0);
		r=0;
	}
    return r;
}*/
