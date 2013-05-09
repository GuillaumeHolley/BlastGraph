#include "Duo.h"
#include "Node.h"
#include "parser.h"
#include "extendHamming.h"
#include "list.h"
#include "sequence_4bits.h"

void extendHamming(Duo* d_current_node, unsigned char* query, int query_lg, int position_on_query, int* forward, int treshold, int overlap_size, list* ens_vertex, list* reminder, list* ens_result){
    HTItem* ht_current_node = (HTItem*)d_current_node->data1;
    Node* n_current_node = (Node*) ht_current_node->data;
    int posOnNode = *((int*)d_current_node->data2);
    int duplicate = 0;
    int current_pos_in_query = position_on_query;
    int current_pos_on_node = posOnNode;
    list* ll_reminder = NULL;

    // Si c'est pas le cas
    if (duplicate == 0){

        unsigned char* seq_current_node;
        int seq_current_node_lg = seqlen(n_current_node->attribute);
        if (*forward == 1) seq_current_node = n_current_node->attribute;
        else seq_current_node = reverseSequence(n_current_node->attribute,1);

        int* calc = malloc(sizeof(int));
        *calc = posOnNode-position_on_query;
        list_add(ll_reminder, createDuo(calc,forward));

        list_add(ens_vertex, ht_current_node);

        int* hamming_distance_calculated = malloc(sizeof(int));
        *hamming_distance_calculated = 0;

        // Comparaison et vérification des caractères de la séquence du noeud et de la séquence requête un par un
         while ((current_pos_in_query<query_lg) && (current_pos_on_node<seq_current_node_lg) && (*hamming_distance_calculated <= treshold)){
            //if (getChar(seq_current_node, current_pos_on_node) != getChar(query, current_pos_in_query)) (*hamming_distance_calculated)++;
            current_pos_on_node++;
            current_pos_in_query++;
         }

            // Si on est en dessous du seuil fixé par l'utilisateur, on ajoute à la structure des résultats finaux
        if ( *hamming_distance_calculated<=treshold && current_pos_in_query >= query_lg && ens_vertex->first != NULL){
            list_add(ens_result, createDuo(ens_vertex,hamming_distance_calculated));
        }
        else if (current_pos_in_query < query_lg && *hamming_distance_calculated<=treshold) {

            cell* elem_children_current_node = n_current_node->children->first;

            while (elem_children_current_node != NULL){

                Duo* d = (Duo*)elem_children_current_node->val;
                int code_child = *((int*)d->data2);
                HTItem* ht_child = (HTItem*)d->data1;

                if (strcmp((char*)ht_child->key,(char*)ht_current_node->key) != 0){
                    if (val1Forward(code_child) == *forward){
                        int* val2 = malloc(sizeof(int));
                        *val2 = val2Forward(code_child);
                        extendHammingAux(ht_child, query, query_lg, current_pos_in_query, *hamming_distance_calculated, val2, treshold, overlap_size, ens_vertex, reminder, ens_result);
                    }
                }

                elem_children_current_node = elem_children_current_node->prox;
            }
        }
        else {
            list_del(ens_vertex, ens_vertex->first);
        }

        if (*forward == 0) free(seq_current_node);
    }
}

void extendHammingAux (HTItem* ht_current_node, unsigned char* query, int query_lg, int position_in_query, int hamming_distance, int* forward, int treshold, int overlap_size, list* ens_vertex, list* reminder, list* ens_result){
    Node* n_current_node = (Node*) ht_current_node->data;
     int n_current_node_lg = seqlen(n_current_node->attribute);
    list* ll_reminder = NULL;
    int duplicate = 0;
    int current_pos_in_query = position_in_query;
    int current_pos_on_node = 0;

    int* hamming_distance_calculated = malloc(sizeof(int));
    *hamming_distance_calculated = hamming_distance;

    if (duplicate == 0){

        unsigned char* seq_current_node;
        int seq_current_node_lg;

        if (*forward == 1) seq_current_node = subSequence(n_current_node->attribute, overlap_size, n_current_node_lg - 1);
        else {
            unsigned char* sub_current_node_overlap = subSequence(n_current_node->attribute, 0, n_current_node_lg - overlap_size - 1);
            seq_current_node = reverseSequence(sub_current_node_overlap, 1);
            free(sub_current_node_overlap);
        }

        seq_current_node_lg = seqlen(seq_current_node);

        list* ens_vertexAux = list_copy(ens_vertex);
        list_add(ens_vertexAux, ht_current_node);

        // Comparaison et vérification des caractères de la séquence du noeud et de la séquence requête un par un
         while (current_pos_in_query<query_lg && current_pos_on_node<seq_current_node_lg && *hamming_distance_calculated <= treshold){
            //if (getChar(seq_current_node, current_pos_on_node) != getChar(query, current_pos_in_query)) hamming_distance_calculated++;
            current_pos_on_node++;
            current_pos_in_query++;
         }

        int* calc = malloc(sizeof(int));
        *calc = -position_in_query;
        list_add(ll_reminder, createDuo(calc,forward));

         if ( *hamming_distance_calculated<=treshold && current_pos_in_query >= query_lg && ens_vertex->first != NULL){
            list_add(ens_result, createDuo(ens_vertexAux,hamming_distance_calculated));
        }
        else if (current_pos_in_query < query_lg && *hamming_distance_calculated<=treshold) {

            cell* elem_children_current_node = n_current_node->children->first;

            while (elem_children_current_node != NULL){

                Duo* d = (Duo*)elem_children_current_node->val;
                int code_child = *((int*)d->data2);
                HTItem* ht_child = (HTItem*)d->data1;

                if (val1Forward(code_child) == *forward){
                    int* val2 = malloc(sizeof(int));
                    *val2 = val2Forward(code_child);
                    extendHammingAux(ht_child, query, query_lg, current_pos_in_query, *hamming_distance_calculated, val2, treshold, overlap_size, ens_vertexAux, reminder, ens_result);
                    //free(val2);
                }

                elem_children_current_node = elem_children_current_node->prox;
            }
        }
        else {
            list_free(ens_vertexAux);
        }

        free(seq_current_node);
    }
}
