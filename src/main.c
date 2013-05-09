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
#include <sys/time.h>
#include <sys/resource.h>
#include <regex.h>
#include <Judy.h>
#include "parser.h"
#include "list.h"
#include "listNodeUint16.h"
#include "listNodeChar.h"
#include "Indexer.h"
#include "extend.h"

/*========== parttie relative a la mesure du temps ===========*/
#include <sys/times.h>
#include <unistd.h>
typedef struct tms sTms;
typedef struct{
	int debut,fin;
	sTms sdebut, sfin;
}temps_exec;
/*========== parttie relative a la mesure du temps ===========*/

#define MAXLINE 100                 // max string (line) length

void temp(temps_exec *tmps){
    printf("Real time :\t %d cs\nUser time :\t %ld cs\nSystem time :\t %ld cs\n",
		tmps->fin - tmps->debut,
		tmps->sfin.tms_utime - tmps->sdebut.tms_utime,
		tmps->sfin.tms_stime - tmps->sdebut.tms_stime);
}

int main(int argc, char *argv[])
{
    if (argc >= 7 && argc <= 13){

        int max_nb_lines = 120;
        int xdrop_treshold = 0;
        char* reverse_comp_att = NULL;

        int i;
        for (i=7; i<argc; i+=2){
            if (strcmp(argv[i],"-r") == 0) reverse_comp_att = argv[i+1];
            else if (strcmp(argv[i],"-x") == 0) xdrop_treshold = atoi(argv[i+1]);
            else if (strcmp(argv[i],"-l") == 0) max_nb_lines = atoi(argv[i+1]);
        }

        // Initialisation du regex
        const char *str_regex = "^[acgtumrwsykvhdbnACGTUMRWSYKVHDBN]+";
        int err;
        regex_t preg;

        err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);

        // Initialisation outil pour connaitre la mémoire utilisée
        char buffer2 [255] = "smem -ntk";

        // Initialisation outil pour connaitre le temps utilisé
        temps_exec temps;
        temps.debut = times(&temps.sdebut);

        // On parse le fichier XGMML
        Pvoid_t net = parse(argv[1], argv[3], argv[4], reverse_comp_att);
        printf("Parsing XGMML file done \n\n");

        // Affichage mémoire utilisée
        /*printf("Memory used by the system after parsing graph \n\n");
        system(buffer2);
        printf("\n\n");
        fflush(stdout);*/

        // On parse le fichier FASTA
        list* list_queries = parseFastaFile(argv[2], max_nb_lines);
         printf("Parsing FASTA file done \n\n");
         fflush(stdout);

        // On indexe le graphe
        Pvoid_t index = indexGraph(&net, atoi(argv[5]), atoi(argv[6]), reverse_comp_att);
        printf("Indexing graph done \n\n");

        // Affichage mémoire utilisée
        /*printf("Memory used by the system after indexing graph \n\n");
        system(buffer2);
        printf("\n\n");*/

        // Affichage temps d'execution
        printf("Time after indexing graph : \n");
        temps.fin = times(&temps.sfin);
        temp(&temps);
        fflush(stdout);

        int nb_queries = 0;
        int found = 0;
        int not_found = 0;
        cell* elem_list_queries = list_queries->first;
        while (elem_list_queries){

                // Si pas d'erreur
               if (err == 0)
               {
                  int match;
                  // On exécute l'expression régulière
                  match = regexec (&preg, (char*)elem_list_queries->val, 0, NULL, 0);

                  // Si il y a correspondance
                  if (match == 0){

                    // On lance les extensions
                    int lAlign = NULL;
                    if (reverse_comp_att == NULL) lAlign = extend((char*)elem_list_queries->val, &index, atoi(argv[5]), atoi(argv[6]), xdrop_treshold, nb_queries);
                    else lAlign = extendR((char*)elem_list_queries->val, &index, atoi(argv[5]), atoi(argv[6]), xdrop_treshold, nb_queries);

                    // Analyse et affichage des résultats
                    (lAlign == 0) ? not_found++ : found++;

                  }
                  else{
                      not_found++;
                      printf("Invalid sequence : %s \n\n", (char*)elem_list_queries->val);
                      exit(0);
                  }
               }
               else printf("An error occured with the regex \n\n");

            elem_list_queries = elem_list_queries->prox;
            nb_queries++;
        }

        printf("Number of queries found : %d \n", found);
        printf("Number of queries not found : %d \n\n", not_found);

        // Affichage mémoire utilisée
        /*printf("Memory used by the system after extending queries \n\n");
        system(buffer2);
        printf("\n\n");*/

        // Affichage temps d'execution
        printf("Time after aligning graph : \n");
        temps.fin = times(&temps.sfin);
        temp(&temps);
        fflush(stdout);

        Word_t* PValue;
        Word_t Bytes;
        uint8_t   keyIndex[MAXLINE];
        uint8_t   keyNetwork[MAXLINE];
        keyIndex[0] = keyNetwork[0] = '\0';

        JSLF(PValue, index, keyIndex);
        while (PValue != NULL)
        {
            list_free_NodeUint16((list_NodeUint16*)*PValue);
            JSLN(PValue, index, keyIndex);
        }

        JSLFA(Bytes, index);

        JSLF(PValue, net, keyNetwork);

        if (reverse_comp_att == NULL){
            while (PValue != NULL)
            {
                freeNode((Node*)*PValue);
                JSLN(PValue, net, keyNetwork);
            }
        }
        else {
            while (PValue != NULL)
            {
                freeNodeR((NodeR*)*PValue);
                JSLN(PValue, net, keyNetwork);
            }

        }

        JSLFA(Bytes, net);

        list_of_generic_free(list_queries);

        // On libère l'espace alloué à notre expression régulière
        regfree (&preg);

        return 0;
    }
    else if (argc == 2){
        if (strcmp(argv[1], "-h") == 0){
            printf("BlastGraph <name_file_graph.xgmml> <name_query_file.fasta> <node_attribute> <edge_attribute> <seed_size> <overlap_size> [-options]\n\n");
            printf("<node_attribute> : the name of the attribute in the XGMML file (in the <node> marker) that contains the sequence of each node\n");
            printf("<edge_attribute> : the name of the attribute in the XGMML file (in the <node> marker) that contains the two letters indicating if the sequences of the source node and target node have to be read in forward (F) or reverse-complement (R)\n");
            printf("<seed_size> is the seed size used to anchor query sequences on the graph\n");
            printf("<overlap_size> is the size of the overlaps between the sequences source and target nodes\n\n");
            printf("[-options] : \n");
            printf("-r reverse_complement_attribute : take into account the reverse-complement identified by reverse_complement_attribute in the graph. By default, compute the reverse-complement of each sequence in each node identified by node_attribute.\n");
            printf("-x value : use this value as treshold for the X-DROP heuristic. 0 by default.\n");
            printf("-l value : use this value as the maximum number of characters per line in the query file. 120 by default.\n");
            return 0;
        }
        else{
            fprintf (stderr, "Bad number of parameters \n");
            exit (EXIT_FAILURE);
        }
    }
    else {
        fprintf (stderr, "Bad number of parameters \n");
        exit (EXIT_FAILURE);
    }
}
