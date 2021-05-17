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
        ft_evaluate_then_sort(a, &cmd);
    }
    return (0);
}