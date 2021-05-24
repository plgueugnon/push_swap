#include "pushswap.h"

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