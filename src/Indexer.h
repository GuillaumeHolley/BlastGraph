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

#ifndef DEF_INDEXER
#define DEF_INDEXER

#include <stdio.h>
#include <stdlib.h>
#include <Judy.h>
#include "Node.h"

Pvoid_t indexGraph(Pvoid_t* network, int size_seeds, int overlap_size, char* reverse_comp);

void createIndexNode(PPvoid_t index, Node* n_current_node, int size_seeds, int overlap_size);
void createIndexNodeAux(PPvoid_t index, Node* n_start, Node* n_father, Node* n_current_node, int posI, int posStop, uint16_t startIndexing, int size_seeds, int overlap_size, unsigned char* sp, int forward);

void createIndexNodeR(PPvoid_t index, NodeR* n_current_node, int size_seeds, int overlap_size);
void createIndexNodeAuxR(PPvoid_t index, NodeR* n_start, NodeR* n_father, NodeR* n_current_node, int posI, int posStop, uint16_t startIndexing, int size_seeds, int overlap_size, unsigned char* sp, int forward);

void index_a_kmer(PPvoid_t index, char* seq, void* n_start_node, uint32_t i);

#endif
