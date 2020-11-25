#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this=(LinkedList*)malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
    	this->size=0;
    	this->pFirstNode=NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux=this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode = NULL;
	Node* nAct;
	Node* nAnt;
	if(this!=NULL && nodeIndex>=0 && nodeIndex<this->size)
	{
		if(nodeIndex==0)
		{
		   pNode=this->pFirstNode;
		}
		else
		{
			nAct=this->pFirstNode;
			while(nodeIndex>0)
		    {
				nAnt=nAct;
				nAct=nAnt->pNextNode;
		        nodeIndex--;
		    }
		  pNode=nAct;
		}
	}
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNode;
    Node* nAnt;
    Node* nAct;
    Node* nAux;
    if(this!=NULL && nodeIndex>=0 && nodeIndex<=this->size)
    {
    	pNode=(Node*)malloc(sizeof(Node));
    	if(pNode!=NULL)
    	{
    		if(nodeIndex==0)
    		{
    		   nAux=this->pFirstNode;
    		   this->pFirstNode=pNode;
    		   pNode->pNextNode=nAux;
    		   pNode->pElement=pElement;
    		}
    		else{
    		   nAct=this->pFirstNode;
    		   while(nodeIndex>1)
    		   {
    			   nAnt=nAct;
    			   nAct=nAnt->pNextNode;
    			   nodeIndex--;
    		   }
    		   nAux=nAct->pNextNode;;
    		   nAct->pNextNode=pNode;
    		   pNode->pElement=pElement;
    		   pNode->pNextNode=nAux;
    		}
    		this->size++;
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux=addNode(this,this->size, pElement);
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* aux;
    if(this!=NULL && index>=0 && index < this->size)
    {
    	aux=getNode(this, index);
    	returnAux=aux->pElement;
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* nAux;
    if(this!=NULL && index>=0 && index<this->size)
    {
    	nAux=getNode(this, index);
    	nAux->pElement=pElement;
    	returnAux=0;
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* aux;
    Node* ant;
    if(this!=NULL && index>=0&& index<this->size)
    {
    	aux=getNode(this, index);
    	if(index==0)
    	{
    		this->pFirstNode=aux->pNextNode;
    	}
    	else{
    		ant=getNode(this, index-1);
    		ant->pNextNode=aux->pNextNode;
    	}
    	free(aux);
    	this->size--;
    	returnAux=0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	for(int i=(ll_len(this)-1);i>=0;i--)
    	{
    		ll_remove(this,i);
    	}
    	returnAux=0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* aux;
    if(this!=NULL)
    {
    	for(int i=0;i<ll_len(this);i++)
    	{
    		aux=ll_get(this, i);
    		if(aux==pElement)
    		{
    			returnAux=i;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	if(ll_len(this)==0)
    	{
    		returnAux=1;
    	}
    	else{
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && index>=0 && index<=ll_len(this))
    {
    	returnAux=addNode(this, index, pElement);
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	returnAux=ll_get(this, index);
    	ll_remove(this, index);
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	if(ll_indexOf(this, pElement)!=-1)
    	{
    		returnAux=1;
    	}
    	else{
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    if(this!=NULL && this2!=NULL)
    {
    	returnAux=1;
    	for(int i=0;i<ll_len(this);i++)
    	{
    		if(!ll_contains(this, ll_get(this2, i)))
    		{
    			returnAux=0;
    			break;
    		}
    	}

    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* aux;
    if(this!=NULL && (from>=0 && from<ll_len(this))&& (to>from && to<=ll_len(this)))
    {
    	cloneArray=ll_newLinkedList();
    	if(cloneArray!=NULL)
    	{
    		for(int i=from;i<=to;i++)
    		{
    		   aux=ll_get(this, i);
    		   ll_add(cloneArray, aux);
    		}
    	}
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this!=NULL)
    {
    	cloneArray=ll_subList(this, 0, ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int flagSwap;
    Node* datoA;
    Node* datoB;
    void* aux;
    if(this!=NULL && pFunc!=NULL && (order==1||order==0))
    {
    	do{
    		flagSwap=0;
    		for(int i=1;i<ll_len(this);i++)
    		{
    		   datoA=getNode(this, i-1);
    		   datoB=getNode(this, i);
    		   if((order==1 && pFunc(datoA->pElement,datoB->pElement)==1)||
    				(order==0 && pFunc(datoA->pElement,datoB->pElement)==-1))
    		   {
    			   aux=datoA->pElement;
    			   datoA->pElement=datoB->pElement;
    			   datoB->pElement=aux;
    			   flagSwap=1;
    		   }
    		}
    	}while(flagSwap);
    	returnAux=0;
    }
    return returnAux;
}
int ll_map(LinkedList* this ,int(*pFunc)(void*))
{
	int r=-1;
	void* aux;
	if(this!=NULL && pFunc!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			aux=ll_get(this, i);
			pFunc(aux);
		}
		r=0;
	}
	return r;
}
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int r=-1;
	void* aux;
	int i;
	if(this!=NULL&& pFunc!=NULL)
	{
		i=0;
		while(i<ll_len(this))
		{
			aux=ll_get(this, i);
			if(!pFunc(aux))
			{
				ll_remove(this, i);
			}
			else{
				i++;
			}
		}
		r=0;
	}
	return r;
}
int ll_reduceInt(LinkedList* this, int(*pFunc)(void*), int* pResultado)
{
	int r=-1;
	void* aux;
	int acumulado=0;
	if(this!=NULL && pFunc!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			aux=ll_get(this, i);
			acumulado=acumulado+pFunc(aux);
		}
		*pResultado=acumulado;
		r=0;
	}
	return r;
}
int ll_reduceFloat(LinkedList* this, float(*pFunc)(void*),float* pResultado)
{
	int r=-1;
	void* aux;
	float acumulado=0;
	if(this!=NULL && pFunc!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			aux=ll_get(this, i);
			acumulado=acumulado+pFunc(aux);
		}
		*pResultado=acumulado;
		r=0;
	}
	return r;
}
int ll_search(LinkedList* this,int(*pFunc)(void*,void*), void* it)
{
	int r=-1;
	void* aux;
	if(this!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			aux=ll_get(this, i);
			if(pFunc(aux,it))
			{
				r=i;
				break;
			}
		}
	}
	return r;
}
int ll_filterII(LinkedList* this, int (*pFunc)(void*,void*),void* element)
{
	int r=-1;
	void* aux;
	int i;
	if(this!=NULL&& pFunc!=NULL)
	{
		i=0;
		while(i<ll_len(this))
		{
			aux=ll_get(this, i);
			if(!pFunc(aux,element))
			{
				ll_remove(this, i);
			}
			else{
				i++;
			}
		}
		r=0;
	}
	return r;
}
int ll_reduceIntII(LinkedList* this, int(*pFunc)(void*,void*),void* this2,int* pResultado)
{
	int r=-1;
	void* aux;
	int acumulado=0;
	if(this!=NULL && pFunc!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			aux=ll_get(this, i);
			acumulado=acumulado+pFunc(aux,this2);
		}
		*pResultado=acumulado;
		r=0;
	}
	return r;
}
