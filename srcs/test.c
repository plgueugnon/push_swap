#include "pushswap.h"

long int	ft_long_atoi(const char *str)
{
	int	i;
	long int	s;
	long int	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	return (r * s);
}

int	ft_charnumlen(char *str)
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
        {
            ft_putstr("Error\n");
            exit(1);
        }
        if (!(str[i] >= 48 && str[i] <= 57) && str[i] != '-' && str[i] != ' ')
        {
            ft_putstr("Error\n");
            exit(1);
        }
        if (str[i] == '-')
            s = 1;
        i++;
    }
    if ((i > 10 && s == 0) || (i > 11 && s == 1))
    {
        ft_putstr("Error\n");
        exit(1);
    }
    return (i);
}

void    ft_check_arg(char *argv)
{
    int i;
    long int r;
    int l;

    i = 0;
    while (argv[i])
    {
        if ((argv[i] >= 48 && argv[i] <= 57) || argv[i] == '-')
        {
            l = ft_charnumlen(&argv[i]); 
            r = ft_long_atoi(&argv[i]);
            if (r > INT_MAX || r < INT_MIN)
            {
                ft_putstr("Error\n");
                exit(1);
            }
            ft_putnbr(r); // ici add to list Puis check maxmin + doublons
            ft_putstr("\n");//
            i += l; 
        }//check num
        else if (!(argv[i] >= 48 && argv[i] <= 57) || argv[i] != '-'
            || argv[i] != ' ')
        {
            ft_putstr("Error\n");
            exit(1);
        }
        if (argv[i] != 0)
            i++;
    }
}

int     ft_check_cmd_syntax(char *s)
{
    if (s[0] == 's' && (s[1] == 'a' || s[1] == 'b') && s[2] == 0)
        return (1);
    else if (s[0] == 's' && s[1] == 's' && s[2] == 0)
        return (1);
    else if (s[0] == 'p' && (s[1] == 'a' || s[1] == 'b') && s[2] == 0)
        return (1);
    else if (s[0] == 'r' && (s[1] == 'a' || s[1] == 'b') && s[2] == 0)
        return (1);
    else if (s[0] == 'r' && s[1] == 'r' && s[2] == 0)
        return (1);
    if (s[0] == 'r' && s[1] == 'r' && (s[2] == 'a' || s[2] == 'b')
        && s[3] == 0)
        return (1);
    else if (s[0] == 'r' && s[1] == 'r' && s[2] == 'r' && s[3] == 0)
        return (1);
    //else if (s[0] == 0)
    //    return (1);
    else
        return (0);
}

void    ft_del(void *content)
{
    free(content);
    // content = NULL;
}

void    ft_error_cmd(t_list *cmd)
{
    ft_lstclear(&cmd, &ft_del);
    ft_putstr_fd("Error\n", 2);
    exit(1);
}

int    ft_check_cmd_validity(t_list *cmd)
{
    t_list *iter;

    iter = cmd;
    while (iter)
    {
        // ft_putstr("check cmd=");
        // ft_putstr(cmd->content);
        // ft_putstr("\n");
        // ft_putstr(iter->content);
        // ft_putstr("\n");
        if (!ft_check_cmd_syntax(iter->content))
            ft_error_cmd(cmd);
        iter = iter->next;
    }
    // ft_putstr("check 3\n");
    return (1);
}

int    ft_parse_cmd(t_list **cmd)
{
    char *line;

    line = NULL;
    // printf("ad2= %p\n", *cmd);
    while (get_next_line(0, &line) > 0)
    {
        *cmd = ft_lst_append(*cmd, line);
    }
    ft_check_cmd_validity(*cmd);
    // ft_putstr("check 2\n");
    // ft_putstr((*cmd)->content);
    // printf("ad3= %p\n", *cmd);
    return (1);
}

int    main(int argc, char **argv)
{
  //  char *line;
    t_list *list;
    printf("nb arg= %d\n", argc);
    list = NULL;
    if (argc > 1)
    {
        if (argc == 2)
        {
            ft_check_arg(argv[1]);
        }
        else
        {
            for (int i = 1; i < argc; i++)
                ft_check_arg(argv[i]);
        }
    }
    // printf("ad1= %p\n", list);
    ft_parse_cmd(&list);
    // printf("ad4= %p\n", list);
    //ft_putstr(list->content);
    // while (get_next_line(0, &line) > 0)
    // {
    //     list = ft_lst_append(list, line);
    //     //ft_putstr(line);
    //     //ft_putstr("\n");
    // }
    // ft_putstr("check 1\n");
    while (list)
    {
        ft_putstr(list->content);
        ft_putstr("\n");
        list = list->next;        
    }
    ft_lstclear(&list, &ft_del);
    // ft_putstr("\n");
    // ft_putstr("le premier argument est ");
    // ft_putstr(argv[1]);
    // ft_putstr("\n");
    return (0);
}