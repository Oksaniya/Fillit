#ifndef COMMON_H
#define COMMON_H

#include "../my_stdlib/header/my_stdlib.h"

#include <stdio.h>

#define FIG_SIZE    21
#define FIG_MAX     26

#define X_WIDTH     21
#define Y_WIDTH     21

typedef struct      s_coordinates
{
    int             x;
    int             y;
    char            letter;
}                   t_coordinates;

typedef struct      s_square_index
{
    int             area;
    int             index;
}                   t_square_index;

typedef struct      s_variant
{
    int             area;
    int             *indx_arr;
}                   t_variant;

#endif