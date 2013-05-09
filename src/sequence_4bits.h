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

#ifndef DEF_SEQUENCE_4_BITS
#define DEF_SEQUENCE_4_BITS

unsigned char* createSequence(char *str);
int seqlen(unsigned char* seq);
int seqcmp(unsigned char* seq1, int position1, unsigned char* seq2, int position2, int costMatch, int costMismatch);
int getNucl(unsigned char* seq1, int position1);
unsigned char* reverseSequence(unsigned char* seq, int complement);
unsigned char* subSequence(unsigned char* seq, int posDeb, int posFin);
unsigned char* concatSequence(unsigned char* seq1, unsigned char* seq2);
char *substr(const char *src,int pos,int len);
unsigned char reverseCompChar(unsigned char c);
unsigned char reverseNucl(unsigned char c);

#endif
