#include "pushswap.h"

void    ft_exec_cmd_n_evaluate(t_lstack *a, t_lstack *cmd)
{
    t_lstack *b;
    t_node *iter;
    int i;

    i = 0;
    b = ft_init_stack();
    iter = cmd->front;
    if (!b)
        ft_error_all(a, b, cmd);
    while (iter)
    {
        ft_exec_cmd(iter->n, a, b);
        iter = iter->next;;
    }
    t_node *itera;//
    t_node *iterb;
    itera = a->front;
    iterb = b->front;
    printf("check exit\n");
    printf("STACK A\n");
    if (itera)
    {
        while (itera)
        {
            printf("%d\n", (int)itera->n);
            itera = itera->next;
        }
    }
    printf("STACK B\n");
    if (iterb)
    {
        while (iterb)
        {
            printf("%d\n", (int)iterb->n);
            iterb = iterb->next;
        }
    }//
    if (ft_evaluate_stack(a, b))
        ft_exit(a, b, cmd, "OK\n");
    else
        ft_exit(a, b, cmd, "KO\n");
}

int     main(int argc, char **argv)
{
    int i;
    t_lstack *cmd;
    t_lstack *a;

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
            while (i < argc)
            {
                ft_parse_arg(argv[i], a);
                i++;
            }
        }
        t_node *iter;
        iter = a->front;
        printf("check entree\n"); //
        while (iter)
        {
            printf("%d\n", (int)iter->n);
            iter = iter->next;
        }
        ft_parse_cmd(&cmd, a);
        ft_exec_cmd_n_evaluate(a, cmd);
    }  
    return (0);
}