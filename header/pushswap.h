
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

typedef struct  s_node
{
    int n;
    struct s_node *next;
}               t_node;

typedef struct  s_lstack
{
    t_node  *front;
    t_node  *rear;
}               t_lstack;

void    ft_del(void *content);
void    ft_error_cmd(t_list *cmd, t_lstack *a);
void    ft_error_stack(t_lstack *s);
void    ft_error_all(t_lstack *a, t_lstack *b, t_lstack *cmd);
void    ft_exit(t_lstack *a, t_lstack *b, t_lstack *cmd, char *msg);

int     ft_check_cmd_syntax(char *s);
void    ft_check_cmd_validity(t_list *cmd, t_lstack *a);
void    ft_parse_cmd(t_lstack **cmd, t_lstack *a);

void    ft_remove_from_stack(t_lstack *s);
void    ft_cleanup_stack(t_lstack *s);
int     ft_stack_is_empty(t_lstack *s);
int    ft_add_to_stack(t_lstack *s, int n);
t_lstack    *ft_init_stack(void);
int    ft_queue_to_stack(t_lstack *s, int n);

long	ft_atol(const char *str);
int	ft_check_char_n_len(char *str, t_lstack *a);
void    ft_duplicates_check(t_lstack *a, int *tab, int c);
void    ft_check_no_duplicates(t_lstack *a);
void    ft_parse_arg(char *argv, t_lstack *a);

void    ft_exec_cmd_n_evaluate(t_lstack *a, t_lstack *cmd);

void    ft_pop_n_add_to_other_stack(t_lstack *o, t_lstack *d);
void    ft_push_top_to_bottom(t_lstack *s);
void    ft_push_bottom_to_top(t_lstack *s);
void    ft_swap_stack_top_two_values(t_lstack *s);

int     ft_stack_max_value(t_lstack *s);
int     ft_stack_min_value(t_lstack *s);
int     ft_index_value(t_lstack *s, int nb);

void    ft_sort_three(t_lstack *a, t_lstack *b, t_lstack *cmd);


int     ft_evaluate_stack(t_lstack *a, t_lstack *b);
void    ft_exec_rotate_cmd(int cmd, t_lstack *a, t_lstack *b);
void    ft_exec_cmd(int cmd, t_lstack *a, t_lstack *b);

void    ft_evaluate_then_sort(t_lstack *a, t_lstack **cmd);

#endif