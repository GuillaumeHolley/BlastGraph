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

#include <stdint.h>
#include "extendLevenshtein.h"
#include "Node.h"
#include "list.h"
#include "listNodeChar.h"
#include "sequence_4bits.h"
#include <limits.h>

void extendLevenshtein (Node* n_current_node, int posOnNode, unsigned char* query, int query_lg, int position_on_query, char forward, char dir, int costIndel, int costMismatch, int costMatch,  int treshold, int overlap_size, list* reminder, list* ens_result){
    int n_current_node_lg = seqlen(n_current_node->attribute);

    //printf("Node = %s, posOnNode = %d, position_on_query = %d, forward = %d, dir = %d\n", n_current_node->id, posOnNode, position_on_query, forward, dir);

    unsigned char* sub_query_for_matrix = subSequence(query,position_on_query, query_lg-1);
    PartialDP* matrix = createPartialDP(sub_query_for_matrix, costIndel, treshold);

    unsigned char* seq_current_node;
    int seq_current_node_lg;
    if (forward == 1) seq_current_node = subSequence(n_current_node->attribute, posOnNode, n_current_node_lg-1);
    else{
        unsigned char* rev = reverseSequence(n_current_node->attribute,1);
        seq_current_node = subSequence(rev, posOnNode, n_current_node_lg-1);
        free(rev);
    }

    seq_current_node_lg = seqlen(seq_current_node);

    list* ens_vertex = list_create();
    list_add(ens_vertex, n_current_node);

    int max = computePartialDP(matrix, seq_current_node/*, 0*/, costIndel, costMismatch, costMatch);
    //printf("Matrix value : A* = %d, colg = %d, cold = %d, max = %d\n", matrix->A_etoile, matrix->colg, matrix->cold, max);
    //printPartialDP(matrix);

    if (max > INT_MIN+2 && seq_current_node_lg >= query_lg && ens_vertex->first == NULL){
        list_add(ens_result, ens_vertex);
    }
    else if (max > INT_MIN+2 && seq_current_node_lg-1 < matrix->nbCol-2) {

        cell_NodeChar* elem_children_current_node;
        if (dir==1) elem_children_current_node = n_current_node->childrenStoT->first;
        else elem_children_current_node = n_current_node->childrenTtoS->first;

        while (elem_children_current_node != NULL){

            PartialDP* matrix_tmp = copyPartialDP(matrix);

            if (val1Forward(elem_children_current_node->val) == forward){

                extendLevenshteinAux(
                        n_current_node,
                        elem_children_current_node->node,
                        seq_current_node,
                        matrix_tmp,
                        position_on_query+seq_current_node_lg,
                        query_lg,
                        seq_current_node_lg,
                        val2Forward(elem_children_current_node->val),
                        dir,
                        costIndel,
                        costMismatch,
                        costMatch,
                        overlap_size,
                        ens_vertex,
                        reminder,
                        ens_result,
                        0
                );
            }

            freePartialDP(matrix_tmp);

            elem_children_current_node = elem_children_current_node->prox;
        }

        list_free(ens_vertex);
    }
    else list_free(ens_vertex);

    freePartialDP(matrix);
    free(seq_current_node);
    free(sub_query_for_matrix);
}

void extendLevenshteinAux (Node* n_father, Node* n_current_node, unsigned char* seq_nodes_to_extend, PartialDP* matrix, int position_on_query_extend, int query_length, int next_position_to_compute, char forward, char dir, int costIndel, int costMismatch, int costMatch, int overlap_size, list* ens_vertex, list* reminder, list* ens_result, int inv){
    int n_current_node_lg = seqlen(n_current_node->attribute);
    int duplicate = 0;

    //printf("NodeAux = %s, forward = %d\n", n_current_node->id, forward);

    int align_rel = 0;
    if (forward == 1) align_rel = -position_on_query_extend;
    else align_rel = n_current_node_lg - query_length-position_on_query_extend -1;

    if (strcmp(n_father->id, n_current_node->id) != 0){
        cell* elem_list_reminder = n_current_node->relative_position->first;
        while (elem_list_reminder != NULL){
            if (*((int*)elem_list_reminder->val) == align_rel){
                duplicate = 1;
                break;
            }
            elem_list_reminder = elem_list_reminder->prox;
        }
    }

    if (duplicate == 0){

        unsigned char* seq_current_node;
        int seq_current_node_lg;
        if (forward == 1){
            unsigned char* sub_current_node_overlap = subSequence(n_current_node->attribute, overlap_size, n_current_node_lg - 1);
            seq_current_node = concatSequence(seq_nodes_to_extend, sub_current_node_overlap);
            free(sub_current_node_overlap);
        }
        else {
            unsigned char* sub_current_node_overlap = subSequence(n_current_node->attribute, 0, n_current_node_lg - overlap_size - 1);
            unsigned char* rev = reverseSequence(sub_current_node_overlap, 1);
            seq_current_node = concatSequence(seq_nodes_to_extend, rev);

            free(rev);
            free(sub_current_node_overlap);
        }

        seq_current_node_lg = seqlen(seq_current_node);

        list* ens_vertexAux = list_copy(ens_vertex);
        list_add(ens_vertexAux, n_current_node);

        int max = computePartialDP(matrix, seq_current_node/*, next_position_to_compute*/, costIndel, costMismatch, costMatch);
        //printf("Matrix value : A* = %d, colg = %d, cold = %d, max = %d\n", matrix->A_etoile, matrix->colg, matrix->cold, max);
        //printPartialDP(matrix);

        int* calc = malloc(sizeof(int));
        *calc = align_rel;
        list_add(n_current_node->relative_position, calc);
        list_add(reminder,n_current_node);

        if (max > INT_MIN+2 && seq_current_node_lg >= matrix->nbCol-1 && ens_vertexAux->first != NULL){
            list_add(ens_result, ens_vertexAux);
        }
        else if (max > INT_MIN+2 && seq_current_node_lg < matrix->nbCol-1){

            cell_NodeChar* elem_children_current_node;
            if (dir==1) elem_children_current_node = n_current_node->childrenStoT->first;
            else elem_children_current_node = n_current_node->childrenTtoS->first;

            while (elem_children_current_node != NULL){

                    if (val1Forward(elem_children_current_node->val) == forward){
                        PartialDP* matrix_tmp = copyPartialDP(matrix);
                        extendLevenshteinAux(n_current_node, elem_children_current_node->node, seq_current_node, matrix_tmp, position_on_query_extend+n_current_node_lg - overlap_size, query_length, seq_current_node_lg, val2Forward(elem_children_current_node->val), dir, costIndel, costMismatch, costMatch, overlap_size, ens_vertexAux, reminder, ens_result, 0);
                        freePartialDP(matrix_tmp);
                    }

                elem_children_current_node = elem_children_current_node->prox;
            }
            list_free(ens_vertexAux);

        }
        else list_free(ens_vertexAux);

        free(seq_current_node);
    }
}

void extendLevenshteinR (NodeR* n_current_node, int posOnNode, unsigned char* query, int query_lg, int position_on_query, char forward, char dir, int costIndel, int costMismatch, int costMatch,  int treshold, int overlap_size, list* reminder, list* ens_result){
    //printf("Node = %s, posOnNode = %d, position_on_query = %d\n", n_current_node->id, posOnNode, position_on_query);

    int n_current_node_lg = seqlen(n_current_node->attribute);
    unsigned char* seq_current_node = NULL;

    unsigned char* sub_query_for_matrix = subSequence(query,position_on_query, query_lg-1);
    PartialDP* matrix = createPartialDP(sub_query_for_matrix, costIndel, treshold);

    if (forward == 1) seq_current_node = subSequence(n_current_node->attribute, posOnNode, n_current_node_lg-1);
    else seq_current_node = subSequence(n_current_node->attributeR, posOnNode, n_current_node_lg-1);

    int seq_current_node_lg = seqlen(seq_current_node);

    list* ens_vertex = list_create();
    list_add(ens_vertex, n_current_node);

    int max = computePartialDP(matrix, seq_current_node, costIndel, costMismatch, costMatch);

    if (max > INT_MIN+2 && seq_current_node_lg >= query_lg && ens_vertex->first != NULL) list_add(ens_result, ens_vertex);
    else if (max > INT_MIN+2 && seq_current_node_lg-1 < matrix->nbCol-2) {

        cell_NodeChar* elem_children_current_node;
        if (dir==1) elem_children_current_node = n_current_node->childrenStoT->first;
        else elem_children_current_node = n_current_node->childrenTtoS->first;

        while (elem_children_current_node != NULL){

            if (val1Forward(elem_children_current_node->val) == forward){
                PartialDP* matrix_tmp = copyPartialDP(matrix);
                extendLevenshteinAuxR(
                        n_current_node,
                        elem_children_current_node->node,
                        seq_current_node,
                        matrix,
                        position_on_query+seq_current_node_lg,
                        query_lg,
                        seq_current_node_lg,
                        val2Forward(elem_children_current_node->val),
                        dir,
                        costIndel,
                        costMismatch,
                        costMatch,
                        overlap_size,
                        ens_vertex,
                        reminder,
                        ens_result
                );

                freePartialDP(matrix_tmp);
            }

            elem_children_current_node = elem_children_current_node->prox;
        }

        list_free(ens_vertex);
    }
    else list_free(ens_vertex);

    freePartialDP(matrix);
    free(seq_current_node);
}

void extendLevenshteinAuxR (NodeR* n_father, NodeR* n_current_node, unsigned char* seq_nodes_to_extend, PartialDP* matrix, int position_on_query_extend, int query_length, int next_position_to_compute, char forward, char dir, int costIndel, int costMismatch, int costMatch, int overlap_size, list* ens_vertex, list* reminder, list* ens_result){
    int n_current_node_lg = seqlen(n_current_node->attribute);
    int duplicate = 0;

    //printf("NodeAux = %s \n", n_current_node->id);

    int align_rel = 0;
    if (forward == 1) align_rel = -position_on_query_extend;
    else align_rel = n_current_node_lg - query_length - position_on_query_extend -1;

    if (strcmp(n_father->id, n_current_node->id) != 0){
        cell* elem_list_reminder = n_current_node->relative_position->first;
        while (elem_list_reminder != NULL){
            if (*((int*)elem_list_reminder->val) == align_rel){
                duplicate = 1;
                break;
            }
            elem_list_reminder = elem_list_reminder->prox;
        }
    }

    if (duplicate == 0){

        unsigned char* seq_current_node;
        int seq_current_node_lg;

        if (forward == 1){
            unsigned char* sub_current_node_overlap = subSequence(n_current_node->attribute, overlap_size, n_current_node_lg - 1);
            seq_current_node = concatSequence(seq_nodes_to_extend, sub_current_node_overlap);
            free(sub_current_node_overlap);
        }
        else {
            unsigned char* sub_current_node_overlap = subSequence(n_current_node->attributeR, 0, n_current_node_lg - overlap_size - 1);
            seq_current_node = concatSequence(seq_nodes_to_extend, sub_current_node_overlap);
            free(sub_current_node_overlap);
        }

        seq_current_node_lg = seqlen(seq_current_node);

        list* ens_vertexAux = list_copy(ens_vertex);
        list_add(ens_vertexAux, n_current_node);

        int max = computePartialDP(matrix, seq_current_node, costIndel, costMismatch, costMatch);
        //printPartialDP(matrix);

        int* calc = malloc(sizeof(int));
        *calc = align_rel;
        list_add(n_current_node->relative_position, calc);
        list_add(reminder,n_current_node);

        if (max > INT_MIN+2 && seq_current_node_lg >= matrix->nbCol-1 && ens_vertexAux->first != NULL) list_add(ens_result, ens_vertexAux);
        else if (max > INT_MIN+2 && seq_current_node_lg < matrix->nbCol-1){

            cell_NodeChar* elem_children_current_node;
            if (dir==1) elem_children_current_node = n_current_node->childrenStoT->first;
            else elem_children_current_node = n_current_node->childrenTtoS->first;

            while (elem_children_current_node != NULL){

                if (val1Forward(elem_children_current_node->val) == forward){
                    PartialDP* matrix_tmp = copyPartialDP(matrix);
                    extendLevenshteinAuxR(n_current_node, elem_children_current_node->node, seq_current_node, matrix, position_on_query_extend+n_current_node_lg - overlap_size, query_length, seq_current_node_lg, val2Forward(elem_children_current_node->val), dir, costIndel, costMismatch, costMatch, overlap_size, ens_vertexAux, reminder, ens_result);
                    freePartialDP(matrix_tmp);
                }

                elem_children_current_node = elem_children_current_node->prox;
            }
            list_free(ens_vertexAux);

        }
        else list_free(ens_vertexAux);

        free(seq_current_node);
    }
}

