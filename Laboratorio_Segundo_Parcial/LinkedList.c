#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


#define INICIOLISTA 0
#define TRUE 1
#define FALSE 0

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
    LinkedList* this= (LinkedList*)malloc(sizeof(LinkedList));
    if(this != NULL){
    	this->size = 0;
    	this->pFirstNode = NULL;
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
    if(this != NULL){
    	returnAux = this->size;
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
	int tamanoLista;
	Node* nodoAuxiliar = NULL;
	tamanoLista = ll_len(this);
	if(this != NULL && nodeIndex > -1 && nodeIndex < tamanoLista){
		nodoAuxiliar = this->pFirstNode;
		for(int i = 0;i<nodeIndex;i++){
			nodoAuxiliar = nodoAuxiliar->pNextNode;
		}
	}
    return nodoAuxiliar;
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
    int tamanoLista;
    Node* pNodoAuxiliar = NULL;
    Node* pNodoAnterior;
    tamanoLista = ll_len(this);
   	if(this != NULL && nodeIndex > -1 && nodeIndex <= tamanoLista){
   		pNodoAuxiliar = (Node*)malloc(sizeof(Node));
   		if(pNodoAuxiliar != NULL){
   			pNodoAuxiliar->pElement = pElement;
   			if(nodeIndex == 0){
   				pNodoAuxiliar->pNextNode = this->pFirstNode;
   				this->pFirstNode = pNodoAuxiliar;
   				this->size++;
   			}else if((nodeIndex == tamanoLista)){
   				pNodoAuxiliar->pNextNode = NULL;
   				pNodoAnterior = getNode(this,nodeIndex-1);
   				pNodoAnterior->pNextNode = pNodoAuxiliar;
   				this->size++;
   			}else{
   				pNodoAnterior = getNode(this,nodeIndex-1);
   				pNodoAuxiliar->pNextNode = pNodoAnterior->pNextNode;
   				pNodoAnterior->pNextNode = pNodoAuxiliar;
   				this->size++;
   			}
   			returnAux = 0;
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
    int tamanoLista;
    if(this != NULL){
    	tamanoLista = ll_len(this);
    	addNode(this,tamanoLista,pElement);
    	returnAux = 0;
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
    Node* pNodoAuxiliar = NULL;
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL && index >= 0 && index < tamanoLista){
    	pNodoAuxiliar= getNode(this, index);
    	returnAux= pNodoAuxiliar->pElement;
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
    Node* pNodoAuxiliar = NULL;
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL && index >= 0 && index < tamanoLista){
        pNodoAuxiliar= getNode(this, index);
        pNodoAuxiliar->pElement = pElement;
        returnAux = 0;
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
    Node* pNodoAuxiliar = NULL;
    Node* pNodoAnteriorAuxiliar = NULL;
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL && index >= 0 && index < tamanoLista){
    	if(index==0)
    	{
    		pNodoAuxiliar=this->pFirstNode;
    	    this->pFirstNode=pNodoAuxiliar->pNextNode;
    	    free(pNodoAuxiliar);
    	}else{
    		pNodoAuxiliar=getNode(this, index);
    		pNodoAnteriorAuxiliar=getNode(this, index-1);
    		pNodoAnteriorAuxiliar->pNextNode=pNodoAuxiliar->pNextNode;
    	    free(pNodoAnteriorAuxiliar);
    	 }

    	 this->size--;
    	 returnAux = 0;
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
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL){
    	for(int i = 0;i<tamanoLista;i++){
    		ll_remove(this,i);
    		returnAux = 0;
    	}
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
    if(this != NULL){
    	ll_clear(this);
    	free(this);
    	returnAux = 0;
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
    Node* pNodoAuxiliar = NULL;
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL){
    	for(int i = 0;i<tamanoLista;i++){
    		pNodoAuxiliar = getNode(this,i);
    		if(pNodoAuxiliar->pElement == pElement){
    			returnAux = i;
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
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL){
    	if(tamanoLista > 0){
    		returnAux = 0;
    	}else{
    		returnAux = 1;
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
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL && index >= 0 && index <= tamanoLista){
    	addNode(this, index, pElement);
    	returnAux = 0;
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
    Node* nodoAuxiliar = NULL;
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL && index >= 0 && index <= tamanoLista){
    	nodoAuxiliar = ll_get(this, index);
    	returnAux = nodoAuxiliar;
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
    Node* nodoAuxiliar = NULL;
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL){
    	returnAux = 0;
    	for(int i = 0;i<tamanoLista;i++){
    		nodoAuxiliar = getNode(this, i);
    		if(nodoAuxiliar->pElement == pElement){
    			returnAux = 1;
    			break;
    		}
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
    void* auxiliar;
    int tamanoLista;
    tamanoLista = ll_len(this2);
    if(this != NULL && this2 != NULL){
    	returnAux = 0;
    	for(int i = 0;i<tamanoLista;i++){
    		auxiliar = ll_get(this2,i);
    		if(ll_contains(this, auxiliar) == 1){
    			returnAux = 1;
    		}else{
    			returnAux = 0;
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
    Node* nodoAuxiliar;
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL && from >= 0 && from < tamanoLista && to >= from && to <= tamanoLista){
    	cloneArray = ll_newLinkedList();
    	for(int i = from;i<to;i++){
    		nodoAuxiliar = ll_get(this, i);
    		ll_add(cloneArray, nodoAuxiliar);
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
    int tamanoLista;
    tamanoLista = ll_len(this);
    if(this != NULL){
    	cloneArray = ll_subList(this, INICIOLISTA, tamanoLista);
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
    int tamanoLista;
    Node* nodoAuxiliarUno;
    Node* nodoAuxiliarDos;
    int banderaSwap;
    int criterio;
    tamanoLista = ll_len(this);
    if(this != NULL && pFunc != NULL && (order == 0 || order == 1)){
		returnAux = 0;
		do{
			banderaSwap = FALSE;
			for(int i = 0;i<tamanoLista-1;i++){
				nodoAuxiliarUno = ll_get(this, i);
				nodoAuxiliarDos = ll_get(this,i+1);
				if(nodoAuxiliarUno != NULL && nodoAuxiliarDos != NULL){
					criterio = pFunc(nodoAuxiliarUno,nodoAuxiliarDos);
					if((order == 0 && criterio == -1) || (order == 1 && criterio == 1)){
						ll_set(this, i, nodoAuxiliarDos);
						ll_set(this, i+1, nodoAuxiliarUno);
						banderaSwap = TRUE;
					}
				}
			}
		}while(banderaSwap == TRUE);
    }
    return returnAux;

}

LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*)){
	LinkedList* retornoListaFiltrada = NULL;
	int criterio;
	int tamanioLista;
	void* pAuxiliar;
	LinkedList* listaFiltrada;
	tamanioLista = ll_len(this);
	if(this != NULL && pFunc != NULL){
		listaFiltrada = ll_newLinkedList();
		for(int i = 0; i < tamanioLista; i++){
			pAuxiliar = ll_get(this, i);
			if(pAuxiliar != NULL){
				criterio = pFunc(pAuxiliar);
				if(criterio == TRUE){
					ll_add(listaFiltrada,pAuxiliar);
				}
			}
		}
		retornoListaFiltrada = listaFiltrada;
	}
	return retornoListaFiltrada;
}


int ll_map(LinkedList* this, void (*pFunc)(void*)){
	int retorno = FALSE;
	void* pAuxiliar;
	if(this != NULL && pFunc != NULL){
		for(int i = 0; i< ll_len(this); i++){
			pAuxiliar = ll_get(this, i);
			if(pAuxiliar != NULL){
				pFunc(pAuxiliar);
			}
		}
		retorno = TRUE;
	}
	return retorno;
}
