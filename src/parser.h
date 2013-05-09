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

#ifndef DEF_PARSER
#define DEF_PARSER

#include <Judy.h>
#include "list.h"
#include "Duo.h"

typedef struct DataParser
{
    Pvoid_t net;
    char* nodeAttribute;
    char* edgeAttribute;
    char* reverseCompAttribute;
    long nb_nucl;
    long nb_node;
    long nb_edge;
} DataParser;

Pvoid_t parse(const char * filename, const char * nodeAttribute, const char * edgeAttribute, char* reverse_comp_att);
DataParser* createDataParser(const char * nodeAttr, const char * edgeAttr, char* reverseAttr);
DuoChar* getReadingDirection(char* reading);
list* parseFastaFile(char* filename, int LG_MAX_LIGNE_FASTA);
char val1Forward(char readingD);
char val2Forward(char readingD);
char invR(char reading);
char *str_del_char (const char *string, regex_t* regex);

#endif
