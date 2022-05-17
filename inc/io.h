#ifndef IO_H
#define IO_H

#include <fcntl.h>
#include "common.h"
#include "maping.h"

void read_file(const char *filename, char figs[FIG_MAX][FIG_SIZE]);
void print_figs(char figs[FIG_MAX][FIG_SIZE], int fig_num);
void print_fild(char *fild);
void display_new_coord(t_coordinates *res);

#endif