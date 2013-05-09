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

#include "PartialDP_XDrop.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sequence_4bits.h"
#include "misc_tools.h"

PartialDP* createPartialDP(unsigned char* attribute, int costIndel, int x_value){

    PartialDP* partial_dp = malloc(sizeof(PartialDP));

    if (partial_dp != NULL){
        partial_dp->query = attribute;
        partial_dp->nbCol = seqlen(attribute) + 1;
        partial_dp->current_line = 1;
        partial_dp->A_etoile = 0;
        partial_dp->colg = 1;
        partial_dp->cold = partial_dp->nbCol-1;
        partial_dp->treshold = x_value;

        partial_dp->data = malloc(partial_dp->nbCol * sizeof(int));
        if (partial_dp->data != NULL){
            int i;
            partial_dp->data[0] = 0;

            for (i=1;i<partial_dp->nbCol;i++){
                if (getNucl(partial_dp->query, i-1) == INT_MAX) partial_dp->data[i] = partial_dp->data[i-1];
                else partial_dp->data[i] = partial_dp->data[i-1] + costIndel;
            }
        }
        else {
            fprintf (stderr, "insufficient memory to create a partial_dp->data of size %d\n", partial_dp->nbCol+1);
            exit (EXIT_FAILURE);
        }

        return partial_dp;
    }
    else {
        fprintf (stderr, "insufficient memory to create a partial_dp \n");
        exit (EXIT_FAILURE);
    }
}

void freePartialDP(PartialDP* partial_dp){
    /*int i;
    for (i=0;i<partial_dp->nbCol;i++){
        free(partial_dp->data[i]);
    }*/
    free(partial_dp->data);
    free(partial_dp);
}

void printPartialDP(PartialDP* partial_dp){
    int j;
    for(j=0;j<partial_dp->nbCol;j++){
            if (partial_dp->data[j] == NULL || partial_dp->data[j] <= INT_MIN+2) printf("[---]",partial_dp->data[j]);
            else if (partial_dp->data[j] > 99) printf("[%d]",partial_dp->data[j]);
            else if (partial_dp->data[j] > 9) printf("[0%d]",partial_dp->data[j]);
            else if (partial_dp->data[j] < 0 && partial_dp->data[j] > -10) printf("[ %d]",partial_dp->data[j]);
            else if (partial_dp->data[j] < 0 && partial_dp->data[j] > -100) printf("[%d]",partial_dp->data[j]);
            else printf("[00%d]",partial_dp->data[j]);
    }
    printf("\n");
}

int computePartialDP(PartialDP* partial_dp, unsigned char* graphString, int costIndel, int costMismatch, int costMatch){

    int j;
    int graphString_lg = seqlen(graphString);

    while (partial_dp->current_line<partial_dp->nbCol && partial_dp->current_line<=graphString_lg && partial_dp->colg <= partial_dp->cold){
        j=partial_dp->colg;
        int tmp = partial_dp->data[j-1];

        if (getNucl(graphString, j-1) != INT_MAX) partial_dp->data[0] += costIndel;

        while (j<=min(partial_dp->cold+1, partial_dp->nbCol-1)){
            int cmp = seqcmp(graphString, partial_dp->current_line-1, partial_dp->query, j-1, costMatch, costMismatch);

            int tmp2 = tmp;
            tmp = partial_dp->data[j];

            if (cmp == INT_MAX) partial_dp->data[j] = partial_dp->data[j-1];
            else if (cmp != INT_MIN) partial_dp->data[j]=max3(tmp2+cmp, partial_dp->data[j]+costIndel, partial_dp->data[j-1]+costIndel);

            if (partial_dp->data[j] > partial_dp->A_etoile) partial_dp->A_etoile = partial_dp->data[j];
            else if (partial_dp->data[j] < partial_dp->A_etoile - partial_dp->treshold) partial_dp->data[j] = INT_MIN+2;

            //printf("colg = %d \t j = %d \t Cmp: %d \t Alt1: %d \t Alt2: %d \t Alt3: %d \t Res: %d\n", partial_dp->colg, j, cmp, tmp+cmp, partial_dp->data[j]+costIndel, partial_dp->data[j-1]+costIndel, partial_dp->data[j]);

            j++;

        }

        while (partial_dp->colg <= partial_dp->cold && partial_dp->data[partial_dp->colg] == INT_MIN+2){
            partial_dp->colg++;
            if (partial_dp->cold < partial_dp->nbCol -1) partial_dp->cold++;
        }

       while (partial_dp->colg <= partial_dp->cold && partial_dp->data[partial_dp->cold] == INT_MIN+2){
            partial_dp->cold--;
        }

        //printPartialDP(partial_dp);

        partial_dp->current_line++;
    }

    int res =INT_MIN+2;
    for(j=1;j<partial_dp->nbCol;j++){
        if(res<partial_dp->data[j]) res = partial_dp->data[j];
    }

    return res;
}

PartialDP* copyPartialDP(PartialDP* partial_dp){

    PartialDP* new_partial_dp = malloc(sizeof(PartialDP));

    if (new_partial_dp != NULL){
        new_partial_dp->query = partial_dp->query;
        new_partial_dp->nbCol = partial_dp->nbCol;
        new_partial_dp->current_line = partial_dp->current_line;
        new_partial_dp->A_etoile = partial_dp->A_etoile;
        new_partial_dp->colg = partial_dp->colg;
        new_partial_dp->cold = partial_dp->cold;
        new_partial_dp->treshold = partial_dp->treshold;

        new_partial_dp->data = malloc(new_partial_dp->nbCol * sizeof(int));
        if (partial_dp->data != NULL){
            int i;
            for (i=0;i<partial_dp->nbCol;i++){
                new_partial_dp->data[i] = partial_dp->data[i];
            }
        }
        else {
            fprintf (stderr, "insufficient memory to create a partial_dp->data of size %d\n", partial_dp->nbCol+1);
            exit (EXIT_FAILURE);
        }

        return new_partial_dp;
    }
    else {
        fprintf (stderr, "insufficient memory to create a partial_dp \n");
        exit (EXIT_FAILURE);
    }
}

