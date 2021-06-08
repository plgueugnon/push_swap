/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:06:49 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 15:56:19 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# define SA 1
# define SB 2
# define SS 3
# define PA 4
# define PB 5
# define RA 6
# define RB 7
# define RR 8
# define RRA 9
# define RRB 10
# define RRR 11

typedef struct s_node
{
	int				n;
	struct s_node	*next;
}				t_node;

typedef struct s_stack
{
	t_node	*front;
	t_node	*rear;
}	t_stack;

void	ft_del(void *content);
void	ft_error_cmd(t_list *cmd, t_stack *a);
void	ft_error_stack(t_stack *s);
void	ft_error_all(t_stack *a, t_stack *b, t_stack *cmd);
void	ft_exit(t_stack *a, t_stack *b, t_stack *cmd, char *msg);
int		ft_check_cmd_syntax(char *s);
void	ft_check_cmd_validity(t_list *cmd, t_stack *a);
void	ft_parse_cmd(t_stack **cmd, t_stack *a);
void	ft_remove_from_stack(t_stack *s);
void	ft_cleanup_stack(t_stack *s);
int		ft_stack_is_empty(t_stack *s);
int		ft_add_to_stack(t_stack *s, int n);
t_stack	*ft_init_stack(void);
int		ft_queue_to_stack(t_stack *s, int n);
void	ft_init_tab(int *tab, int c);
int		ft_check_char_n_len(char *str, t_stack *a);
void	ft_duplicates_check(t_stack *a, int *tab, int c);
void	ft_check_no_duplicates(t_stack *a);
void	ft_parse_arg(char *argv, t_stack *a);
void	ft_exec_cmd_n_evaluate(t_stack *a, t_stack *cmd);
void	ft_pop_n_add_to_other_stack(t_stack *o, t_stack *d);
void	ft_push_top_to_bottom(t_stack *s);
void	ft_push_bottom_to_top(t_stack *s);
void	ft_swap_stack_top_two_values(t_stack *s);
int		ft_evaluate_stack(t_stack *a, t_stack *b);
int		ft_stack_max_value(t_stack *s);
int		ft_stack_min_value(t_stack *s);
int		ft_index_value(t_stack *s, int nb);
int		ft_stack_len(t_stack *s);
void	ft_sort_three(t_stack *a, t_stack *b, t_stack *cmd);
void	ft_empty_stack(t_stack *a, t_stack *b, t_stack *cmd, int ccode);
void	ft_sort_small_stack(t_stack *a, t_stack *b, t_stack *cmd, int total);
void	ft_exec_rotate_cmd(int cmd, t_stack *a, t_stack *b);
void	ft_exec_cmd(int cmd, t_stack *a, t_stack *b);
void	ft_evaluate_then_sort(t_stack *a, t_stack **cmd);
void	ft_exec_n_stash_cmd(t_stack *a, t_stack *b, t_stack *cmd, int code);
void	ft_get_pivot(t_stack *a, t_stack *b, t_stack *cmd, t_stack *pivot);
void	ft_sort_big_stack(t_stack *a, t_stack *b, t_stack *cmd);
void	ft_quicksort(t_stack *a, t_stack *b, t_stack *cmd, t_stack *pivot);
void	ft_eval_pivot(t_stack *a, t_stack *b, t_stack *cmd, t_stack *pivot);
void	ft_tab_insertion_sort(int *tab, int size);

#endif
