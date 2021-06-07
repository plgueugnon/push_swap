#include "pushswap.h"

static void    ft_copy_stack_to_tab(t_lstack *a, int *tab)
{
    t_node *iter;
    int i;

    i = 0;
    iter = a->front;
    while (iter)
    {
        tab[i] = iter->n;
        i++;
        iter = iter->next;
    }
}

static void    ft_tab_insertion_sort(int *tab, int size)
{
    int tmp;
    int i;
    int j;

    i = 0;
    tmp = 0;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (tab[j] < tab[i])
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

static void    ft_get_chunks_limit(int *limit, int chunks, int size)
{
    int j;

    j = 1;
    limit[0] = size / chunks;
    while (j < chunks)
    {
        limit[j] = (size / chunks) + limit[j - 1];
        j++;
    }
}

static int    ft_stack_up_pivot(int *tab, t_lstack *pivot, int size)
{
    int i;
    int chunks;
    int limit[12];
    int j;

    chunks = 5;
    if (size > 100)
        chunks = 12;
    i = 0;
    j = 0;
    ft_get_chunks_limit(limit, chunks, size);
    while (i < size)
    {
        if (j < chunks)
            if (i == limit[j])
            {
                if (!ft_queue_to_stack(pivot, tab[i]))
                    return(0);
                j++;
            }
        i++;
    }
    if (!ft_queue_to_stack(pivot, tab[size - 1]))
        return(0);
    return (1);
}

void    ft_get_pivot(t_lstack *a, t_lstack *b, t_lstack *cmd, t_lstack *pivot)
{
    int *tab;
    int size;
    //int i;

    //i = 0;
    size = ft_stack_len(a);
    tab = malloc(sizeof(int) * size);
    if (!tab)
    {
        ft_cleanup_stack(pivot);
        ft_error_all(a, b, cmd);
    }
    ft_copy_stack_to_tab(a, tab);
    ft_tab_insertion_sort(tab, size);
    if (!ft_stack_up_pivot(tab, pivot, size))
    {
        free(tab);
        ft_cleanup_stack(pivot);
        ft_error_all(a, b, cmd);
    }
    free(tab);
}