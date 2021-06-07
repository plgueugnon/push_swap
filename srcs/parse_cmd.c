#include "pushswap.h"

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
    else if (s[0] == 'r' && s[1] == 'r' && (s[2] == 'a' || s[2] == 'b')
        && s[3] == 0)
        return (1);
    else if (s[0] == 'r' && s[1] == 'r' && s[2] == 'r' && s[3] == 0)
        return (1);
    else
        return (0);
}

void    ft_check_cmd_validity(t_list *cmd, t_lstack *a)
{
    t_list *iter;

    iter = cmd;
    while (iter)
    {
        if (!ft_check_cmd_syntax(iter->content))
            ft_error_cmd(cmd, a);
        iter = iter->next;
    }
}

int     ft_encode_cmd(char *s)
{
    if (s[0] == 's' && s[1] == 'a') 
        return (SA);
    if (s[0] == 's' && s[1] == 'b')
        return (SB);
    if (s[0] == 's' && s[1] == 's')
        return (SS);
    if (s[0] == 'p' && s[1] == 'a')
        return (PA);
    if (s[0] == 'p' && s[1] == 'b')
        return (PB);
    if (s[0] == 'r' && s[1] == 'a')
        return (RA);
    if (s[0] == 'r' && s[1] == 'b')
        return (RB);
    if (s[0] == 'r' && s[1] == 'r' && s[2] == 0)
        return (RR);
    if (s[0] == 'r' && s[1] == 'r' && s[2] == 'a')
        return (RRA);
    if (s[0] == 'r' && s[1] == 'r' && s[2] == 'b')
        return (RRB);
    if (s[0] == 'r' && s[1] == 'r' && s[2] == 'r')
        return (RRR);
    return (0);
}

void    ft_transform_cmd_list_to_stack(t_list *list, t_lstack *a, t_lstack **cmd)
{
    t_list *iter;
    
    iter = list;
    *cmd = ft_init_stack();
    if (!*cmd)
        ft_error_cmd(list, a);
    while (iter)
    {
        if(!ft_queue_to_stack(*cmd, ft_encode_cmd(iter->content)))
        {
            ft_cleanup_stack(*cmd);
            ft_error_cmd(list, a);
        }
        iter = iter->next;
    }
    ft_lstclear(&list, &ft_del);
}

void    ft_parse_cmd(t_lstack **cmd, t_lstack *a)
{
    char *line;
    t_list *list;

    line = NULL;
    list = NULL;
    while (get_next_line(0, &line) > 0)
    {
        list = ft_lst_append(list, line);
    }
    free(line);
    ft_check_cmd_validity(list, a);
    ft_transform_cmd_list_to_stack(list, a, cmd);
}