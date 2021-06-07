#include "pushswap.h"

void    ft_print_rotate_cmd(int n)
{
    if (n == RA)
        ft_putstr("ra\n");
    else if (n == RB)
        ft_putstr("rb\n");
    else if (n == RR)
        ft_putstr("rr\n");
    else if (n == RRR)
        ft_putstr("rrr\n");
    else if (n == RRA)
        ft_putstr("rra\n");
    else if (n == RRB)
        ft_putstr("rrb\n");
}

void    ft_print_cmd(t_lstack *cmd)
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
        else if (iter->n == PA)
            ft_putstr("pa\n");
        else if (iter->n == PB)
            ft_putstr("pb\n");
        else if (iter->n >= RA && iter->n <= RRR)
            ft_print_rotate_cmd(iter->n);
        iter = iter->next;
    }
}

void    ft_evaluate_then_sort(t_lstack *a, t_lstack **cmd)
{
    t_lstack *b;
    int count;

    count = ft_stack_len(a);
    b = ft_init_stack();
    *cmd = ft_init_stack();
    if (!b || !*cmd)
        ft_error_all(a, b, *cmd);
    if (ft_evaluate_stack(a, b))
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

int     main(int argc, char **argv)
{
    int i;
    t_lstack *cmd;
    t_lstack *a;

    i = 1;
    cmd = NULL;
    a = ft_init_stack();
    if (!a)
        ft_error_stack(a);
    if (argc > 1)
    {
        if (argc == 2)
            ft_parse_arg(argv[1], a);
        else
        {
            while (i < argc)
            {
                ft_parse_arg(argv[i], a);
                i++;
            }
        }
        ft_evaluate_then_sort(a, &cmd);
    }
    ft_cleanup_stack(a);
    return (0);
}