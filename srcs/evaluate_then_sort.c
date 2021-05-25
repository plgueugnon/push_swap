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
    if (!ft_queue_to_stack(cmd, ccode))
        ft_error_all(a, b, cmd);
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

    iter = NULL;
    if (ccode < PA && ccode > PB)
        return ;
    if (ccode == PA)
        iter = b->front;
    else if (ccode == PB)
        iter = a->front;
    while (iter)
    {
        iter = iter->next; // NB iterer avant remove sinon error carfree
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

void    ft_copy_stack_to_tab(t_lstack *a, int *tab)
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

void    ft_tab_insertion_sort(int *tab, int size)
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

void    ft_get_chunks_limit(int *limit, int chunks, int size)
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

int    ft_stack_up_pivot(int *tab, t_lstack *pivot, int size)
{
    int i;
    int chunks;
    int limit[9];
    int j;

    chunks = 5;
    if (size > 100)
        chunks = 9;
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
    int i;

    i = 0;
    size = ft_quantity_to_sort(a);
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

void    ft_quicksort(t_lstack *a, t_lstack *b, t_lstack *cmd, t_lstack *pivot)
{
    int i;

    i = 0;
    while (a->front)
    {
        while(a->front->n != pivot->front->n)
        {
            if (a->front->n > pivot->front->n)
                ft_exec_n_stash_cmd(a, b, cmd, RA);
            else if (a->front->n < pivot->front->n)
                ft_exec_n_stash_cmd(a, b, cmd, PB);
        }
        ft_exec_n_stash_cmd(a, b, cmd, RA);
        while(a->front->n != pivot->front->n)
        {
            if (a->front->n > pivot->front->n)
                ft_exec_n_stash_cmd(a, b, cmd, RA);
            else if (a->front->n < pivot->front->n)
                ft_exec_n_stash_cmd(a, b, cmd, PB);
        }
        ft_exec_n_stash_cmd(a, b, cmd, PB);
        ft_remove_from_stack(pivot);
    }
}

void    ft_sort_b(t_lstack *a, t_lstack *b, t_lstack *cmd)
{
    int s;
    int i;

    i = 0;
    s = ft_quantity_to_sort(b);
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
    ft_quicksort(a, b, cmd, pivot);
    ft_cleanup_stack(pivot);
    ft_sort_b(a, b, cmd);
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
    else if (count > 3 && count < 11)
        ft_sort_small_stack(a, b, *cmd, count);
    else if (count >= 11)
        ft_sort_big_stack(a, b, *cmd);
    ft_print_cmd(*cmd);
    ft_exit(a, b, *cmd, "");
}