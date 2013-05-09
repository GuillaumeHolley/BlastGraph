/**
 * Copyright INRIA and ENS, contributors Peterlongo and Chikhi
 * pierre.peterlongo@inria.fr
 * rayan.chikhi@irisa.fr
 *
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
/*
 * commons.h
 *
 *  Created on: 17 sept. 2010
 *      Author: ppeterlo
 */

#ifndef COMMONS_H_
#define COMMONS_H_
#include<stdio.h>
int artificial_overlap;
char comp ['t'+1];
char nuc [4];
char verbose;
char silent;
int size_seeds;
char * anykmer;
char export_mapped_reads;
FILE* file_reads_mapped;
char **  sort_strings (char ** strings, int number);
void print_rev_comp(char s[], FILE * out);
void revcomp(char s[], int len);
void rev(char s[], int len);
void init_static_variables();
char * to_upper (char  * word);
char * to_lower (char  * word);
char * format_comment(char * raw_comment);
int get_next_sequence_and_comments (FILE * file, char * sequence, char * comment);
int get_next_sequence (FILE * file, char * read);
int number_of_sequences_in_fasta_file(FILE * file);
int last_index_of(char * string, char character);

// macro to test if a variable is null (i.e., a malloc failed)
#define test_alloc( variable) {	if(variable == NULL){		fprintf(stderr,"cannot allocate memory for variable %s, exit\n",#variable);		exit(1);	}}
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

#endif /* COMMONS_H_ */
