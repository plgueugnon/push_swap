#include "pushswap.h"

void    ft_exec_n_stash_cmd(t_lstack *a, t_lstack *b, t_lstack *cmd, int ccode)
{
    if (!ft_queue_to_stack(cmd, ccode))
        ft_error_all(a, b, cmd);
    ft_exec_cmd(ccode, a, b);
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