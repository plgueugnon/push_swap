#include "pushswap.h"

int     ft_stack_max_value(t_lstack *s)
{
    t_node *iter;
    int max;

    iter = s->front;
    max = s->front->n;
    while (iter)
    {
        if (max < iter->n)
            max = iter->n;
        iter = iter->next;
    }
    return (max);
}

int     ft_stack_min_value(t_lstack *s)
{
    t_node *iter;
    int min;

    iter = s->front;
    min = s->front->n;
    while (iter)
    {
        if (min > iter->n)
            min = iter->n;
        iter = iter->next;
    }
    return (min);
}

int     ft_index_value(t_lstack *s, int nb)
{
    int i;
    t_node *iter;

    i = 0;
    iter = s->front;
    while (iter)
    {
        if (iter->n == nb)
            return (i);
        i++;
        iter = iter->next;
    }
    return (i);
}

int     ft_quantity_to_sort(t_lstack *a)
{
    t_node *iter;
    int c;

    c = 0;
    iter = a->front;
    while (iter)
    {
        c++;
        iter = iter->next;
    }
    return (c);
}

void    ft_exec_n_stash_cmd(t_lstack *a, t_lstack *b, t_lstack *cmd, int ccode)
{
    ft_queue_to_stack(cmd, ccode);
    ft_exec_cmd(ccode, a, b);
}

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

    iter = b->front;
    if (ccode < PA && ccode > PB)
        return ;
    while (iter)
    {
        iter = iter->next; // NB iterer avant remove sinon error carfree
        ft_exec_n_stash_cmd(a, b, cmd, ccode);
    }
}

void    ft_sort_small_amount(t_lstack *a, t_lstack *b, t_lstack *cmd, int total)
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

void    ft_print_cmd(t_lstack *cmd) // a ameliorer ou suppr pr privilegier impression directe
{
    t_node *iter;

    iter = cmd->front;
    while (iter)
    {
        if (iter->n == SA)
            ft_putstr("sa\n");
        else if (iter->n == SB)
            ft_putstr("sb\n");
        else if (iter->n == SS)
            ft_putstr("ss\n");
        else if (iter->n == RA)
            ft_putstr("ra\n");
        else if (iter->n == RB)
            ft_putstr("rb\n");
        else if (iter->n == RR)
            ft_putstr("rr\n");
        else if (iter->n == RRR)
            ft_putstr("rrr\n");
        else if (iter->n == RRA)
            ft_putstr("rra\n");
        else if (iter->n == RRB)
            ft_putstr("rrb\n");
        else if (iter->n == PA)
            ft_putstr("pa\n");
        else if (iter->n == PB)
            ft_putstr("pb\n");
        iter = iter->next;
    }
}

void    ft_evaluate_then_sort(t_lstack *a, t_lstack **cmd)
{
    t_lstack *b;
    int count;

    count = ft_quantity_to_sort(a);
    b = ft_init_stack();
    *cmd = ft_init_stack();
    if (!b || !*cmd)
        ft_error_all(a, b, *cmd);
    if (ft_evaluate_stack(a, b)) // si tout est trie je quit
        ft_exit(a, b, *cmd, "");
    if (count < 4)
        ft_sort_three(a, b, *cmd);
    if (count > 3 && count < 11)
        ft_sort_small_amount(a, b, *cmd, count);
    ft_print_cmd(*cmd);
    ft_exit(a, b, *cmd, "");
}