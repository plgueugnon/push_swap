#include "pushswap.h"

void    ft_exec_cmd_n_evaluate(t_lstack *a, t_lstack *cmd)
{
    t_lstack *b;
    t_node *iter;

    b = ft_init_stack();
    iter = cmd->front;
    if (!b)
        ft_error_all(a, b, cmd);
    while (iter)
    {
        ft_exec_cmd(iter->n, a, b);
        iter = iter->next;;
    }
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
            while (i < argc)
            {
                ft_parse_arg(argv[i], a);
                i++;
            }
        ft_parse_cmd(&cmd, a);
        ft_exec_cmd_n_evaluate(a, cmd);
    }
    ft_cleanup_stack(a);  
    return (0);
}