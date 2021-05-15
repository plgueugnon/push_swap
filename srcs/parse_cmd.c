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

void    ft_transform_cmd_list_to_tab(t_list *list, t_lstack *a, int **cmd)
{
    t_list *iter;
    int c;
    
    c = ft_lstsize(list);
    // printf("%d\n", c);
    iter = list;
    // printf("%p\n", *cmd);
    // printf("%p\n", cmd);
    *cmd = malloc(sizeof(int *) * (c + 1));
    // printf("%p\n", *cmd);
    // printf("%p\n", cmd);
    if (!*cmd)
        ft_error_cmd(list, a);
    c = 0;
    // *(cmd)[0] = 1;
    // printf("%d\n", *(cmd)[0]);
    while (iter)
    {
        (*cmd)[c] = ft_encode_cmd(iter->content);
        // printf("%d\n", (*cmd)[c]);
        c++;
        iter = iter->next;
    }
    (*cmd)[c] = 0;
    ft_lstclear(&list, &ft_del);
}

void    ft_parse_cmd(int **cmd, t_lstack *a)
{
    char *line;
    t_list *list;

    line = NULL;
    list = NULL;
    while (get_next_line(0, &line) > 0)
    {
        list = ft_lst_append(list, line);
        // printf("check line %p\n", line);
        // printf("%s\n", line);
        // printf("%s\n", list->content);
    }
    ft_check_cmd_validity(list, a);
    ft_transform_cmd_list_to_tab(list, a, cmd);
    // printf("%p\n", cmd);
}