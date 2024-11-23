/*
 *  \author ...
 */

#include "somm24.h"

#include <stdint.h>

namespace group
{
    double pctLifetime(uint16_t pid)
    {
        soProbe(305, "%s(%u)\n", __func__, pid);

        require(pctList != UNDEF_PCT_NODE, "The PCT linked list must exist");
        require(pid > 0, "a valid process ID must be greater than zero");

        /* replace with your code */
        throw Exception(ENOSYS, __func__);
    }

} // end of namespace somm22
