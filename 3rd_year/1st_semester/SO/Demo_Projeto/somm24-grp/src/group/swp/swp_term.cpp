/*
 *  \author ...
 */

#include "somm24.h"

namespace group
{

// ================================================================================== //

    void swpTerm()
    {
        soProbe(602, "%s()\n", __func__);

        require(swappingPolicy == FirstProcess or swappingPolicy == FirstFitProcess, "Module is not in a valid open state!");
        require(swpList != UNDEF_SWP_NODE and swpTail != UNDEF_SWP_NODE, "Module is not in a valid open state!");

        /* TODO POINT: Replace next instruction with your code */
        throw Exception(ENOSYS, __func__);
    }

// ================================================================================== //

} // end of namespace binaries

