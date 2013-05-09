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

#ifndef DEF_EXTEND_LEV
#define DEF_EXTEND_LEV

#include "Duo.h"
#include "list.h"
#include "PartialDP_XDrop.h"
#include "Node.h"

void extendLevenshtein (Node* n_current_node, int posOnNode, unsigned char* query, int query_lg, int position_on_query, char forward, char dir, int costIndel, int costMismatch, int costMatch,  int treshold, int overlap_size, list* reminder, list* ens_result);
void extendLevenshteinAux (Node* node_father, Node* n_current_node, unsigned char* seq_nodes_to_extend, PartialDP* matrix, int position_on_query_extend, int query_length, int next_position_to_compute, char forward, char dir, int costIndel, int costMismatch, int costMatch, int overlap_size, list* ens_vertex, list* reminder, list* ens_result, int inv);

void extendLevenshteinR (NodeR* n_current_node, int posOnNode, unsigned char* query, int query_lg, int position_on_query, char forward, char dir, int costIndel, int costMismatch, int costMatch,  int treshold, int overlap_size, list* reminder, list* ens_result);
void extendLevenshteinAuxR (NodeR* node_father, NodeR* n_current_node, unsigned char* seq_nodes_to_extend, PartialDP* matrix, int position_on_query_extend, int query_length, int next_position_to_compute, char forward, char dir, int costIndel, int costMismatch, int costMatch, int overlap_size, list* ens_vertex, list* reminder, list* ens_result);

#endif
