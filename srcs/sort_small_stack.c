/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:50:25 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 15:41:47 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_sort_three(t_stack *a, t_stack *b, t_stack *cmd)
{
	int		i;
	t_node	*iter;

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

void	ft_empty_stack(t_stack *a, t_stack *b, t_stack *cmd, int ccode)
{
	t_node	*iter;

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

void	ft_sort_small_stack(t_stack *a, t_stack *b, t_stack *cmd, int total)
{
	int	index;

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
