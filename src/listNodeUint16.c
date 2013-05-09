/**
 * Copyright INRIA and ENS, contributors Peterlongo and Chikhi
 * pierre.peterlongo@inria.fr
 * rayan.chikhi@irisa.fr
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".

 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.

 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */

/*
 * list.c
 *
 *  Created on: 16 sept. 2010
 *      Author: ppeterlo
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listNodeUint16.h"
#include "commons.h"

list_NodeUint16* list_create_NodeUint16(void){
	list_NodeUint16 * l = malloc(sizeof(list_NodeUint16)); test_alloc(l);
	//l->size=0;
	l->first= NULL;
	return l;
}

void list_add_NodeUint16(list_NodeUint16* l, void* n, uint32_t val)
{
        cell_NodeUint16 * new_l = (cell_NodeUint16 *)malloc(sizeof(cell_NodeUint16)); test_alloc(new_l);
        new_l->node = n;
        new_l->val = val;

        //l->size++;
        new_l->prox = l->first;
        l->first=new_l;
}

void list_add_tail_NodeUint16(list_NodeUint16* l, void* n, uint32_t val)
{
	cell_NodeUint16 * new = (cell_NodeUint16 *)malloc(sizeof(cell_NodeUint16)); test_alloc(new);
	new->node = n;
	new->val = val;
	new->prox = NULL;
	//l->size++;

	// new is going to be appended at the end of the list
	if (l->first==NULL)
		l->first=new;
	else
	{
		cell_NodeUint16 *tmp=l->first;
		while (tmp->prox!=NULL)
			{
			tmp=tmp->prox;
			}
		tmp->prox = new;
	}


}

/*
 * free a list which has no content
 */
void list_free_NodeUint16(const void *v_list)
{
		list_NodeUint16* p_list = (list_NodeUint16*) v_list;
		cell_NodeUint16 *aux;
		cell_NodeUint16 *l = p_list->first;

		while (l != NULL)
		{
			aux = l;
			l = l->prox;
			free(aux);
		}
		free(p_list);
}

/*int numberInList_NodeUint16 (list_NodeUint16*l)
{
	return l->size;
}*/

list_NodeUint16* list_copy_NodeUint16(list_NodeUint16* l){
    list_NodeUint16* new_l = list_create_NodeUint16();
    if (l){
         cell_NodeUint16* elem_list = l->first;
         while (elem_list != NULL){
            list_add_NodeUint16(new_l, elem_list->node, elem_list->val);
            elem_list = elem_list->prox;
         }
    }
    return new_l;
}
