/*
 *  \author ...
 */

#include "somm24.h"

#include <stdint.h>

namespace group
{
    uint32_t pctMemSize(uint16_t pid)
    {
        soProbe(306, "%s(%u)\n", __func__, pid);

        require(pctList != UNDEF_PCT_NODE, "The PCT linked list must exist");
        require(pid > 0, "a valid process ID must be greater than zero");

        /* replace with your code */
        PctNode *current_node = pctList;

        int found = 0;

        while (current_node->next != NULL){
            if(current_node->pcb.pid == pid){
                found = 1;
                return current_node->pcb.memSize;
            }
        }
        if(!found){throw EINVAL;}
    }

} // end of namespace somm22
