#include "pushswap.h"

int     ft_evaluate_stack(t_lstack *a, t_lstack *b) // a deplacer
{
    t_node *iter;
    t_node *jter;

    iter = a->front;
    while (iter)
    {
        jter = a->front;
        while (jter != iter)
        {
            if (jter->n > iter->n)
                return (0);
            jter = jter->next;
        }
        iter = iter->next;
    }
    if (b->front)
        return(0);
    return (1);
}

void    ft_exec_rotate_cmd(int cmd, t_lstack *a, t_lstack *b)
{
    if (cmd == RA)
        ft_push_top_to_bottom(a);
    if (cmd == RB)
        ft_push_top_to_bottom(b);
    if (cmd == RR)
    {
        ft_push_top_to_bottom(a);
        ft_push_top_to_bottom(b);
    }
    if (cmd == RRA)
        ft_push_bottom_to_top(a);
    if (cmd == RRB)
        ft_push_bottom_to_top(b);
    if (cmd == RRR)
    {
        ft_push_bottom_to_top(a);
        ft_push_bottom_to_top(b);
    }
}

void    ft_exec_cmd(int cmd, t_lstack *a, t_lstack *b)
{
    if (cmd == SA)
        ft_swap_stack_top_two_values(a);
    if (cmd == SB)
        ft_swap_stack_top_two_values(b);
    if (cmd == SS)
    {
        ft_swap_stack_top_two_values(a);
        ft_swap_stack_top_two_values(b);
    }
    if (cmd == PA)
        ft_pop_n_add_to_other_stack(b, a);
    if (cmd == PB)
        ft_pop_n_add_to_other_stack(a, b);
    if (cmd >= RA && cmd <= RRR)
        ft_exec_rotate_cmd(cmd, a, b);
}

void    ft_exec_cmd_n_evaluate(t_lstack *a, t_lstack *cmd)
{
    t_lstack *b;
    t_node *iter;
    int i;

    i = 0;
    b = ft_init_stack();
    iter = cmd->front;
    if (!b)
        ft_error_all(a, b, cmd);
    while (iter)
    {
        ft_exec_cmd(iter->n, a, b);
        iter = iter->next;;
    }
    t_node *itera;//
    t_node *iterb;
    itera = a->front;
    iterb = b->front;
    printf("check exit\n");
    printf("STACK A\n");
    if (itera)
    {
        while (itera)
        {
            printf("%d\n", (int)itera->n);
            itera = itera->next;
        }
    }
    printf("STACK B\n");
    if (iterb)
    {
        while (iterb)
        {
            printf("%d\n", (int)iterb->n);
            iterb = iterb->next;
        }
    }//
    if (ft_evaluate_stack(a, b))
        ft_exit(a, b, cmd, "OK\n");
    else
        ft_exit(a, b, cmd, "KO\n");
}