/*
 *  \author ...
 */

#include "somm24.h"

namespace group
{

// ================================================================================== //

    /*
     * Return the submission time of the first job description table
     */
    double jdtNextSubmission()
    {
        soProbe(206, "%s()\n", __func__);

        require(maxAddressSpace != NO_SIZE, "Module must be open");

        /* TODO POINT: Replace next instruction with your code */
        throw Exception(ENOSYS, __func__);
    }

// ================================================================================== //

} // end of namespace group



