#include "../inc/maping.h"

void maping(char figs[FIG_MAX][FIG_SIZE])
{
    int i;
    char c;
    int j;

    i = 0;
    c = 'A';
    while (i < FIG_MAX)
    {
        if (ft_strlen(figs[i]) > 0)
        {
            j = 0;
            while (figs[i][j] != '\0')
            {
                if (figs[i][j] == '#')
                {
                    figs[i][j] = c;
                }
                j++;
            }
        }
        else
        {
            break ;
        }
        i++;
        c++;
    }
}

int coordinates_to_index(int x, int y)
{
    int index;

    index = (y * X_WIDTH) + x;
    return index;
}

t_coordinates index_to_coordinates(int index)
{
    t_coordinates   res;

    res.y = index / X_WIDTH;
    res.x = index % X_WIDTH;

    return res;
}

static t_coordinates fig_index_to_coordinates(int index)
{
    t_coordinates   res;

    res.y = index / 5;
    res.x = index % 5;

    return res;
}

t_coordinates *fig_move(char *fig)
{
    t_coordinates *res;
    int i;
    int j;

    i = 0;
    j = 0;
    res = (t_coordinates *)malloc(sizeof(t_coordinates) * 4);
    while (fig[i] != '\0')
    {
        if (fig[i] >= 'A' && fig[i] <= 'Z')
        {
            res[j] = fig_index_to_coordinates(i);
            res[j].letter = fig[i];
            j++;
        }
        i++;
    }
    res = move(res);
    return res;
}

t_coordinates *move(t_coordinates *res)
{
    while ((res[0].x > 0) && (res[1].x > 0) && (res[2].x > 0) && (res[3].x > 0))
    {
        res[0].x = res[0].x - 1;
        res[1].x = res[1].x - 1;
        res[2].x = res[2].x - 1;
        res[3].x = res[3].x - 1;
    }

    while ((res[0].y > 0) && (res[1].y > 0) && (res[2].y > 0) && (res[3].y > 0))
    {
        res[0].y = res[0].y - 1;
        res[1].y = res[1].y - 1;
        res[2].y = res[2].y - 1;
        res[3].y = res[3].y - 1;
    }
    return res;
}

void make_fig_great_again(t_coordinates **res, char figs[FIG_MAX][FIG_SIZE])
{
    int i;

    i = 0;
    while (i < FIG_MAX)
    {
        res[i] = fig_move(figs[i]);
        display_new_coord(res[i]);

        i++;
    }
}
