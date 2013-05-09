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

#include <string.h>
#include "Duo.h"
#include "extendLevenshtein.h"
#include "Node.h"
#include "extend.h"
#include "sequence_4bits.h"
#include "listNodeUint16.h"

int extend(char* req, Pvoid_t* index, int size_seeds, int overlap_size, int treshold, int id_query){

    list* ens_node_analyze = list_create();
    list* ensVertexLeft = NULL;
    list* ensVertexRight = NULL;

    char forward = 1;
    char reverse = 0;

    char StoT = 1;
    char TtoS = 0;

    int i, j;
    int res = 0;

    int req_lg = strlen(req);

    // Test toute les graines de la requête
    for (i=0; i<=(req_lg-size_seeds); i++){
        int seed_found = 0;
        for (j=0; j<2 && seed_found == 0; j++){

            unsigned char *requete = NULL;
            unsigned char *rev_requete = NULL;

            if (j==0){
                    requete = createSequence(req);
                    rev_requete = reverseSequence(requete,1);
            }
            else{
                    rev_requete = createSequence(req);
                    requete = reverseSequence(rev_requete,1);
            }

            unsigned char* graine = subSequence(requete,i,i+size_seeds-1);
            list_NodeUint16* elem_seed = NULL;

            Word_t* PValue = NULL;
            JSLG(PValue, *index, (char*)graine)

            if (PValue != NULL){

                elem_seed = (list_NodeUint16*)*PValue;

                ensVertexLeft = list_create();
                ensVertexRight = list_create();

                cell_NodeUint16* elem_list = elem_seed->first;

                while (elem_list != NULL){
                    Node* n = elem_list->node;
                    int duplicate = 0;

                    cell* elem_list_reminder = n->relative_position->first;
                    while (elem_list_reminder != NULL && duplicate == 0){
                        if (*((int*)elem_list_reminder->val) == elem_list->val-i){
                            duplicate = 1;
                        }
                        elem_list_reminder = elem_list_reminder->prox;
                    }

                    if (duplicate == 0){

                        int* calc = malloc(sizeof(int));
                        *calc = elem_list->val-i;
                        list_add(n->relative_position, calc);
                        list_add(ens_node_analyze, n);

                        if ( i != 0 ) extendLevenshtein (n, seqlen(n->attribute) - elem_list->val - 1, rev_requete, req_lg, req_lg - i-1, reverse, TtoS, -2, -1, 1, treshold, overlap_size, ens_node_analyze, ensVertexLeft);

                        if (i != (strlen(req)-size_seeds)) extendLevenshtein (n, elem_list->val, requete, req_lg, i, forward, StoT, -2, -1, 1, treshold, overlap_size, ens_node_analyze, ensVertexRight);

                        if (i == 0){
                            cell* elem_list_ensVertex_right = ensVertexRight->first;
                            while (elem_list_ensVertex_right != NULL){
                                if (res==0) printf("One or more alignments found for query %d \n\n", id_query);
                                res = 1;
                                seed_found = 1;
                                cell* elem_list_ensVertex_rightbis = ((list*)elem_list_ensVertex_right->val)->first;
                                while (elem_list_ensVertex_rightbis != NULL){
                                    Node* n_tmp = (Node*)elem_list_ensVertex_rightbis->val;
                                    printf("In node %s \n", n_tmp->id);

                                    elem_list_ensVertex_rightbis = elem_list_ensVertex_rightbis->prox;
                                }
                                printf("-----\n");

                                list_free(elem_list_ensVertex_right->val);
                                elem_list_ensVertex_right = elem_list_ensVertex_right->prox;
                            }

                            list_free(ensVertexLeft);
                            ensVertexLeft = list_create();
                            list_free(ensVertexRight);
                            ensVertexRight = list_create();
                        }
                        else if (i == (strlen(req)-size_seeds)){
                            cell* elem_list_ensVertex = ensVertexLeft->first;
                            while (elem_list_ensVertex != NULL){
                                if (res==0) printf("One or more alignments found for query %d \n\n", id_query);
                                res = 1;
                                seed_found = 1;
                                cell* elem_list_ensVertex_leftbis = ((list*)elem_list_ensVertex->val)->first;
                                while (elem_list_ensVertex_leftbis != NULL){
                                    Node* n_tmp = (Node*)elem_list_ensVertex_leftbis->val;
                                    printf("In node %s \n", n_tmp->id);
                                    elem_list_ensVertex_leftbis = elem_list_ensVertex_leftbis->prox;
                                }
                                printf("-----\n");

                                list_free(elem_list_ensVertex->val);
                                elem_list_ensVertex = elem_list_ensVertex->prox;
                            }

                            list_free(ensVertexLeft);
                            ensVertexLeft = list_create();
                            list_free(ensVertexRight);
                            ensVertexRight = list_create();

                        }
                        else {
                            cell* elem_list_ensVertex = ensVertexLeft->first;
                            while (elem_list_ensVertex != NULL){

                                cell* elem_list_ensVertex_right = ensVertexRight->first;
                                while (elem_list_ensVertex_right != NULL){
                                    if (res==0) printf("One or more alignments found for query %d \n\n", id_query);
                                    res = 1;
                                    seed_found = 1;
                                    cell* elem_list_ensVertex_leftbis = ((list*)elem_list_ensVertex->val)->first;
                                    while (elem_list_ensVertex_leftbis != NULL){
                                        Node* n_tmp = (Node*)elem_list_ensVertex_leftbis->val;
                                        printf("In node %s \n", n_tmp->id);
                                        elem_list_ensVertex_leftbis = elem_list_ensVertex_leftbis->prox;
                                    }

                                    cell* elem_list_ensVertex_rightbis = ((list*)elem_list_ensVertex_right->val)->first;
                                    while (elem_list_ensVertex_rightbis != NULL){
                                        Node* n_tmp = (Node*)elem_list_ensVertex_rightbis->val;
                                        printf("In node %s \n", n_tmp->id);
                                        elem_list_ensVertex_rightbis = elem_list_ensVertex_rightbis->prox;
                                    }

                                    printf("-----\n");

                                    elem_list_ensVertex_right = elem_list_ensVertex_right->prox;
                                }

                                elem_list_ensVertex = elem_list_ensVertex->prox;
                            }

                            elem_list_ensVertex = ensVertexLeft->first;
                            while (elem_list_ensVertex != NULL){
                                list_free(elem_list_ensVertex->val);
                                elem_list_ensVertex = elem_list_ensVertex->prox;
                            }

                            cell* elem_list_ensVertex_right = ensVertexRight->first;
                            while (elem_list_ensVertex_right != NULL){
                                list_free(elem_list_ensVertex_right->val);
                                elem_list_ensVertex_right = elem_list_ensVertex_right->prox;
                            }

                            list_free(ensVertexLeft);
                            ensVertexLeft = list_create();
                            list_free(ensVertexRight);
                            ensVertexRight = list_create();

                        }
                    }

                    if(elem_list) elem_list = elem_list->prox;
                    else break;
                }

                list_free(ensVertexLeft);
                list_free(ensVertexRight);
            }

            free(graine);
            free(requete);
            free(rev_requete);
        }
    }

    if (res==0) printf("No alignment found for query %d \n\n", id_query);
    fflush(stdout);

    cell* elem_list_free = ens_node_analyze->first;

    while (elem_list_free != NULL){
        Node* n = (Node*)elem_list_free->val;
        list_of_generic_free(n->relative_position);
        n->relative_position = list_create();

        elem_list_free = elem_list_free->prox;
    }

    list_free(ens_node_analyze);

    return res;
}

int extendR(char* req, Pvoid_t* index, int size_seeds, int overlap_size, int treshold, int id_query){

    list* ens_node_analyze = list_create();
    list* ensVertexLeft = NULL;
    list* ensVertexRight = NULL;

    char forward = 1;
    char reverse = 0;

    char StoT = 1;
    char TtoS = 0;

    int i, j;
    int res = 0;

    int req_lg = strlen(req);

    // Test toute les graines de la requête
    for (i=0; i<=(req_lg-size_seeds); i++){
        int seed_found = 0;
        for (j=0; j<2 && seed_found == 0; j++){

            unsigned char *requete = NULL;
            unsigned char *rev_requete = NULL;

            if (j==0){
                    requete = createSequence(req);
                    rev_requete = reverseSequence(requete,1);
            }
            else{
                    rev_requete = createSequence(req);
                    requete = reverseSequence(rev_requete,1);
            }

            unsigned char* graine = subSequence(requete,i,i+size_seeds-1);
            list_NodeUint16* elem_seed = NULL;

            Word_t* PValue = NULL;
            JSLG(PValue, *index, (char*)graine)

            if (PValue != NULL){

                elem_seed = (list_NodeUint16*)*PValue;
                seed_found = 1;

                ensVertexLeft = list_create();
                ensVertexRight = list_create();

                cell_NodeUint16* elem_list = elem_seed->first;

                while (elem_list != NULL){
                    NodeR* n = elem_list->node;
                    int posOnNodeReverse = seqlen(n->attribute) - elem_list->val - 1;

                    int duplicate = 0;

                    cell* elem_list_reminder = n->relative_position->first;
                    while (elem_list_reminder != NULL && duplicate == 0){
                        if (*((int*)elem_list_reminder->val) == elem_list->val-i){
                            duplicate = 1;
                        }
                        elem_list_reminder = elem_list_reminder->prox;
                    }

                    if (duplicate == 0){

                        int* calc = malloc(sizeof(int));
                        *calc = elem_list->val-i;
                        list_add(n->relative_position, calc);
                        list_add(ens_node_analyze, n);

                        if ( i != 0 ) extendLevenshteinR (n, seqlen(n->attribute) - elem_list->val - 1, rev_requete, req_lg, req_lg - i-1, reverse, TtoS, -2, -1, 1, treshold, overlap_size, ens_node_analyze, ensVertexLeft);

                        if (i != (strlen(req)-size_seeds)) extendLevenshteinR (n, elem_list->val, requete, req_lg, i, forward, StoT, -2, -1, 1, treshold, overlap_size, ens_node_analyze, ensVertexRight);

                        if (i == 0){
                            cell* elem_list_ensVertex_right = ensVertexRight->first;
                            while (elem_list_ensVertex_right != NULL){
                                if (res==0) printf("One or more alignments found for query %d \n\n", id_query);
                                res = 1;
                                cell* elem_list_ensVertex_rightbis = ((list*)elem_list_ensVertex_right->val)->first;
                                while (elem_list_ensVertex_rightbis != NULL){
                                    NodeR* n_tmp = (NodeR*)elem_list_ensVertex_rightbis->val;
                                    printf("In node %s \n", n_tmp->id);

                                    elem_list_ensVertex_rightbis = elem_list_ensVertex_rightbis->prox;
                                }
                                printf("-----\n");

                                list_free(elem_list_ensVertex_right->val);
                                elem_list_ensVertex_right = elem_list_ensVertex_right->prox;
                            }

                            list_free(ensVertexLeft);
                            ensVertexLeft = list_create();
                            list_free(ensVertexRight);
                            ensVertexRight = list_create();
                        }
                        else if (i == (strlen(req)-size_seeds)){
                            cell* elem_list_ensVertex = ensVertexLeft->first;
                            while (elem_list_ensVertex != NULL){
                                if (res==0) printf("One or more alignments found for query %d \n\n", id_query);
                                res = 1;
                                cell* elem_list_ensVertex_leftbis = ((list*)elem_list_ensVertex->val)->first;
                                while (elem_list_ensVertex_leftbis != NULL){
                                    NodeR* n_tmp = (NodeR*)elem_list_ensVertex_leftbis->val;
                                    printf("In node %s \n", n_tmp->id);

                                    elem_list_ensVertex_leftbis = elem_list_ensVertex_leftbis->prox;
                                }
                                printf("-----\n");

                                list_free(elem_list_ensVertex->val);
                                elem_list_ensVertex = elem_list_ensVertex->prox;
                            }

                            list_free(ensVertexLeft);
                            ensVertexLeft = list_create();
                            list_free(ensVertexRight);
                            ensVertexRight = list_create();

                        }
                        else {
                            cell* elem_list_ensVertex = ensVertexLeft->first;
                            while (elem_list_ensVertex != NULL){

                                cell* elem_list_ensVertex_right = ensVertexRight->first;
                                while (elem_list_ensVertex_right != NULL){
                                    if (res==0) printf("One or more alignments found for query %d \n\n", id_query);
                                    res = 1;

                                    cell* elem_list_ensVertex_leftbis = ((list*)elem_list_ensVertex->val)->first;
                                    while (elem_list_ensVertex_leftbis != NULL){
                                        NodeR* n_tmp = (NodeR*)elem_list_ensVertex_leftbis->val;
                                        printf("In node %s \n", n_tmp->id);

                                        elem_list_ensVertex_leftbis = elem_list_ensVertex_leftbis->prox;
                                    }

                                    cell* elem_list_ensVertex_rightbis = ((list*)elem_list_ensVertex_right->val)->first;
                                    while (elem_list_ensVertex_rightbis != NULL){
                                        Node* n_tmp = (Node*)elem_list_ensVertex_rightbis->val;
                                        printf("In node %s \n", n_tmp->id);

                                        elem_list_ensVertex_rightbis = elem_list_ensVertex_rightbis->prox;
                                    }

                                        printf("-----\n");

                                    elem_list_ensVertex_right = elem_list_ensVertex_right->prox;
                                }

                                elem_list_ensVertex = elem_list_ensVertex->prox;
                            }

                            elem_list_ensVertex = ensVertexLeft->first;
                            while (elem_list_ensVertex != NULL){

                                list_free(elem_list_ensVertex->val);

                                elem_list_ensVertex = elem_list_ensVertex->prox;
                            }

                            cell* elem_list_ensVertex_right = ensVertexRight->first;
                            while (elem_list_ensVertex_right != NULL){
                                list_free(elem_list_ensVertex_right->val);

                                elem_list_ensVertex_right = elem_list_ensVertex_right->prox;
                            }


                            list_free(ensVertexLeft);
                            ensVertexLeft = list_create();
                            list_free(ensVertexRight);
                            ensVertexRight = list_create();

                        }
                    }

                    if(elem_list) elem_list = elem_list->prox;
                    else break;
                }

                list_free(ensVertexLeft);
                list_free(ensVertexRight);
            }

            free(graine);
            free(requete);
            free(rev_requete);
        }
    }

    if (res==0) printf("No alignment found for query %d \n\n", id_query);
    fflush(stdout);

    cell* elem_list_free = ens_node_analyze->first;

    while (elem_list_free != NULL){
        NodeR* n = (NodeR*)elem_list_free->val;
        list_of_generic_free(n->relative_position);
        n->relative_position = list_create();

        elem_list_free = elem_list_free->prox;
    }

    list_free(ens_node_analyze);

    return res;
}

