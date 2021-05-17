#include "pushswap.h"

void    ft_del(void *content)
{
    free(content);
    content = NULL;
}

void    ft_error_cmd(t_list *list, t_lstack *a)
{
    ft_lstclear(&list, &ft_del);
    ft_cleanup_stack(a);
    ft_putstr_fd("Error\n", 2);
    exit(1);
}

void    ft_error_stack(t_lstack *s)
{
    ft_cleanup_stack(s);
    ft_putstr_fd("Error\n", 2);
    exit(1);
}

void    ft_error_all(t_lstack *a, t_lstack *b, t_lstack *cmd)
{
        ft_cleanup_stack(a);
        ft_cleanup_stack(b);
        ft_cleanup_stack(cmd);
        ft_putstr_fd("Error\n", 2);
        exit(1);
}

void    ft_exit(t_lstack *a, t_lstack *b, t_lstack *cmd, char *msg)
{
    // t_node *itera;//
    // t_node *iterb;
    // itera = a->front;
    // iterb = b->front;
    // printf("check exit\n");
    // printf("STACK A\n");
    // if (itera)
    // {
    //     while (itera)
    //     {
    //         printf("%d\n", (int)itera->n);
    //         itera = itera->next;
    //     }
    // }
    // printf("STACK B\n");
    // if (iterb)
    // {
    //     while (iterb)
    //     {
    //         printf("%d\n", (int)iterb->n);
    //         iterb = iterb->next;
    //     }
    // }//
    ft_cleanup_stack(a);
    ft_cleanup_stack(b);
    ft_cleanup_stack(cmd);
    ft_putstr(msg);
    exit(0);
}