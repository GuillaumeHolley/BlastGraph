/**
 * Copyright INRIA and ENS, contributors Peterlongo and Chikhi
 * pierre.peterlongo@inria.fr
 * rayan.chikhi@irisa.fr
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
 * commons.c
 *
 *  Created on: 17 sept. 2010
 *      Author: ppeterlo
 */

#include"commons.h"
#include <ctype.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>



static int
cmpstringp(const void *p1, const void *p2)
{
	/* Les arguments de cette fonction sont des "pointeurs de
              pointeurs sur des caractères", mais les arguments de
              strcmp(3) sont des "pointeurs sur des caractères", d’où
              le forçage de type et l’utilisation de l’astérisque */

	return strcmp(* (char * const *) p1, * (char * const *) p2);
}



char ** sort_strings (char ** strings, int number)
{
	qsort(strings,number, sizeof(char *), cmpstringp);
	return strings;
}


void init_static_variables(){
	int i;
	for (i=0;i<'T'+1;i++) comp[i]=i; // for other iupac alphabet letters
	comp['A']='T';
	comp['T']='A';
	comp['C']='G';
	comp['G']='C';
	comp['a']='t';
	comp['t']='a';
	comp['c']='g';
	comp['g']='c';

	nuc[0]='A';
	nuc[1]='C';
	nuc[2]='G';
	nuc[3]='T';
	anykmer = (char *) malloc(size_seeds+1); test_alloc(anykmer);
}

void print_rev_comp(char s[], FILE * out){
	int i;
	const int len=strlen(s);
	for(i=len-1;i>-1;i--)fprintf(out, "%c",comp[(int)s[i]]);
}

void revcomp(char s[], int len)
{
	int i;
	char t;
	for (i=0;i<len/2;i++)
	{
		t=s[i];
		s[i] = comp [(int)(s[len-i-1])];
		s[len-i-1] = comp [(int)(t)];
	}
	if (len%2==1)
		s[len/2]=comp[(int)(s[len/2])];

}

void rev(char s[], int len)
{
	int i;
	char t;
	for (i=0;i<len/2;i++)
	{
		t=s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = t;
	}
	if (len%2==1)
		s[len/2]=s[len/2];
}

char * to_upper (char  * word){
	int i=0;
//	printf("before upper=%s %c\n", word, word[0]);
	while(word[i]!='\0')
		{
//			printf("%d %c %d", i, word[i], word[i]);
			word[i]=toupper(word[i]);
//			printf(" -> %c |", word[i]);
			i++;
		}
//	printf("after  upper=%s\n", word);
	return word;
}

char * to_lower (char  * word){
	int i=0;
	while(word[i]!='\0') {word[i]=tolower(word[i]); i++;}
	return word;
}

char line[1048576];

/**
 * removes eventual first '>' character
 * remove eventual last '\n' character
 * duplicate the raw_comment
 */
char * format_comment(char * raw_comment){
	if(raw_comment[0]=='>') raw_comment++;
	int l = strlen(raw_comment);
	if(raw_comment[l-1]=='\n' || raw_comment[l-1]=='\r') raw_comment[l-1]='\0';
	return strdup(raw_comment);
}

int get_next_sequence_and_comments (FILE * file, char * sequence, char * comment){
	char *rv;
	char *p;
	int nextchar=0;
	rv=fgets((char *)comment,1048576,file);// read comment ('>read00xxxx...\n')

	if(rv == NULL) return 0;
	do{
		rv=fgets((char *)sequence,1048575,file); //
	}while(sequence[0]=='>');


	p = (char *)strchr((char*)sequence, '\n');
	if (p) *p = '\0';
	p = (char *)strchr((char*)sequence, '\r');
	if (p) *p = '\0';

	nextchar=fgetc(file); // cheat, reads the next '>' character in order to induce EOF

	while (nextchar!='>' && !feof(file))
	{
		fseek(file, -1, SEEK_CUR);
		rv=fgets((char *)line,1048576,file);// read comment ('>read00xxxx...\n')
		rv = strchr(line, '\n'); // find the last \n char
		if(rv) *rv = '\0';       // change it into \0
		rv = strchr(line, '\r'); // find the last \r char
		if(rv) *rv = '\0';       // change it into \0

		strcat(sequence, line); // concat the restult in the sequence

		nextchar=fgetc(file); // cheat, reads the next '>' character in order to induce EOF
	}
	to_upper(sequence);
	//printf("return sequence %s\n",sequence);
	return strlen(sequence); // readlen
}

int get_next_sequence (FILE * file, char * sequence){
	char *rv;
	char *p;
	int nextchar=0;
	rv=fgets((char *)line,1048576,file);// read comment ('>read00xxxx...\n')
	if(rv == NULL) return 0;
	do{
		rv=fgets((char *)sequence,1048575,file); //
	}while(sequence[0]=='>');


	p = (char *)strchr((char*)sequence, '\n');
	if (p) *p = '\0';
	p = (char *)strchr((char*)sequence, '\r');
	if (p) *p = '\0';

	nextchar=fgetc(file); // cheat, reads the next '>' character in order to induce EOF

	while (nextchar!='>' && !feof(file))
	{
		fseek(file, -1, SEEK_CUR);
		rv=fgets((char *)line,1048576,file);// read line ('>read00xxxx...\n')
		rv = strchr(line, '\n'); // find the last \n char
		if(rv) *rv = '\0';       // change it into \0
		rv = strchr(line, '\r'); // find the last \r char
		if(rv) *rv = '\0';       // change it into \0

		strcat(sequence, line); // concat the restult in the sequence

		nextchar=fgetc(file); // cheat, reads the next '>' character in order to induce EOF
	}
//	printf("return sequence %s\n",sequence);
	to_upper(sequence);
//	printf("after up return sequence %s\n",sequence);
	return strlen(sequence); // readlen
}

int number_of_sequences_in_fasta_file(FILE * file){
	int sequences_number=0;
	int previous_is_a_comment=0;
	rewind(file);
	char line[1048576];
	do{
		if(fgets((char *)line,1048576,file) != NULL) {
			if(line[0]=='>'){
				if(!previous_is_a_comment){
					previous_is_a_comment=1;
					sequences_number++;
				}
			}
			else previous_is_a_comment=0;
		}
		else{
			break;
		}
	}
	while(1);
	rewind(file);
//	if(!silent) printf("Read file contains %d reads\n", sequences_number);
	return sequences_number;
}

int last_index_of(char * string, char character){
	int i, pos=-1;
	for(i=0;i<strlen(string);i++) if(string[i]==character) pos=i;
	return pos;
}
