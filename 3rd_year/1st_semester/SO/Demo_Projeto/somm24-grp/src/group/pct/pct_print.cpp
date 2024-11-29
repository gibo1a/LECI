/*
 *  \author ...
 */

#include "somm24.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void pctPrint(FILE *fout)
    {
        soProbe(303, "%s(\"%p\")\n", __func__, fout);

        require(pctList != UNDEF_PCT_NODE, "Module is not in a valid open state!");
        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        /* TODO POINT: Replace next instruction with your code */
        PctNode *current_node = pctList;

        while (current_node->next != NULL){
            int print = fprintf(fout,""); //perguntar ao stor o que é suposto imprimir
            current_node = current_node->next; 
            if(print < 0){throw Exception(1,"pctPrint","Exception");}

        }
        
    }

// ================================================================================== //

} // end of namespace group

