#include "../inc/io.h"
#include "../inc/validator.h"
#include "../inc/maping.h"
#include "../inc/fitting.h"

static void check_argc(int argc)
{
    if (argc != 2)
    {
        ft_putstr("Odyn daj fajl, padlo!\n");
    }
}

int main(int argc, char **argv)
{
    t_coordinates   **fig_coord;
    char            fild[442];
    char            figs[FIG_MAX][FIG_SIZE];
    int             fig_num;

    fig_coord = (t_coordinates **)malloc(sizeof(t_coordinates *) * FIG_MAX);
    for (int i = 0; i < FIG_MAX; i++)
    {
        fig_coord[i] = (t_coordinates *)malloc(sizeof(t_coordinates) * 4);
    }
    ft_memset((void *)fild, '.', 442);
    fild[441] = '\0';
    ft_bzero((void *)figs, FIG_MAX * FIG_SIZE);
    check_argc(argc);
    read_file(argv[1], figs);
    fig_num = validator(figs);
    maping(figs);
    //print_figs(figs, fig_num);
    make_fig_great_again(fig_coord, figs);
    lisostep(fig_coord, fig_num, fild);
    //create_int(figs, fig_num);
    //print_fild(fild);
    return 0;
}