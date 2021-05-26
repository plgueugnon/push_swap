#include "pushswap.h"

void    ft_eval_pivot(t_lstack *a, t_lstack *b, t_lstack *cmd, t_lstack *pivot)
{
    while(a->front->n != pivot->front->n)
    {
        if (a->front->n > pivot->front->n)
            ft_exec_n_stash_cmd(a, b, cmd, RA);
        else if (a->front->n < pivot->front->n)
            ft_exec_n_stash_cmd(a, b, cmd, PB);
    }
}

void    ft_quicksort(t_lstack *a, t_lstack *b, t_lstack *cmd, t_lstack *pivot)
{
    int s;

    s = (ft_stack_len(a) - ft_index_value(a, pivot->front->n));
    ft_eval_pivot(a, b, cmd, pivot);
    if (s != 0)
    {
        ft_exec_n_stash_cmd(a, b, cmd, RA);
        if (pivot->front->n != ft_stack_max_value(a))
            while(s--)
            {
                if (a->front->n > pivot->front->n)
                    ft_exec_n_stash_cmd(a, b, cmd, RA);
                else if (a->front->n < pivot->front->n)
                    ft_exec_n_stash_cmd(a, b, cmd, PB);
            }
        else
        {
            ft_eval_pivot(a, b, cmd, pivot);
            ft_exec_n_stash_cmd(a, b, cmd, PB);
        }
    }
    else
        ft_exec_n_stash_cmd(a, b, cmd, PB);
    ft_remove_from_stack(pivot);
}

static void    ft_sort_b(t_lstack *a, t_lstack *b, t_lstack *cmd)
{
    int s;
    int i;

    i = 0;
    s = ft_stack_len(b);
    while (b->front)
    {
        i = ft_index_value(b, ft_stack_max_value(b));
        if (i == 1)
            ft_exec_n_stash_cmd(a, b, cmd, SB);
        else if (i < s / 2)
            while (i--)
                ft_exec_n_stash_cmd(a, b, cmd, RB);
        else
            while (i++ < s)
                ft_exec_n_stash_cmd(a, b, cmd, RRB);
        if (b->front)
        {
            if (b->front->n == ft_stack_max_value(b))
            {
                ft_exec_n_stash_cmd(a, b, cmd, PA);
                s--;
            }
        }
    }
}

void    ft_sort_big_stack(t_lstack *a, t_lstack *b, t_lstack *cmd)
{
    t_lstack *pivot;

    pivot = ft_init_stack();
    if (!pivot)
        ft_error_all(a, b, cmd);
    ft_get_pivot(a, b, cmd, pivot);
    while (a->front)
        ft_quicksort(a, b, cmd, pivot);
    ft_cleanup_stack(pivot);
    ft_sort_b(a, b, cmd);
}