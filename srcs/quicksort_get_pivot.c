/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_get_pivot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:49:37 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 16:16:52 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	ft_copy_stack_to_tab(t_stack *a, int *tab)
{
	t_node	*iter;
	int		i;

	i = 0;
	iter = a->front;
	while (iter)
	{
		tab[i] = iter->n;
		i++;
		iter = iter->next;
	}
}

static void	ft_get_chunks_limit(int *limit, int chunks, int size)
{
	int	j;

	j = 1;
	limit[0] = size / chunks;
	while (j < chunks)
	{
		limit[j] = (size / chunks) + limit[j - 1];
		j++;
	}
}

static int	ft_chunks_size(int size)
{
	if (size > 100)
		return (12);
	else
		return (5);
}

static int	ft_stack_up_pivot(int *tab, t_stack *pivot, int size)
{
	int	i;
	int	chunks;
	int	limit[12];
	int	j;

	chunks = ft_chunks_size(size);
	i = 0;
	j = 0;
	ft_get_chunks_limit(limit, chunks, size);
	while (i < size)
	{
		if (j < chunks)
		{
			if (i == limit[j])
			{
				if (!ft_queue_to_stack(pivot, tab[i]))
					return (0);
				j++;
			}
		}
		i++;
	}
	if (!ft_queue_to_stack(pivot, tab[size - 1]))
		return (0);
	return (1);
}

void	ft_get_pivot(t_stack *a, t_stack *b, t_stack *cmd, t_stack *pivot)
{
	int	*tab;
	int	size;

	size = ft_stack_len(a);
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
