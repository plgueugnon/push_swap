/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:38:39 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 15:57:25 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_init_tab(int *tab, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		tab[i] = 0;
		i++;
	}
}

void	ft_tab_insertion_sort(int *tab, int size)
{
	int	tmp;
	int	i;
	int	j;

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
