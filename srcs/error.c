/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:46:55 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 15:39:19 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_del(void *content)
{
	free(content);
	content = NULL;
}

void	ft_error_cmd(t_list *list, t_stack *a)
{
	ft_lstclear(&list, &ft_del);
	ft_cleanup_stack(a);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	ft_error_stack(t_stack *s)
{
	ft_cleanup_stack(s);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	ft_error_all(t_stack *a, t_stack *b, t_stack *cmd)
{
	ft_cleanup_stack(a);
	ft_cleanup_stack(b);
	ft_cleanup_stack(cmd);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	ft_exit(t_stack *a, t_stack *b, t_stack *cmd, char *msg)
{
	ft_cleanup_stack(a);
	ft_cleanup_stack(b);
	ft_cleanup_stack(cmd);
	ft_putstr(msg);
	exit(0);
}
