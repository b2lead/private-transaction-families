///////////////////////////////////////////////////////
// mock of ACL code
///////////////////////////////////////////////////////
#include "memset_s.h"

errno_t memset_s(void *s, size_t smax, int c, size_t n)
{
    memset(s, c, n);
    return 0;
}