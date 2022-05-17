#include "../inc/validator.h"

static void char_check(char *fig)
{
    for (int i = 0; fig[i] != '\0'; i++)
    {
        if (fig[i] != '.' && fig[i] != '#' && fig[i] != '\n')
        {
            ft_putstr("Incorrect symbols\n");
            exit(EXIT_FAILURE);
        }

        if ((i + 1) % 5 == 0 && fig[i] != '\n')
        {
            ft_putstr("NO \\n in the end of string or Incorrect symbols\n");
            exit(EXIT_FAILURE);
        }
    }
}

static void hesh_check(char *fig)
{
    int i;
    int hesh_counter;
    
    i = 0;
    hesh_counter = 0;
    int pos[4] = {0};

    while (fig[i] != '\0' && i >= 0)
    {
        if (fig[i] == '#')
        {
            pos[0] = i - 5;
            pos[1] = i - 1;
            pos[2] = i + 1;
            pos[3] = i + 5;

            if ((pos[0] >= 0 && (fig[pos[0]] == '#'))
            || (pos[1] >= 0 && (fig[pos[1]] == '#'))
            || (pos[2] < 21 && (fig[pos[2]] == '#'))
            || (pos[3] < 21 && (fig[pos[3]] == '#')))
            {
                hesh_counter++;
            }
            else
            {
                ft_putstr("The # is not connected, Aaaa!");
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }
    if (hesh_counter != 4)
    {
        ft_putstr("The figure consists of wrong amount of #.\n");
        exit(EXIT_FAILURE);
    }
}

int validator(char figs[FIG_MAX][FIG_SIZE])
{
    int i;
    int fig_num;

    i = 0;
    fig_num = 0;
    while (i < 26)
    {
        if (ft_strlen(figs[i]) > 0)
        {
            char_check(figs[i]);
            hesh_check(figs[i]);
            fig_num++;
        }
        i++;
    }
    return fig_num;
}
