#include <stdlib.h>
#include <string.h>

typedef struct      s_variant
{
    int             square;
    int             *indx_arr;
}                   t_variant;

int     main(void)
{
    int         arr[] = {3,2,1,0};
    t_variant   *varnt;

    varnt =  (t_variant *)malloc(sizeof(t_variant) * 1);
    varnt[0].indx_arr = (int *)malloc(sizeof(int) * 4);

    varnt[0].indx_arr = (int *)memcpy((void *)(varnt[0].indx_arr), (void *)arr, 4);

    return 0;
}