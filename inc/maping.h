#ifndef MAPING_H
#define MAPING_H

#include "common.h"
#include "io.h"

void            maping(char figs[FIG_MAX][FIG_SIZE]);
int             coordinates_to_index(int x, int y);
t_coordinates   index_to_coordinates(int index);
t_coordinates   *fig_move(char *fig);
t_coordinates   *move(t_coordinates res[4]);
void            make_fig_great_again(t_coordinates **res, char figs[FIG_MAX][FIG_SIZE]);

#endif