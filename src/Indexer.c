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

#include "sequence_4bits.h"
#include "Indexer.h"
#include "list.h"
#include "listNodeUint16.h"
#include "listNodeChar.h"
#include "Duo.h"
#include "Node.h"

#define MAXLINE 100

Pvoid_t indexGraph(Pvoid_t* network, int size_seeds, int overlap_size, char* reverse_comp){

    if (network != NULL)
    {
        Pvoid_t index = (Pvoid_t) NULL;

        Word_t* PValue;
        uint8_t   keyNode[MAXLINE];
        keyNode[0] = '\0';

        JSLF(PValue, *network, keyNode);

        if (reverse_comp == NULL){
            while (PValue != NULL)
            {
                createIndexNode(&index, (Node*)*PValue, size_seeds, overlap_size);
                JSLN(PValue, *network, keyNode);
            }
        }
        else {
            while (PValue != NULL)
            {
                createIndexNodeR(&index, (NodeR*)*PValue, size_seeds, overlap_size);
                JSLN(PValue, *network, keyNode);
            }
        }

        return index;
    }
    else {
        fprintf (stderr, "Insufficient memory\n");
        exit (EXIT_FAILURE);
    }
}

void createIndexNode(PPvoid_t index, Node* n_current_node, int size_seeds, int overlap_size){
    int posOnSeq=0;
    int n_current_node_lg = seqlen(n_current_node->attribute);

    //On indexe les k-mers contenues dans la séquence du noeud
    for (posOnSeq=0; posOnSeq < n_current_node_lg-size_seeds; posOnSeq+=1){
        index_a_kmer(index, (char*)subSequence(n_current_node->attribute, posOnSeq, posOnSeq+size_seeds-1), n_current_node, (uint32_t)posOnSeq);
    }

    // On parcours les fils pour indexer les k-mers qui commencent sur ce noeud et qui sont répartis sur des noeuds fils via creerIndexAuxString()
    cell_NodeChar* elem_list = n_current_node->childrenStoT->first;
    while (elem_list) {
        if (val1Forward(elem_list->val) == 1){

            createIndexNodeAux(
                        index,
						n_current_node, // node init
						n_current_node, // node father
						elem_list->node, // node child
						posOnSeq+1,  // where we are in the original sequence
						n_current_node_lg,  // where we stop in the original sequence
						posOnSeq+1,
						size_seeds,
						overlap_size,
						n_current_node->attribute,
						val2Forward(elem_list->val));
        }

        elem_list = elem_list->prox;
    }
}

void createIndexNodeAux(PPvoid_t index, Node* n_start, Node* n_father, Node* n_current_node, int posI, int posStop, uint16_t startIndexing, int size_seeds, int overlap_size, unsigned char* sp, int forward){
    unsigned char* seq = NULL;
    int seq_lg;

    if (forward == 1){
        unsigned char* sub_current_node_overlap = subSequence(n_current_node->attribute, overlap_size, seqlen(n_current_node->attribute) - 1);
        seq = concatSequence(sp,sub_current_node_overlap);
        free(sub_current_node_overlap);
    }
    else{
        unsigned char* sub_current_node_overlap = subSequence(n_current_node->attribute, 0, seqlen(n_current_node->attribute) - overlap_size - 1);
        unsigned char* rev = reverseSequence(sub_current_node_overlap, 1);
        seq = concatSequence(sp,rev);
        free(rev);
        free(sub_current_node_overlap);
    }
    seq_lg = seqlen(seq);

     if (seq_lg < posStop+size_seeds){

        //on indexe tous les kmers débutants entre la position posI et posStop (exclue) si la sequence est assez longue. Sinon on descend.
        int i;
        for(i=startIndexing;i+size_seeds<=seq_lg && i<posStop;i+=1){
            index_a_kmer(index, (char*)subSequence(seq, i, i+size_seeds-1),n_start, (uint32_t)i);
        }

        cell_NodeChar* elem_list = n_current_node->childrenStoT->first;
        while (elem_list){

             if (strcmp(n_father->id,((Node*)elem_list->node)->id) != 0 && strcmp(n_current_node->id,((Node*)elem_list->node)->id) != 0){
                 if (val1Forward(elem_list->val) == forward){
                        createIndexNodeAux(
                                index,
								n_start, // still the same origine
								n_current_node, // I'm your father
								elem_list->node, // the called node
								posI, // original position doest not change
								posStop,
								i,
								size_seeds,
								overlap_size,
								seq, // send the sequence
								val2Forward(elem_list->val));
                 }
             }

             elem_list = elem_list->prox;
        }
    }

    free(seq);
}

void createIndexNodeR(PPvoid_t index, NodeR* n_current_node, int size_seeds, int overlap_size){
    int posOnSeq;
    int n_current_node_lg = seqlen(n_current_node->attribute);

    //On indexe les k-mers contenues dans la séquence du noeud
    for (posOnSeq=0; posOnSeq<n_current_node_lg-size_seeds; posOnSeq+=1){
        index_a_kmer(index, (char*)subSequence(n_current_node->attribute, posOnSeq, posOnSeq+size_seeds-1), (void*)n_current_node, (uint32_t)posOnSeq);
    }

    // On parcours les fils pour indexer les k-mers qui commencent sur ce noeud et qui sont répartis sur des noeuds fils via creerIndexAuxString()
    if (posOnSeq < n_current_node_lg){
        cell_NodeChar* elem_list = n_current_node->childrenStoT->first;
        while (elem_list) {
            if (val1Forward(elem_list->val) == 1){

                createIndexNodeAuxR(
                            index,
                            n_current_node, // node init
                            n_current_node, // node father
                            elem_list->node, // node child
                            posOnSeq+1,  // where we are in the original sequence
                            n_current_node_lg,  // where we stop in the original sequence
                            posOnSeq+1,
                            size_seeds,
                            overlap_size,
                            n_current_node->attribute,
                            val2Forward(elem_list->val));
            }

            elem_list = elem_list->prox;
        }
    }
}

void createIndexNodeAuxR(PPvoid_t index, NodeR* n_start, NodeR* n_father, NodeR* n_current_node, int posI, int posStop, uint16_t startIndexing, int size_seeds, int overlap_size, unsigned char* sp, int forward){
    unsigned char* sub_current_node_overlap = NULL;
    unsigned char* seq = NULL;
    int seq_lg;

    //printf("NodeAux = %s \n", n_current_node->id);

    if (forward == 1) sub_current_node_overlap = subSequence(n_current_node->attribute, overlap_size, seqlen(n_current_node->attribute) - 1);
    else sub_current_node_overlap = subSequence(n_current_node->attributeR, 0, seqlen(n_current_node->attributeR) - overlap_size - 1);

    seq = concatSequence(sp,sub_current_node_overlap);
    seq_lg = seqlen(seq);

    free(sub_current_node_overlap);

     if (seq_lg < posStop+size_seeds){

        //on indexe tous les kmers débutants entre la position posI et posStop (exclue) si la sequence est assez longue. Sinon on descend.
        int i;
        for(i=startIndexing;i+size_seeds<=seq_lg && i<posStop;i+=1){
            index_a_kmer(index, (char*)subSequence(seq, i, i+size_seeds-1),(void*)n_start,(uint32_t)i);
        }

        cell_NodeChar* elem_list = n_current_node->childrenStoT->first;
        while (elem_list){

             if (strcmp(n_current_node->id,((NodeR*)elem_list->node)->id) != 0 && strcmp(n_father->id,((NodeR*)elem_list->node)->id) != 0){
                 if (val1Forward(elem_list->val) == forward){
                        createIndexNodeAuxR(
                                index,
								n_start, // still the same origine
								n_current_node, // I'm your father
								elem_list->node, // the called node
								posI, // original position doest not change
								posStop,
								i,
								size_seeds,
								overlap_size,
								seq, // send the sequence
								val2Forward(elem_list->val));
                 }
             }

             elem_list = elem_list->prox;
        }
    }

    free(seq);
}

void index_a_kmer(PPvoid_t index, char* seq, void* n_start_node, uint32_t i){
    Word_t* PValue = NULL;
    list_NodeUint16* ll = NULL;

    JSLG(PValue, *index, seq)

    if (PValue == NULL){
        ll = list_create_NodeUint16();

        JSLI(PValue, *index, seq);
        if (PValue == PJERR)
        {
            printf("Malloc failed while inserting node in the graph - not enough memory n");
            exit(1);
        }

        *PValue = (Word_t)ll;
        list_add_NodeUint16(ll, n_start_node, i);
    }
    else list_add_NodeUint16((list_NodeUint16*)*PValue, n_start_node, i);

    free(seq);
}
