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
 *
 *  Created on: 16 sept. 2010
 *      Author: ppeterlo
 */

#ifndef LIST_NODE_CHAR_H_
#define LIST_NODE_CHAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct CELL_NodeChar {
   void* node;
   char val;
   struct CELL_NodeChar* prox;
} cell_NodeChar;

typedef struct {
	cell_NodeChar* first;
} list_NodeChar;

list_NodeChar *list_create_NodeChar(void);
void list_add_NodeChar(list_NodeChar *l, void* n, char val);
void list_add_tail_NodeChar(list_NodeChar* l, void* n, char val);

void list_free_NodeChar(list_NodeChar* p_list);

list_NodeChar* list_copy_NodeChar(list_NodeChar* l);

#endif
