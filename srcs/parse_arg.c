/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:31:14 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 16:16:34 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ft_check_char_n_len(char *str, t_stack *a)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		if ((str[i] >= 48 && str[i] <= 57) && ((str[i - 1] == '-'
					&& (str[i - 2] >= 48 && str[i - 2] <= 57))
				|| (str[i + 1] == '-')))
			ft_error_stack(a);
		if (!(str[i] >= 48 && str[i] <= 57) && str[i] != '-' && str[i] != ' ')
			ft_error_stack(a);
		if (str[i] == '-')
			s = 1;
		i++;
	}
	if ((i > 10 && s == 0) || (i > 11 && s == 1))
		ft_error_stack(a);
	return (i);
}

static void	ft_check_no_double_zero(t_stack *a, int *tab, int c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < c)
	{
		if (tab[i] == 0)
			flag++;
		if (flag > 1)
		{
			free(tab);
			ft_error_stack(a);
		}
		i++;
	}
}

void	ft_duplicates_check(t_stack *a, int *tab, int c)
{
	int		i;
	int		j;
	t_node	*iter;

	i = 0;
	iter = a->front;
	while (i < c)
	{
		j = 0;
		while (j <= i)
		{
			if (tab[j] == iter->n && iter->n != 0)
			{
				free(tab);
				ft_error_stack(a);
			}
			j++;
		}
		tab[i] = iter->n;
		i++;
		iter = iter->next;
	}
	ft_check_no_double_zero(a, tab, c);
}

void	ft_check_no_duplicates(t_stack *a)
{
	int		*tab;
	t_node	*iter;
	int		c;

	c = 0;
	tab = NULL;
	iter = a->front;
	while (iter)
	{
		c++;
		iter = iter->next;
	}
	tab = malloc(sizeof(int) * c);
	if (!tab)
		ft_error_stack(a);
	ft_init_tab(tab, c);
	ft_duplicates_check(a, tab, c);
	free(tab);
}

void	ft_parse_arg(char *argv, t_stack *a)
{
	long	r;
	int		l;

	l = 0;
	r = 0;
	while (*argv)
	{
		if ((*argv >= 48 && *argv <= 57) || *argv == '-')
		{
			l = ft_check_char_n_len(&(*argv), a);
			r = ft_atol(&(*argv));
			if (r > INT_MAX || r < INT_MIN)
				ft_error_stack(a);
			if (!ft_queue_to_stack(a, r))
				ft_error_stack(a);
			argv += l;
		}
		else if (!(*argv >= 48 && *argv <= 57) || *argv != '-'
			|| *argv != ' ')
			ft_error_stack(a);
		if (*argv != 0)
			argv++;
	}
	ft_check_no_duplicates(a);
}
