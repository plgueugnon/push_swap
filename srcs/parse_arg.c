#include "pushswap.h"

long	ft_atol(const char *str)
{
	long	s;
	long	r;

	s = 1;
	r = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str == '-')
	{
		s *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
	{
		r = r * 10 + *str - 48;
		str++;
	}
	return (r * s);
}

int	ft_check_char_n_len(char *str, t_lstack *a)
{
    int i;
    int s;

    i = 0;
    s = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            break;
        if ((str[i] >= 48 && str[i] <= 57) && ((str[i - 1] == '-' 
            && (str[i - 2] >= 48 && str[i - 2] <= 57)) || (str[i + 1] == '-')))
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

void    ft_check_no_double_zero(t_lstack *a, int *tab, int c)
{
    int i;
    int flag;

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

void    ft_duplicates_check(t_lstack *a, int *tab, int c)
{
    int i;
    int j;
    t_node *iter;

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

void    ft_init_tab(int *tab, int c)
{
    int i;

    i = 0;
    while (i < c)
    {
        tab[i] = 0;
        i++;
    }
}

void    ft_check_no_duplicates(t_lstack *a)
{
    int *tab;
    t_node *iter;
    int c;

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

void    ft_parse_arg(char *argv, t_lstack *a)
{
    long r;
    int l;

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