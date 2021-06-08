/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:47:20 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 16:28:02 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_stack	*ft_init_stack(void)
{
	t_stack	*s;

	s = malloc(sizeof(t_stack));
	if (!s)
		return (0);
	s->front = NULL;
	s->rear = NULL;
	return (s);
}

void	ft_remove_from_stack(t_stack *s)
{
	t_node	*tmp;

	if (s->front == s->rear)
	{
		s->front->n = 0;
		free(s->front);
		s->front = NULL;
	}
	else
	{
		tmp = s->front;
		s->front = s->front->next;
		free(tmp);
		tmp = NULL;
	}
}

void	ft_cleanup_stack(t_stack *s)
{
	while (s->front)
		ft_remove_from_stack(s);
	if (s)
		free(s);
	s = NULL;
}

int	ft_add_to_stack(t_stack *s, int n)
{
	t_node	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (0);
	if (tmp)
	{
		tmp->n = n;
		tmp->next = NULL;
	}
	if (s->front)
	{
		tmp->next = s->front;
		s->front = tmp;
		s->front->next = tmp->next;
	}
	else
	{
		s->front = s->rear;
		s->front = tmp;
		s->rear = s->front;
		s->rear = tmp;
	}
	return (1);
}

int	ft_queue_to_stack(t_stack *s, int n)
{
	t_node	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (0);
	if (tmp)
	{
		tmp->n = n;
		tmp->next = NULL;
	}
	if (s->front)
	{
		s->rear->next = tmp;
		s->rear = tmp;
	}
	else
	{
		s->front = s->rear;
		s->front = tmp;
		s->rear = s->front;
		s->rear = tmp;
	}
	return (1);
}
