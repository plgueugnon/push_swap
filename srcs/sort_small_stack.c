#include "pushswap.h"

void    ft_sort_three(t_lstack *a, t_lstack *b, t_lstack *cmd)
{
    int i;
    t_node *iter;

    iter = a->front->next;
    i = ft_index_value(a, ft_stack_max_value(a));
    if (i == 0)
        ft_exec_n_stash_cmd(a, b, cmd, RA);
    else if (i == 1)
        ft_exec_n_stash_cmd(a, b, cmd, RRA);
    iter = a->front->next;
    if (a->front->n > iter->n)
        ft_exec_n_stash_cmd(a, b, cmd, SA);
}

void    ft_empty_stack(t_lstack *a, t_lstack *b, t_lstack *cmd, int ccode)
{
    t_node *iter;

    iter = NULL;
    if (ccode < PA && ccode > PB)
        return ;
    if (ccode == PA)
        iter = b->front;
    else if (ccode == PB)
        iter = a->front;
    while (iter)
    {
        iter = iter->next;
        ft_exec_n_stash_cmd(a, b, cmd, ccode);
    }
}

void    ft_sort_small_stack(t_lstack *a, t_lstack *b, t_lstack *cmd, int total)
{
    int index;

    index = 0;
    while (total > 3)
    {
        index = ft_index_value(a, ft_stack_min_value(a));
        if (index < total / 2)
            while (index--)
                ft_exec_n_stash_cmd(a, b, cmd, RA);
        else
            while (index++ < total)
                ft_exec_n_stash_cmd(a, b, cmd, RRA);
        ft_exec_n_stash_cmd(a, b, cmd, PB);
        total--;
    }
    ft_sort_three(a, b, cmd);
    ft_empty_stack(a, b, cmd, PA);
}