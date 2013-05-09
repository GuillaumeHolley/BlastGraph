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
#include "list.h"
#include "commons.h"

list* list_create(void){
	list * l = malloc(sizeof(list)); test_alloc(l);
	//l->size=0;
	l->first= NULL;
	return l;
}

void list_add(list *l, void * val)
{
        cell * new_l = (cell *)malloc(sizeof(cell)); test_alloc(new_l);
        new_l->val = val;

        //l->size++;
        new_l->prox = l->first;
        l->first=new_l;
}

void list_add_tail(list *l, void * val)
{
	cell * new = (cell *)malloc(sizeof(cell)); test_alloc(new);
	new->val = val;
	new->prox = NULL;
	//l->size++;

	// new is going to be appended at the end of the list
	if (l->first==NULL)
		l->first=new;
	else
	{
		cell *tmp=l->first;
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
void list_free(const void *v_list)
{
		list * p_list = (list *) v_list;
		cell *aux;
		cell *l = p_list->first;

		while (l != NULL)
		{
			aux = l;
			l = l->prox;
			free(aux);
		}
		free(p_list);
}

/**
 * free a list and its generic content: free all cells, and specifically free their val using a function given as argument.
 */
void list_specific_free(const void *v_list, void (*specific_free)(void *))
{
	list * p_list = (list *) v_list;
	cell *aux;
	cell *l = p_list->first;

	while (l != NULL)
	{
		aux = l;
		l = l->prox;
		specific_free(aux->val);
		free(aux);
	}
	free(p_list);
}

/**
 * free a list and its generic content: free all cells, and  free their val using free().
 */
void list_of_generic_free(const void * v_list)
{
	list * p_list = (list *) v_list;
	cell *aux;
	if(!p_list) return;
	cell * l = p_list->first;

	while (l != NULL)
	{
		if(l->val != NULL) free(l->val);
		l->val=NULL;
		aux = l;
		l = l->prox;
		free(aux);
	}
	free(p_list);
}

/*
 * returns 1 if l1 is included in l2, else 0
 */
int list_included(list *l1, list* l2, int *cmp_func(void *,void *))
{
	cell *cur = l1->first;
	while (cur != NULL)
	{
		if (list_find(l2,cur->val, cmp_func) == NULL)
			return 0;
		cur=cur->prox;
	}
	return 1;
}

void list_del(list *l, cell *c)
{
	cell *cur = l->first;
	if (cur == c)
	{
		cell *next=cur->prox;
		free(c);
		l->first=next;
		return;
	}
	while (cur != NULL)
	{
		if (cur->prox == c)
		{
			cur->prox=c->prox;
			free(c);
			return;
		}
		if (cur->prox == NULL)
			return;
		cur=cur->prox;
	}
}

/*int numberInList (list *l)
{
	return l->size;
}*/

/*
 * returns the cell in l such that cmp_func(cell->val,val)==1
 */
cell* list_find(list *l, void *val, int *cmp_func(void *,void *))
{
	cell *cur = l->first;
	while (cur != NULL)
	{
		if (cmp_func(cur->val,val))
			return cur;
		cur=cur->prox;
	}
	return NULL;
}

int list_id_cmp(void *a, void* b)
{
	return a==b;
}

list* list_copy(list* l){
    list* new_l = list_create();
    if (l){
         cell* elem_list = l->first;
         while (elem_list != NULL){
            //list_add_tail(new_l, elem_list_tmp);
            list_add(new_l, elem_list->val);
            elem_list = elem_list->prox;
         }
    }
    return new_l;
}

list* list_fusion(list* l1, list* l2){
    list* new_l = list_create();
    if (l1 && l2){
         cell* elem_list = l1->first;
         while (elem_list != NULL){
            cell* elem_list_tmp = malloc(sizeof(cell));
            elem_list_tmp = elem_list->val;
           // list_add_tail(new_l, elem_list_tmp);
           list_add(new_l, elem_list_tmp);
            elem_list = elem_list->prox;
         }

         cell* elem_list_l2 = l2->first;
        while (elem_list_l2 != NULL){
            cell* elem_list_tmp = malloc(sizeof(cell));
            elem_list_tmp = elem_list_l2->val;
            //list_add_tail(new_l, elem_list_tmp);
            list_add(new_l, elem_list_tmp);
            elem_list_l2 = elem_list_l2->prox;
         }
    }
    return new_l;
}
