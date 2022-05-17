#include "../inc/fitting.h"

static void try_to_fit_fig(t_coordinates *fig, char *field, int *max_x, int *max_y);
static int  unique(int *arr, int fig_num);
static int  *variants_search(int *arr, int fig_num);
static void variant_service(t_variant **variants, int variant_index, int fig_num);
static void variant_check(t_variant *variant, t_coordinates **coorrd_of_figs, char *field, int fig_num);
static void memory_exit(void);

void lisostep(t_coordinates **coorrd_of_figs, int fig_num, char *field)
{
    t_variant   *variants;
    int         variant_index;

    variants = NULL;
    variant_index = 0;

    variant_service(&variants, variant_index, fig_num);
    while (variants[variant_index].indx_arr != NULL)
    {
        variant_check(&variants[variant_index], coorrd_of_figs, field, fig_num);
        variant_index++;
        variant_service(&variants, variant_index, fig_num);
        variants[variant_index].indx_arr = variants_search(variants[0].indx_arr, fig_num);
    }
    print_fild(field);
}

static void     try_to_fit_fig(t_coordinates *fig, char *field, int *max_x, int *max_y)
{
    int             i;
    t_coordinates   buf[4];
    int             b_max_x;
    int             b_max_y;
    t_square_index  s_i;
    char            fig_exist;
    int             fig_indx;
    int             s_i_i;

    i = 0;
    b_max_x = 0;
    b_max_y = 0;
    fig_exist = 0;
    s_i_i = 0;
    while (field[i] != '\0')
    {
        fig_indx = 0;
        while (fig_indx < 4)
        {
            buf[fig_indx] = index_to_coordinates(i);
            buf[fig_indx].x = buf[fig_indx].x + fig[fig_indx].x;
            buf[fig_indx].y = buf[fig_indx].y + fig[fig_indx].y;
            if (buf[fig_indx].x > X_WIDTH
            || buf[fig_indx].y > Y_WIDTH
            || field[coordinates_to_index(buf[fig_indx])] != '.')
            {
                fig_exist = 1;
                break ;
            }
            if (b_max_x < buf[fig_indx].x)
            {
                b_max_x = buf[fig_indx].x;
            }
            if (b_max_y < buf[fig_indx].y)
            {
                b_max_y = buf[fig_indx].y;
            }
            fig_indx++;
        }
        if (fig_indx == 4)
        {
            s_i.index = i;
            s_i.area = b_max_x * b_max_y;
            s_i_i++;
        }
    }
}

static void     variant_check(t_variant *variant, t_coordinates **coorrd_of_figs, char *field, int fig_num)
{
    int     max_x;
    int     max_y;

    max_x = 0;
    max_y = 0;
    for (int i = 0; i < fig_num; i++)
    {
        try_to_fit_fig(coorrd_of_figs[variant->indx_arr[i]], field, &max_x, &max_y);
    }
    variant->area = max_x * max_y;
}

static void     variant_service(t_variant **variants, int variant_index, int fig_num)
{
    t_variant   *variants_buf;
    int         array_init;

    /* initialize array of variants */
    array_init = fig_num - 1;
    if (*variants == NULL && variant_index == 0)
    {
        *variants = (t_variant *)malloc(sizeof(t_variant) * 1);
        if (*variants != NULL)
        {
            variants[0][variant_index].indx_arr = (int *)malloc(sizeof(int) * fig_num);
            if (variants[0][variant_index].indx_arr == NULL)
            {
                memory_exit();
            }
        }
        else
        {
            memory_exit();
        }
        for (int fig_indx = 0; fig_indx < fig_num; fig_indx++)
        {
            variants[0][variant_index].indx_arr[fig_indx] = array_init;
            array_init--;
        }
    }

    /* enlarge array of variants by 1 with all previous info saved */
    else if (*variants != NULL && variant_index > 0)
    {
        variants_buf = (t_variant *)malloc(sizeof(t_variant) * (variant_index + 1));
        if (variants_buf != NULL)
        {
            for (int i = 0; i < variant_index; i++)
            {
                variants_buf[i].indx_arr = (int *)malloc(sizeof(int) * fig_num);
                if (variants_buf[i].indx_arr == NULL)
                {
                    memory_exit();
                }
            }
        }
        else
        {
            memory_exit();
        }
        variants_buf = ft_memcpy((void *)(variants_buf), (void *)(*variants), sizeof(t_variant) * (variant_index + 1));
        for (int i = 0; i < variant_index; i++)
        {
            variants_buf[i].indx_arr = (int *)ft_memcpy((void *)variants_buf[i].indx_arr,
                                                            (void *)variants[0][i].indx_arr,
                                                            sizeof(int) * fig_num);
        }
        free(*variants);
        *variants = (t_variant *)malloc(sizeof(t_variant) * (variant_index + 2));
        if (*variants != NULL)
        {
            for (int i = 0; i < variant_index; i++)
            {
                variants[0][i].indx_arr = (int *)malloc(sizeof(int) * fig_num);
                if (variants[0][variant_index].indx_arr == NULL)
                {
                    memory_exit();
                }
            }
        }
        else
        {
            memory_exit();
        }
        *variants = ft_memcpy((void *)(*variants), (void *)(variants_buf), sizeof(t_variant) * (variant_index + 1));
        for (int i = 0; i < (variant_index); i++)
        {
            variants[0][i].indx_arr = (int *)ft_memcpy((void *)variants[0][i].indx_arr,
                                                            (void *)variants_buf[i].indx_arr,
                                                            sizeof(int) * fig_num);
        }
        free(variants_buf);
    }
    else
    {
        perror("smthing went wrong with pointers to variants or variants_buf\n");
        exit(1);
    }
}

static void    memory_exit(void)
{
    perror("nema pamjati\n");
    exit(1);
}

// t_variant   checking_variant(t_coordinates *coorrd_of_fig, int fig_num, char *field, t_variant variant)
// {
//     for (int fig_indx = 0; fig_indx < fig_num; fig_indx++)
//     {
        
//     }
// }

// static int try_to_fit_fig(t_coordinates *coorrd_of_fig, char *field, int *max_x, int *max_y)
// {
    
// }

static int      *variants_search(int *arr, int fig_num)
{
    int i;

    while (1)
    {
        i = 0;
        while(i < fig_num)
        {
            if ((i < fig_num) && ((arr[i] + 1) >= fig_num))
            {
                arr[i] = 0;
                i++;
            }
            if ((i < fig_num) && ((arr[i] + 1) < fig_num))
            {
                arr[i]++;
                break ;
            }
        }
        if (!(unique(arr, fig_num)))
        {
            return arr;
        }
        else if (i >= fig_num)
        {
            free(arr);
            return NULL;
        }
    }
}

static int     unique(int *arr, int fig_num)
{
    int i;
    int j;
    int h;

    j = 0;
    h = 0;
    while (j < fig_num)
    {
        i = 0;
        while(i < fig_num)
        {
            if ((arr[i] == arr[j]) && (i != j))
            {
                h++;
            }
            if (h > 0)
            {
                break ;
            }
            i++;
        }
        if (h > 0)
        {
            break ;
        }
        j++;
    }
    return !!h;
}

#if 0
// lisostep

int i;
    int max_x;
    int max_y;
    int *arr;
    int varnt_quant;
    t_variant   *varnt;
    t_variant   *varnt_buf;
    t_variant   min;

    max_x = 0;
    max_y = 0;
    i = 0;
    varnt_quant = 0;
    min.square = INT_MAX;
    varnt = NULL;
    varnt_buf = NULL;

    min.indx_arr = (int *)malloc(sizeof(int) * fig_num);

    i = fig_num - 1;
    arr = (int *)malloc(sizeof(int) * fig_num);
    for (int j = 0; j < fig_num; j++)
    {
        arr[j] = i;
        i--;
    }
    while (arr != NULL)
    {
        /* resizing variant arrays */
        if (varnt != NULL && varnt_buf != NULL)
        {
            varnt_buf = (t_variant *)ft_memcpy((void *)varnt_buf, (void *)varnt, sizeof(t_variant) * varnt_quant);
            free(varnt);
            varnt_quant++;
            varnt = (t_variant *)malloc(sizeof(t_variant) * varnt_quant);
            varnt = (t_variant *)ft_memcpy((void *)varnt, (void *)varnt_buf, sizeof(t_variant) * varnt_quant - 1);
            free(varnt_buf);
            varnt_buf = (t_variant *)malloc(sizeof(t_variant) * varnt_quant);
        }
        else
        {
            varnt = (t_variant *)malloc(sizeof(t_variant) * 1);
            varnt_buf = (t_variant *)malloc(sizeof(t_variant) * 1);
            varnt_quant++;
        }

        /* copying unique array of indexes into last variant */
        varnt[varnt_quant - 1].indx_arr = (int *)malloc(sizeof(int) * fig_num);
        varnt[varnt_quant - 1].indx_arr = (int *)ft_memcpy((void *)varnt[varnt_quant - 1].indx_arr, (void *)arr, (sizeof(int) * fig_num));

        /* fitting all the figures from figure array and writing the smallest area possible for this combination into last variant */
        i = 0;
        while (i < fig_num)
        {
            varnt[varnt_quant - 1].square = try_to_fit_fig(coorrd_of_figs[arr[i]], field, &max_x, &max_y);
            i++;
        }
        field = (char *)ft_memset((void *)field, '.', 441);
        arr = variants_search(arr, fig_num);
    }

    /* finding variant with the smallest area */
    for (int h = 0; h < varnt_quant; h++)
    {
        if (varnt[h].square < min.square)
        {
            min.square = varnt[h].square;
            min.indx_arr = (int *)ft_memcpy((void *)min.indx_arr, (void *)varnt[h].indx_arr, sizeof(int) * fig_num);
        }
    }

    /* filling the best combination of figures from database array */
    max_x = 0;
    max_y = 0;
    for (int fig_i = 0; fig_i < fig_num; fig_i++)
    {
        try_to_fit_fig(coorrd_of_figs[min.indx_arr[fig_i]], field, &max_x, &max_y);
    }
#endif

#if 0
// try to fit fig
int i;
    int j;
    int buf;
    int t;
    int b_max_x = 0;
    int b_max_y = 0;
    t_coordinates field_xy;
    t_square_index *s_i;
    t_square_index min;

    i = 0;
    t = 0;
    s_i = (t_square_index *)malloc(sizeof(t_square_index) * 442);

    while (field[i] != '\0')
    {
        if (field[i] >= 'A' && field[i] <= 'Z')
        {
            i++;
            continue ;
        }
        j = 0;
        b_max_x = *max_x;
        b_max_y = *max_y;
        while (j < 4)
        {
            field_xy = index_to_coordinates(i);
            field_xy.x = field_xy.x + coorrd_of_fig[j].x;
            if (field_xy.x > (X_WIDTH - 1))
            {
                break;
            }
            field_xy.y = field_xy.y + coorrd_of_fig[j].y;
            if (field_xy.y > (Y_WIDTH - 1))
            {
                break;
            }

            if (b_max_x < field_xy.x)
            {
                b_max_x = field_xy.x;
            }

            if (b_max_y < field_xy.y)
            {
                b_max_y = field_xy.y;
            }

            buf = coordinates_to_index(field_xy.x, field_xy.y);

            if (field[buf] >= 'A' && field[buf] <= 'Z')
            {
                break ;
            }
            j++;
        }
        if (j == 4)
        {
            b_max_x++;
            b_max_y++;
            s_i[t].index = i;
            s_i[t].square = (b_max_x * b_max_y);
            t++;
        }
        i++;
    }

    t--;
    min.square = s_i[t].square;
    min.index = s_i[t].index;
    while (t > -1)
    {
        if ((min.square > s_i[t].square) || ((min.square == s_i[t].square) && (min.index > s_i[t].index)))
        {
            min.square = s_i[t].square;
            min.index = s_i[t].index;
        }
        t--;
    }
    
    j = 0;
    while (j < 4)
    {
        field_xy = index_to_coordinates(min.index);
        field_xy.x = field_xy.x + coorrd_of_fig[j].x;
        field_xy.y = field_xy.y + coorrd_of_fig[j].y;
        if (*max_x < field_xy.x + 1)
        {
            *max_x = field_xy.x + 1;
        }

        if (*max_y < field_xy.y + 1)
        {
            *max_y = field_xy.y + 1;
        }
        buf = coordinates_to_index(field_xy.x, field_xy.y);
        field[buf] = coorrd_of_fig[j].letter;
        j++;
    }
    return min.square;
#endif
