#ifndef DEF_EXTEND_HAMMING
#define DEF_EXTEND_HAMMING

#include <stdio.h>
#include <stdlib.h>
#include "Duo.h"
#include "list.h"
#include "hash.h"

void extendHamming(Duo* d_current_node, unsigned char* query, int query_lg, int position_on_query, int* forward, int treshold, int overlap_size, list* ens_vertex, list* reminder, list* ens_result);
void extendHammingAux (HTItem* ht_current_node, unsigned char* query, int query_lg, int position_in_query, int hamming_distance, int* forward, int treshold, int overlap_size, list* ens_vertex, list* reminder, list* ens_result);

#endif
