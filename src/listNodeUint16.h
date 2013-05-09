/**
 * Copyright INRIA and ENS, contributors Peterlongo and Chikhi
 * pierre.peterlongo@inria.fr
 * rayan.chikhi@irisa.fr
 *
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

#ifndef LIST_NODE_UINT16_H_
#define LIST_NODE_UINT16_H_

#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>

typedef struct CELL_NodeUint16 {
   void* node;
   uint32_t val;
   struct CELL_NodeUint16* prox;
} cell_NodeUint16;

typedef struct {
	//int size;
	cell_NodeUint16* first;
} list_NodeUint16;

list_NodeUint16 *list_create_NodeUint16(void);
void list_add_NodeUint16(list_NodeUint16 *l, void* n, uint32_t val);
void list_add_tail_NodeUint16(list_NodeUint16* l, void* n, uint32_t val);

void list_free_NodeUint16(const void *v_list);

list_NodeUint16* list_copy_NodeUint16(list_NodeUint16* l);

#endif
