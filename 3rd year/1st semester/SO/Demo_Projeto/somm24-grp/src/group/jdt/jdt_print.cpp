/*
 *  \author ...
 */

#include "somm24.h"

#include <stdio.h>
#include <stdint.h>

namespace group 
{

// ================================================================================== //

    void jdtPrint(FILE *fout)
    {
        soProbe(203, "%s(\"%p\")\n", __func__, fout);

        require(maxAddressSpace != NO_SIZE, "Module is not in a valid open state!");
        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        /* TODO POINT: Replace next instruction with your code */
        throw Exception(ENOSYS, __func__);
    }

// ================================================================================== //

} // end of namespace group

