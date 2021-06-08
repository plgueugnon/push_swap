/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:47:01 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 16:30:02 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ft_evaluate_stack(t_stack *a, t_stack *b)
{
	t_node	*iter;
	t_node	*jter;

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
		return (0);
	return (1);
}

int	ft_stack_max_value(t_stack *s)
{
	t_node	*iter;
	int		max;

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

int	ft_stack_min_value(t_stack *s)
{
	t_node	*iter;
	int		min;

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

int	ft_index_value(t_stack *s, int nb)
{
	int		i;
	t_node	*iter;

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

int	ft_stack_len(t_stack *s)
{
	t_node	*iter;
	int		c;

	c = 0;
	iter = s->front;
	while (iter)
	{
		c++;
		iter = iter->next;
	}
	return (c);
}
