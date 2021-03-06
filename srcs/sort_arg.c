/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:49:43 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 15:50:54 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_pop_n_add_to_other_stack(t_stack *o, t_stack *d)
{
	if (!o->front)
		return ;
	ft_add_to_stack(d, o->front->n);
	ft_remove_from_stack(o);
}

void	ft_push_top_to_bottom(t_stack *s)
{
	t_node	*tmp;

	if (!s->front)
		return ;
	if (s->front->next == NULL)
		return ;
	tmp = s->front->next;
	s->rear->next = s->front;
	s->rear = s->front;
	s->rear->next = NULL;
	s->front = tmp;
	s->front->next = tmp->next;
}

void	ft_push_bottom_to_top(t_stack *s)
{
	t_node	*tmp;

	tmp = s->front;
	if (!s->front)
		return ;
	if (s->front->next == NULL)
		return ;
	while (tmp)
	{
		if (tmp->next == s->rear)
			break ;
		tmp = tmp->next;
	}
	s->rear->next = s->front;
	s->front = s->rear;
	s->front->next = s->rear->next;
	s->rear = tmp;
	s->rear->next = NULL;
}

void	ft_swap_stack_top_two_values(t_stack *s)
{
	t_node	*tmp;

	if (!s->front)
		return ;
	if (s->front->next == NULL)
		return ;
	tmp = s->front->next;
	s->front->next = tmp->next;
	tmp->next = s->front;
	s->front = tmp;
	s->front->next = tmp->next;
}
