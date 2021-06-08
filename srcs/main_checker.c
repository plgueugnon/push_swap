/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:47:33 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 16:26:37 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_exec_cmd_n_evaluate(t_stack *a, t_stack *cmd)
{
	t_stack	*b;
	t_node	*iter;

	b = ft_init_stack();
	iter = cmd->front;
	if (!b)
		ft_error_all(a, b, cmd);
	while (iter)
	{
		ft_exec_cmd(iter->n, a, b);
		iter = iter->next;
	}
	if (ft_evaluate_stack(a, b))
		ft_exit(a, b, cmd, "OK\n");
	else
		ft_exit(a, b, cmd, "KO\n");
}

int	main(int argc, char **argv)
{
	int		i;
	t_stack	*cmd;
	t_stack	*a;

	i = 1;
	cmd = NULL;
	a = ft_init_stack();
	if (!a)
		ft_error_stack(a);
	if (argc > 1)
	{
		if (argc == 2)
			ft_parse_arg(argv[1], a);
		else
		{
			while (i++ < argc)
				ft_parse_arg(argv[i], a);
		}
		ft_parse_cmd(&cmd, a);
		ft_exec_cmd_n_evaluate(a, cmd);
	}
	ft_cleanup_stack(a);
	return (0);
}
