/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:47:11 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 16:28:20 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_exec_n_stash_cmd(t_stack *a, t_stack *b, t_stack *cmd, int code)
{
	if (!ft_queue_to_stack(cmd, code))
		ft_error_all(a, b, cmd);
	ft_exec_cmd(code, a, b);
}

void	ft_exec_rotate_cmd(int cmd, t_stack *a, t_stack *b)
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

void	ft_exec_cmd(int cmd, t_stack *a, t_stack *b)
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
