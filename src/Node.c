/**
 * Copyright INRIA, contributors Holley and Peterlongo
 * guillaume.holley@gmail.com
 * pierre.peterlongo@inria.fr
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Duo.h"
#include "sequence_4bits.h"

Node* createNode(char* id, char* attribute){
    Node* n = malloc(sizeof(Node));
    if ( n!= NULL ){
        n->id = strdup(id);
        n->attribute = createSequence(attribute);
        n->childrenStoT = list_create_NodeChar();
        n->childrenTtoS = list_create_NodeChar();
        n->relative_position = list_create();

        return n;
    }
    else {
        fprintf (stderr, "insufficient memory to create a node\n");
        exit (EXIT_FAILURE);
    }
}

void freeNode(Node* n){
    free(n->attribute);
    free(n->id);

    list_free_NodeChar(n->childrenStoT);
    list_free_NodeChar(n->childrenTtoS);
    list_free(n->relative_position);
    free(n);
}

int addNeigh(Node* n_source, Node* n_target, char* reading){
    DuoChar* reading_direction = getReadingDirection(reading);

    // On parcours la liste des fils de n_source à la recherche du duplicate
    cell_NodeChar* elem_list = n_source->childrenStoT->first;
    while (elem_list != NULL){
         if (strcmp(((Node*)elem_list->node)->id,n_target->id) == 0 && elem_list->val == reading_direction->data1){
             free(reading_direction);
             return 0;
         }
         elem_list = elem_list->prox;
    }

        // On parcours la liste des fils de n_target à la recherche du duplicate
    elem_list = n_target->childrenTtoS->first;
    while (elem_list != NULL){
         if (strcmp(((Node*)elem_list->node)->id,n_source->id) == 0 && elem_list->val == reading_direction->data2){
             free(reading_direction);
             return 0;
         }
         elem_list = elem_list->prox;
    }

    // Si pas présent dans les fils (y compris le dernier élément) alors on insère nTarget
    list_add_NodeChar(n_target->childrenTtoS, n_source, reading_direction->data2);
    list_add_NodeChar(n_source->childrenStoT, n_target, reading_direction->data1);

    free(reading_direction);
    return 1;
}

NodeR* createNodeR(char* id, char* attribute, char* reverse_comp_attribute){
    NodeR* n = malloc(sizeof(NodeR));
    if ( n!= NULL ){
        n->id = strdup(id);
        n->attribute = createSequence(attribute);
        n->attributeR = createSequence(reverse_comp_attribute);
        n->childrenStoT = list_create_NodeChar();
        n->childrenTtoS = list_create_NodeChar();
        n->relative_position = list_create();
        return n;
    }
    else {
        fprintf (stderr, "insufficient memory to create a node\n");
        exit (EXIT_FAILURE);
    }
}

void freeNodeR(NodeR* n){
    free(n->attribute);
    free(n->attributeR);
    free(n->id);

    list_free_NodeChar(n->childrenStoT);
    list_free_NodeChar(n->childrenTtoS);
    list_free(n->relative_position);
    free(n);
}

int addNeighR(NodeR* n_source, NodeR* n_target, char* reading){
    DuoChar* reading_direction = getReadingDirection(reading);

    // On parcours la liste des fils de n_source à la recherche du duplicate
    cell_NodeChar* elem_list = n_source->childrenStoT->first;
    while (elem_list != NULL){
         if (strcmp(((NodeR*)elem_list->node)->id,n_target->id) == 0 && elem_list->val == reading_direction->data1){
             free(reading_direction);
             return 0;
         }
         elem_list = elem_list->prox;
    }

        // On parcours la liste des fils de n_target à la recherche du duplicate
    elem_list = n_target->childrenTtoS->first;
    while (elem_list != NULL){
         if (strcmp(((NodeR*)elem_list->node)->id,n_source->id) == 0 && elem_list->val == reading_direction->data2){
             free(reading_direction);
             return 0;
         }
         elem_list = elem_list->prox;
    }

    // Si pas présent dans les fils (y compris le dernier élément) alors on insère nTarget
    list_add_NodeChar(n_target->childrenTtoS, n_source, reading_direction->data2);
    list_add_NodeChar(n_source->childrenStoT, n_target, reading_direction->data1);

    free(reading_direction);
    return 1;
}
