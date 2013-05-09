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
#include <limits.h>
#include "sequence_4bits.h"

#define MASK_0_1 15
#define MASK_1_0 240
#define MASK_1_1 255

enum {NUCLEO_0, NUCLEO_A, NUCLEO_C, NUCLEO_M, NUCLEO_R, NUCLEO_V, NUCLEO_H, NUCLEO_W, NUCLEO_S, NUCLEO_D, NUCLEO_B, NUCLEO_Y, NUCLEO_K, NUCLEO_G, NUCLEO_T_U, NUCLEO_N, NUCLEO_IGN};
//--------------------------------------------------------------
unsigned char* createSequence(char *str)
{
    int lg, i, dec;
    int nucleo;
    unsigned char * seq;
    unsigned char * pseq;
    //Initialisation du tableau de caractère
    lg = strlen(str);
    dec = lg%2;
    lg = lg/2 + (dec != 0);
    seq = malloc((lg+1)* sizeof(unsigned char));
    if (seq != NULL)
    {
      //lire la séquence
       for(i = 0, dec = 0 ;*str != '\0'; str++)
       {
          switch(*str)
          {
             case 'a' :
             case 'A' : nucleo = NUCLEO_A;   break;
             case 'c' :
             case 'C' : nucleo = NUCLEO_C;   break;
             case 'g' :
             case 'G' : nucleo = NUCLEO_G;   break;
             case 'u' :
             case 'U' :
             case 't' :
             case 'T' : nucleo = NUCLEO_T_U;   break;
             case 'm' :
             case 'M' : nucleo = NUCLEO_M;   break;
             case 'r' :
             case 'R' : nucleo = NUCLEO_R;   break;
             case 'w' :
             case 'W' : nucleo = NUCLEO_W;   break;
             case 's' :
             case 'S' : nucleo = NUCLEO_S;   break;
             case 'y' :
             case 'Y' : nucleo = NUCLEO_Y;   break;
             case 'k' :
             case 'K' : nucleo = NUCLEO_K;   break;
             case 'v' :
             case 'V' : nucleo = NUCLEO_V;   break;
             case 'h' :
             case 'H' : nucleo = NUCLEO_H;   break;
             case 'd' :
             case 'D' : nucleo = NUCLEO_D;   break;
             case 'b' :
             case 'B' : nucleo = NUCLEO_B;   break;
             case 'n' :
             case 'N' : nucleo = NUCLEO_N;   break;
             case ' ' :
             case '\n': nucleo = NUCLEO_IGN; break;
             default  : printf("Invalid character encountered : - Operation aborted");
                        free(seq);
                        exit(0);
          }
          if(nucleo != NUCLEO_IGN) // ne traiter que si c'est un caractère valide
          {
             if (dec==0){
                seq[i] = nucleo << 4;
                dec++;
             }
             else {
                seq[i] |=  nucleo;
                dec=0;
                i++;
             }
          }
       } // fin de lecture
       if (dec==1) i++;
       if (i>lg){
           pseq = realloc(seq,i+1);    // redimensionner le tableau
            if(pseq != NULL) seq = pseq;
       }
       seq[i] = '\0';             // et le terminer
    }
    return seq;
}
//

int seqlen(unsigned char* seq){
    int lg = strlen(seq);
    int dec = seq[lg-1] & MASK_0_1;

    if (dec == 0) return (lg-1)*2+1;
    return 2*lg;
}

int seqcmp(unsigned char* seq1, int position1, unsigned char* seq2, int position2, int costMatch, int costMismatch){
    int nb1, nb2;

    switch (position1%2){
        case 1: nb1 = seq1[position1/2] & MASK_0_1; break;
        case 0: nb1 = (seq1[position1/2] & MASK_1_0) >> 4; break;
        default: exit(EXIT_FAILURE);
    }

    switch (position2%2){
        case 1: nb2 = seq2[position2/2] & MASK_0_1; break;
        case 0: nb2 = (seq2[position2/2] & MASK_1_0) >> 4; break;
        default: exit(EXIT_FAILURE);
    }

    if (nb1 == nb2){
        switch (nb1){
            case NUCLEO_A: return costMatch;
            case NUCLEO_C: return costMatch;
            case NUCLEO_T_U: return costMatch;
            case NUCLEO_G: return costMatch;
            default: return INT_MIN;
        }
    }

    switch (nb1){
        case NUCLEO_A:
        case NUCLEO_C:
        case NUCLEO_T_U:
        case NUCLEO_G: break;
        default: return INT_MAX;
    }

    switch (nb2){
        case NUCLEO_A: return costMismatch;
        case NUCLEO_C: return costMismatch;
        case NUCLEO_T_U: return costMismatch;
        case NUCLEO_G: return costMismatch;
        default: return INT_MIN;
    }
}

int getNucl(unsigned char* seq1, int position1){
    int nb1;

    switch (position1%2){
        case 1: nb1 = seq1[position1/2] & MASK_0_1; break;
        case 0: nb1 = (seq1[position1/2] & MASK_1_0) >> 4; break;
        default: exit(EXIT_FAILURE);
    }

    switch (nb1){
        case NUCLEO_A:
        case NUCLEO_C:
        case NUCLEO_T_U:
        case NUCLEO_G: return nb1;
        default: return INT_MAX;
    }
}

unsigned char* reverseSequence(unsigned char* seq, int complement){
    int i=0, lg, seq_lg = seqlen(seq);

    //Calcul de la longueur du tableau de caractère
    lg = strlen(seq);
    char *newSeq = malloc((lg+1)* sizeof(unsigned char));

    if (newSeq != NULL){
        if (complement==0){
            for (i=0; i<lg; i++){
                newSeq[i] = reverseCompChar(seq[i]);
            }
            if (seq_lg%2==1) newSeq[i-1] &= MASK_1_0;
            newSeq[lg] = '\0';
            return newSeq;
        }

        if (lg > 1){
            for (i=0; i<lg/2; i++){
                newSeq[i] = reverseCompChar(seq[lg-i-1]);
                newSeq[lg-i-1] = reverseCompChar(seq[i]);
            }

            if (lg%2 == 1) newSeq[i] = reverseCompChar(seq[i]);
            newSeq[lg] = '\0';

            if (seq_lg%2 == 1){
                char* res = subSequence(newSeq, 1, (lg*2)-1);
                free(newSeq);
                return res;
            }
        }
        else{
            newSeq[i] = reverseCompChar(seq[i]);
            if (seq_lg%2==1) newSeq[i] <<= 4;
            newSeq[lg] = '\0';
        }

        return newSeq;
    }
    else {
        fprintf (stderr, "Insufficient memory\n");
        exit (EXIT_FAILURE);
    }
}

unsigned char* subSequence(unsigned char* seq, int posDeb, int posFin){

    int i, k=0, lg, newSeq_lg, seq_lg, dec;
    unsigned char tmp1;
    unsigned char* newSeq;

    //Calcul de la longueur du tableau de caractère
    newSeq_lg = posFin-posDeb+1;
    seq_lg = seqlen(seq);
    dec = newSeq_lg%2;
    lg = newSeq_lg/2 + (dec != 0);

    newSeq = malloc((lg+1) * sizeof(unsigned char));

    if (newSeq != NULL){
        if (posDeb%2 == 0){
            for (i = posDeb/2; i<posFin/2; i++){
                newSeq[k] = seq[i];
                k++;
            }
            if (dec == 1) newSeq[k] = seq[i] & MASK_1_0;
            else newSeq[k] = seq[i];
        }
        else {
            for (i = posDeb/2; i<posFin/2; i++){
                tmp1 = seq[i] << 4;
                if (seq_lg > 2) tmp1 |= (seq[i+1] >> 4);
                newSeq[k] = tmp1;
                k++;
            }
            if (dec == 1) newSeq[k] = seq[i] << 4;
        }

        newSeq[lg] = '\0';

        return newSeq;
    }
    else {
        fprintf (stderr, "Insufficient memory\n");
        exit (EXIT_FAILURE);
    }
}

unsigned char* concatSequence(unsigned char* seq1, unsigned char* seq2){
    int lgTab1, lgTab2, i, k, lgTmp, decTmp = 0;
    int seq_lg = seqlen(seq1) + seqlen(seq2);
    unsigned char* seq;

    lgTmp = seq_lg/2 + (seq_lg%2 != 0);

    // Calcul de la longueur du tableau de la séquence 1
    lgTab1 = strlen(seq1);
    lgTab2 = strlen(seq2);

    seq = malloc((lgTmp+1) * sizeof(unsigned char));

    // Recopie du tableau de la séquence 1 dans la nouvelle séquence
    for (i=0; i<lgTab1; i++){
        seq[i] = seq1[i];
    }

    if ((seq1[i-1] & MASK_0_1) == 0) decTmp = 1;

    // Si aucun décalage dans la séquence 1, je recopie le tableau de la séquence 2 à la suite du 1 dans la nouvelle séquence
    if (decTmp == 0){
        for (k=0; k<lgTab2; k++){
            seq[i] = seq2[k];
            i++;
        }
    }
    else {
        // Gestion du décalage entre la dernière ligne du premier tableau et la première ligne du dernier tableau

        seq[i-1] |= (seq2[0] >> 4);
        if (i < lgTmp) seq[i] = seq2[0] << 4;

        // Recopie du deuxième tableau avec gestion du décalage
        for (k=0; k<lgTab2-1; k++){
            seq[i] |= seq2[k+1] >> 4;
            seq[i+1] = seq2[k+1] << 4;
            i++;
        }
    }

    seq[lgTmp]= '\0';

    return seq;
}

unsigned char reverseCompChar(unsigned char c){
   return reverseNucl(c >> 4) | (reverseNucl(c) << 4);
}

unsigned char reverseNucl(unsigned char c){
    switch (c){
        case 7:
        case 8:
        case 15: return c;
        default: return ~c & MASK_0_1;
    }
}
