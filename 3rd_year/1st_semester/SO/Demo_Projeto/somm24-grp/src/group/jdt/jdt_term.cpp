/*
 *  \author ...
 */

#include "somm24.h"

namespace group 
{

// ================================================================================== //

    void jdtTerm() 
    {
        soProbe(202, "%s()\n", __func__);

        require(maxAddressSpace != NO_SIZE, "Module is not in a valid open state!");

        /* TODO POINT: Replace next instruction with your code */
        throw Exception(ENOSYS, __func__);
    }

// ================================================================================== //

} // end of namespace group

