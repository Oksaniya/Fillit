#include "../inc/io.h"

static ssize_t get_fig(int fd, char *fig)
{
    ssize_t res_read;
    ssize_t res_read_nl;
    char    buf[1];

    res_read = 1;

    res_read = read(fd, (void *)fig, FIG_SIZE - 1);
    res_read_nl = read(fd, (void *)buf, 1);
    if (res_read_nl > 0 && buf[0] != '\n')
    {
        ft_putstr("Incorrect file format. No empty line between the figures.\n");
        exit(EXIT_FAILURE);
    }
    
    return res_read;
}

void read_file(const char *filename, char figs[FIG_MAX][FIG_SIZE])
{
    int     fd;
    ssize_t res_read;

    fd = open(filename, O_RDONLY);
    res_read = 1;
    

    if (fd < 3)
    {
        ft_putstr("Unable to open the file\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < FIG_MAX && res_read > 0; i++)
    {
        res_read = get_fig(fd, figs[i]);
    }
    close(fd);
}

void print_figs(char figs[FIG_MAX][FIG_SIZE], int fig_num)
{
    for (int i = 0; i < fig_num; i++)
    {
        ft_putstr(figs[i]);
        ft_putchar('\n');
    }
}

void print_fild(char *fild)
{
    int i;

    i = 0;
    //printf("field[441] = %u\n", fild[441]);
    while (fild[i] != '\0')
    {
        ft_putchar(fild[i]);
        if ((i + 1) % 21 == 0)
        {
            ft_putchar('\n');
        }
        i++;
    }
    ft_putchar('\n');
}

void display_new_coord(t_coordinates *res)
{
    char fig[FIG_SIZE];
    int i;
    int j;

    i = 0;
    j = 0;
    ft_memset((void *)fig, '.', FIG_SIZE);
    fig[FIG_SIZE - 1] = '\0';
    for (int i = 0; i < FIG_SIZE; i++)
    {
        if ((i + 1) % 5 == 0)
        {
            fig[i] = '\n';
        }
    }

    while (i < FIG_SIZE)
    {
        if (i == coordinates_to_index(res[j].x, res[j].y))
        {
            fig[i] = '#';
            j++;
        }
        i++;
    }
    //ft_putstr(fig);
   // ft_putchar('\n');
}