/*
 *  \author ...
 */

#include "somm24.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    uint16_t pctNewProcess(double admissionTime, double lifetime, uint32_t memSize)
    {
        soProbe(304, "%s(%0.1f, %0.1f, %#x)\n", __func__, admissionTime, lifetime, memSize);

        require(pctList != UNDEF_PCT_NODE, "Module is not in a valid open state!");
        require(admissionTime >= 0, "Bad admission time");
        require(lifetime > 0, "Bad lifetime");
        require(memSize > 0, "Bad memory size");

        /* TODO POINT: Replace next instruction with your code */
        static int pids = 0;
        PctNode *new_node = (PctNode*)malloc(sizeof(PctNode));
        PctBlock new_block = {.pid = pids++, 
                                .state = NEW, 
                                .storeTime = UNDEF_TIME, 
                                .startTime= UNDEF_TIME, 
                                .finishTime = UNDEF_TIME,
                                .memStart = UNDEF_ADDRESS, 
                                .admissionTime = admissionTime,
                                .lifetime = lifetime,
                                .memSize = memSize};

        new_node->pcb = new_block;

        PctNode *current_node = pctList;
        while(current_node->pcb.pid < new_block.pid){
            current_node = current_node->next;
        }
        PctNode *next_node = current_node->next;
        current_node->next = new_node;
        new_node->next = next_node;
    }

// ================================================================================== //

} // end of namespace group

