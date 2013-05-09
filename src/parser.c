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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <regex.h>
#include "Node.h"
#include "parser.h"
#include "Duo.h"

void debut_element(void *user_data, const xmlChar *name, const xmlChar **attrs) {
    DataParser* dp = (DataParser*)user_data;
     if (xmlStrEqual(name, BAD_CAST "node")) {
         char* id = NULL;
         char* att = NULL;
         char* rev = NULL;
         if (NULL != attrs) {
            int i;
            for (i = 0; attrs[i] != NULL; i+=2) {
                if (xmlStrEqual(attrs[i], BAD_CAST dp->nodeAttribute)) {
                    att = calloc(strlen((char *) attrs[i+1]) + 1, sizeof(char));
                    strcpy(att, (char *) attrs[i+1]);
                }
                else if (xmlStrEqual(attrs[i], BAD_CAST "id")) {
                    id = calloc(strlen((char *) attrs[i+1]) + 1, sizeof(char));
                    strcpy(id, (char *) attrs[i+1]);
                }
                else if (xmlStrEqual(attrs[i], BAD_CAST dp->reverseCompAttribute)) {
                    rev = calloc(strlen((char *) attrs[i+1]) + 1, sizeof(char));
                    strcpy(rev, (char *) attrs[i+1]);
                }
            }

            if (id != NULL){
                if(att != NULL) {

                    Word_t* PValue;
                    dp->nb_nucl += (long) strlen((char *) att);

                    JSLI(PValue, dp->net, id);
                    if (PValue == PJERR) {
                        printf("Malloc failed while inserting node in the graph - not enough memory n");
                        exit(1);
                    }

                    if (dp->reverseCompAttribute != NULL){
                        if (rev != NULL){
                            *PValue = (Word_t)createNodeR(id, att, rev);
                            dp->nb_node += 1;
                            free(rev);
                        }
                        else{
                            fprintf (stderr, "Missing reverse-complement sequence on one node while parsing graph\n");
                            exit (EXIT_FAILURE);
                        }
                    }
                    else{
                        *PValue = (Word_t)createNode(id, att);
                        dp->nb_node += 1;
                    }
                    free(att);
                }
                else {
                    fprintf (stderr, "Missing forward sequence on one node while parsing graph\n");
                    exit (EXIT_FAILURE);
                }
                free(id);
            }
            else {
                fprintf (stderr, "Missing identifier of one node while parsing graph\n");
                exit (EXIT_FAILURE);
            }
         }
     }
     else if (xmlStrEqual(name, BAD_CAST "edge")) {
        if (NULL != attrs) {
            int i;
            char* reading = NULL;
            Word_t* s = NULL;
            Word_t* t = NULL;
            for (i = 0; attrs[i] != NULL; i+=2) {
                if (xmlStrEqual(attrs[i], BAD_CAST dp->edgeAttribute)) {
                    int l = strlen((char *) attrs[i+1]) + 1;
                    reading = calloc(l, sizeof(char));
                    strcpy(reading, (char *) attrs[i+1]);
                }
                else if (xmlStrEqual(attrs[i], BAD_CAST "source")) {
                    JSLG(s, dp->net, (char *) attrs[i+1])
                }
                else if (xmlStrEqual(attrs[i], BAD_CAST "target")) {
                    JSLG(t, dp->net, (char *) attrs[i+1])
                }
            }

            if (reading != NULL && s != NULL && t != NULL){
                if (dp->reverseCompAttribute == NULL) dp->nb_edge += addNeigh((Node*)*s, (Node*)*t, reading);
                else dp->nb_edge += addNeighR((NodeR*)*s, (NodeR*)*t, reading);
                free(reading);
            }
         }
     }
}

Pvoid_t parse(const char * filename, const char * nodeAttribute, const char * edgeAttribute, char* reverse_comp_att){
    // Initialisation à zéro de tous les membres (NULL pour un pointeur par conversion)
    xmlSAXHandler sh = {0};

    DataParser* dp = createDataParser(nodeAttribute, edgeAttribute, reverse_comp_att);

    // Affectation des fonctions de rappel
    sh.startElement = debut_element;

    // Parsing du document XML
    if (xmlSAXUserParseFile(&sh, dp, filename) != 0) {
        fprintf(stderr, "Parsing error\n");
        exit (EXIT_FAILURE);
    }

    printf("\n\nNumber of nucleotides in the graph : %ld \n\n", dp->nb_nucl);
    printf("\n\nNumber of nodes in the graph : %ld \n\n", dp->nb_node);
    printf("\n\nNumber of edges in the graph : %ld \n\n", dp->nb_edge);

    Pvoid_t net = dp->net;

    free(dp->nodeAttribute);
    free(dp->edgeAttribute);
    free(dp);

    xmlCleanupParser();

    return net;
}

DataParser* createDataParser(const char * nodeAttr, const char * edgeAttr, char* reverseAttr){
    DataParser* dp = malloc(sizeof(DataParser));
    if (dp != NULL){
        dp->nb_nucl = 0;
        dp->nb_node = 0;
        dp->nb_edge = 0;
        dp->net = (Pvoid_t) NULL;
        dp->nodeAttribute = calloc(strlen(nodeAttr)+1, sizeof(char));

        if (dp->nodeAttribute != NULL){
            strcpy(dp->nodeAttribute, nodeAttr);
            dp->edgeAttribute = calloc(strlen(edgeAttr)+1, sizeof(char));

            if (dp->edgeAttribute != NULL){
                strcpy(dp->edgeAttribute, edgeAttr);
                if (reverseAttr != NULL){
                    dp->reverseCompAttribute = calloc(strlen(reverseAttr)+1, sizeof(char));
                    if (dp->reverseCompAttribute != NULL) strcpy(dp->reverseCompAttribute, reverseAttr);
                    else {
                        fprintf (stderr, "insufficient memory to create a DataParser structure \n");
                        exit (EXIT_FAILURE);
                    }
                }
                else dp->reverseCompAttribute = NULL;
            }
            else {
                fprintf (stderr, "insufficient memory to create a DataParser structure \n");
                exit (EXIT_FAILURE);
            }

        }
        else {
            fprintf (stderr, "insufficient memory to create a DataParser structure \n");
            exit (EXIT_FAILURE);
        }
    }
    else {
        fprintf (stderr, "insufficient memory to create a DataParser structure\n");
        exit (EXIT_FAILURE);
    }

    return dp;
}

DuoChar* getReadingDirection(char* reading){
    if (strlen(reading) != 2){
        fprintf (stderr, "Building phase undone : reading-direction value must have a length of 2 characters \n");
        exit (EXIT_FAILURE);
    }

    if (strcmp(reading,"FF") == 0 || strcmp(reading,"ff") == 0) return createDuoChar(0,3);
    else if (strcmp(reading,"FR") == 0 || strcmp(reading,"fr") == 0) return createDuoChar(1,1);
    else if (strcmp(reading,"RR") == 0 || strcmp(reading,"rr") == 0) return createDuoChar(3,0);
    else if (strcmp(reading,"RF") == 0 || strcmp(reading,"rf") == 0) return createDuoChar(2,2);
    else return 0;
}

char val1Forward(char readingD){
    if (readingD == 0 || readingD == 1) return 1;
    return 0;
}

char val2Forward(char readingD){
    if (readingD == 0 || readingD == 2) return 1;
    return 0;
}

char invR(char reading){
    if (reading == 0) return 1;
    return 0;
}

list* parseFastaFile(char* filename, int LG_MAX_LIGNE_FASTA){

    list* ll = list_create();
    char* ligne;
    char* ligne_tmp;
    const char *str_regex = "^[acgtumrwsykvhdbnACGTUMRWSYKVHDBN ]+";
    const char *str_regex2 = "^[acgtumrwsykvhdbnACGTUMRWSYKVHDBN]{1}";
    int err, err2;
    regex_t preg, preg2;
    FILE* file = fopen(filename, "r");

    if (file != NULL){
        ligne = calloc(LG_MAX_LIGNE_FASTA, sizeof(char));
        ligne_tmp = calloc(LG_MAX_LIGNE_FASTA, sizeof(char));

        if (ligne != NULL && ligne_tmp != NULL){
            while (fgets(ligne_tmp, LG_MAX_LIGNE_FASTA, file) != NULL){
                // On compile notre expression régulière
                err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
                err2 = regcomp (&preg2, str_regex2, REG_NOSUB | REG_EXTENDED);
                // Si pas d'erreur
               if (err == 0 && err2 == 0)
               {
                  int match;
                  // On exécute l'expression régulière
                  match = regexec (&preg, ligne_tmp, 0, NULL, 0);

                  // Si il y a correspondance
                  if (match == 0){
                    // On agrandit le contenu de la variable pour qu'elle puisse contenir les lignes déjà lues de la séquence FASTA + la nouvelle ligne
                    if (strlen(ligne)>0){

                        ligne = realloc(ligne, sizeof(char) * (strlen(ligne)+strlen(ligne_tmp)+1));
                        if (ligne != NULL){
                            // On copie le nouveau contenu dedans la nouvelle ligne
                            strcat(ligne,ligne_tmp);
                        }
                        else {
                            fprintf (stderr, "Insufficient memory\n");
                            exit (EXIT_FAILURE);
                        }
                    }
                    else{
                        strcpy(ligne,ligne_tmp);
                        /*char* replace = str_del_char(ligne, &preg2);

                        free(ligne);
                        ligne = calloc(strlen(replace)+1, sizeof(char));
                        strcpy(ligne, replace);

                        free(replace);*/
                    }
                  }
                  else if (match == REG_NOMATCH){
                      // Si la ligne commence par > ou ;
                      if (*ligne_tmp == '>' || *ligne_tmp == ';'){
                            //c'est qu'il s'agit d'une nouvelle séquence donc on insère la précédente dans la liste chainé sauf s'il s'agit de la première séquence du fichier
                          if (strlen(ligne)>0){
                              char* replace = str_del_char(ligne, &preg2);
                              //list_add_tail(ll,strcpy(calloc(strlen(ligne)+1,sizeof(char)),ligne));
                              list_add_tail(ll,strcpy(calloc(strlen(replace)+1,sizeof(char)),replace));
                              free(ligne);
                              free(replace);
                              ligne = calloc(LG_MAX_LIGNE_FASTA, sizeof(char));
                          }
                      }
                      // Sinon c'est une erreur
                      else if (strlen(ligne_tmp) > 1 ){
                          printf ("%s is not a valid FASTA sequence\n", ligne_tmp);
                          exit (EXIT_FAILURE);
                      }
                  }
                  else
                  {
                     char *text;
                     size_t size;

                    // On essaye de connaitre la taille du message d'erreur
                     size = regerror (err, &preg, NULL, 0);
                     text = malloc (sizeof (*text) * size);
                     if (text)
                     {
                        // On affiche le message d'erreur
                        regerror (err, &preg, text, size);
                        fprintf (stderr, "%s\n", text);
                        free (text);
                     }
                     else
                     {
                         // PLus de place en mémoire : on arrête le programme
                        fprintf (stderr, "Insufficient memory\n");
                        exit (EXIT_FAILURE);
                     }
                  }
               }

                // On libère l'espace alloué à notre expression régulière
                regfree (&preg);
                regfree (&preg2);
            }

            // On insère la dernière séquence du fichier, on ferme le fichier et on retourne la liste
            if (strlen(ligne)>0){
                char* replace = str_del_char(ligne, &preg2);
                //list_add_tail(ll,strcpy(calloc(strlen(ligne)+1,sizeof(char)),ligne));
                list_add_tail(ll,strcpy(calloc(strlen(replace)+1,sizeof(char)),replace));
                free(replace);
            }
        }
        else
        {
            fprintf (stderr, "Insufficient memory\n");
            exit (EXIT_FAILURE);
        }

        free(ligne);
        free(ligne_tmp);
    }
    else {
        fprintf (stderr, "this FASTA file does not exist \n");
        exit (EXIT_FAILURE);
    }

    fclose(file);

    return ll;
}

char *str_del_char (const char *string, regex_t* regex)
{
    int i=0, j=0;
    char *strip = calloc(strlen(string)+1, sizeof(char));

    if (string != NULL)
    {
        if (strip != NULL)
        {
            for (i = 0; i<strlen(string); i++){
                /*if (regexec (regex, string+i, 0, NULL, 0) == 0){
                    strip[j] = string[i];
                    j++;
                }*/
                if (string[i] != '\n' && string[i] != ' ' && string[i] != 0){
                    strip[j] = string[i];
                    j++;
                }
            }
            strip[j] = '\0';

            if((strip = realloc(strip, (j+1)*sizeof(char))) != NULL) return strip;
            fprintf (stderr, "Insufficient memory \n");
             exit (EXIT_FAILURE);

        }
        else
        {
         fprintf (stderr, "Insufficient memory \n");
         exit (EXIT_FAILURE);
        }
    }
    else
    {
     fprintf (stderr, "Insufficient memory\n");
     exit (EXIT_FAILURE);
    }
}
