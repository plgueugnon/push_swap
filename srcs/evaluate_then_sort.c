#include "pushswap.h"

int     ft_stack_max_value(t_lstack *s)
{
    t_node *iter;
    int max;

    iter = s->front;
    max = s->front->n;
    while (iter)
    {
        if (max < iter->n)
            max = iter->n;
        iter = iter->next;
    }
    return (max);
}

int     ft_stack_min_value(t_lstack *s)
{
    t_node *iter;
    int min;

    iter = s->front;
    min = s->front->n;
    while (iter)
    {
        if (min > iter->n)
            min = iter->n;
        iter = iter->next;
    }
    return (min);
}

int     ft_index_value(t_lstack *s, int nb)
{
    int i;
    t_node *iter;

    i = 0;
    iter = s->front;
    while (iter)
    {
        if (iter->n == nb)
            return (i);
        i++;
        iter = iter->next;
    }
    return (i);
}

int     ft_quantity_to_sort(t_lstack *a)
{
    t_node *iter;
    int c;

    c = 0;
    iter = a->front;
    while (iter)
    {
        c++;
        iter = iter->next;
    }
    return (c);
}

void    ft_exec_n_stash_cmd(t_lstack *a, t_lstack *b, t_lstack *cmd, int ccode)
{
    if (!ft_queue_to_stack(cmd, ccode))
        ft_error_all(a, b, cmd);
    ft_exec_cmd(ccode, a, b);
}

void    ft_sort_three(t_lstack *a, t_lstack *b, t_lstack *cmd)
{
    int i;
    t_node *iter;

    iter = a->front->next;
    i = ft_index_value(a, ft_stack_max_value(a));
    if (i == 0)
        ft_exec_n_stash_cmd(a, b, cmd, RA);
    else if (i == 1)
        ft_exec_n_stash_cmd(a, b, cmd, RRA);
    iter = a->front->next;
    if (a->front->n > iter->n)
        ft_exec_n_stash_cmd(a, b, cmd, SA);
}

void    ft_empty_stack(t_lstack *a, t_lstack *b, t_lstack *cmd, int ccode)
{
    t_node *iter;

    iter = NULL;
    if (ccode < PA && ccode > PB)
        return ;
    if (ccode == PA)
        iter = b->front;
    else if (ccode == PB)
        iter = a->front;
    while (iter)
    {
        iter = iter->next; // NB iterer avant remove sinon error carfree
        ft_exec_n_stash_cmd(a, b, cmd, ccode);
    }
}

void    ft_sort_small_stack(t_lstack *a, t_lstack *b, t_lstack *cmd, int total)
{
    int index;

    index = 0;
    while (total > 3)
    {
        index = ft_index_value(a, ft_stack_min_value(a));
        if (index < total / 2)
            while (index--)
                ft_exec_n_stash_cmd(a, b, cmd, RA);
        else
            while (index++ < total)
                ft_exec_n_stash_cmd(a, b, cmd, RRA);
        ft_exec_n_stash_cmd(a, b, cmd, PB);
        total--;
    }
    ft_sort_three(a, b, cmd);
    ft_empty_stack(a, b, cmd, PA);
}

void    ft_copy_stack_to_tab(t_lstack *a, int *tab)
{
    t_node *iter;
    int i;

    i = 0;
    iter = a->front;
    while (iter)
    {
        tab[i] = iter->n;
        i++;
        iter = iter->next;
    }
}

void    ft_tab_insert_sort(int *tab, int size)
{
    int tmp;
    int i;
    int j;

    i = 0;
    tmp = 0;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (tab[j] < tab[i])
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

int    ft_stack_up_pivot(int *tab, t_lstack *pivot, int size)
{
    int i;
    int mquarter;

    int limit[10];
    int j;

    j = 1;
    i = 0;
    mquarter = size / 1.33;
    //printf("%d\n", mquarter);
    // if (size > 100)
    //     mquarter = 375;
    limit[0] = size / 10;
    if (size > 100)
    {
        while (j < 10)
        {
            limit[j] = (size / 10) + limit[j - 1];
            j++;
        }
    }
    // j = 0;
    // while (j < 10)
    // {
    //     printf("%d ", limit[j]);
    //     j++;
    // }
    j = 0;
    while (i < size)
    {
        if (size > 100 && j < 10)
        {
            if (i == limit[j] && j < 10)
            {
                if (!ft_queue_to_stack(pivot, tab[i]))
                {
                    ft_cleanup_stack(pivot);
                    return(0);
                }
                j++;
            }
        }
        else
        {
            if (i == 20 || i == 40 || i == 60 || i == 80)
                if (!ft_queue_to_stack(pivot, tab[i]))
                {
                    ft_cleanup_stack(pivot);
                    return(0);
                }
        }
        i++;
    }
    // printf("check 1\n");
    // t_node *iter = pivot->front;
    // while (iter)
    // {
    //     printf("pivot = %d\n", iter->n);
    //     iter = iter->next;
    // }
    if (!ft_queue_to_stack(pivot, tab[size - 1]))
    {
        ft_cleanup_stack(pivot);
        return(0);
    }
    return (1);
}

void    ft_get_pivot(t_lstack *a, t_lstack *b, t_lstack *cmd, t_lstack *pivot)
{
    int *tab;
    int size;
    int i;

    i = 0;
    size = ft_quantity_to_sort(a);
    //printf("check size 1 = %d\n", size);
    tab = malloc(sizeof(int) * size);
    if (!tab)
    {
        ft_cleanup_stack(pivot);
        ft_error_all(a, b, cmd);
    }
    ft_copy_stack_to_tab(a, tab);
    ft_tab_insert_sort(tab, size);
    if (!ft_stack_up_pivot(tab, pivot, size))
        ft_error_all(a, b, cmd);
    // t_node *iter = pivot->front;
    // while (iter)
    // {
    //     printf("pivot = %d\n", iter->n);
    //     iter = iter->next;
    // }

}
// MODELE QUI MARCHE PAS TOUCHER
    // int max;
    // int min;
    // int c;

    // c = ft_quantity_to_sort(a);
    // max = ft_stack_max_value(a);
    // min = ft_stack_min_value(a);
    // if (c > 5) // a modif
    // {
    //     if (a->rear->n == max || a->rear->n == min) // pour eviter au mieux les mauvais pivot
    //         ft_exec_n_stash_cmd(a, b, cmd, RRA);
    //     if (a->rear->n == max || a->rear->n == min)
    //        ft_exec_n_stash_cmd(a, b, cmd, RRA);
    // }
    // if (!ft_add_to_stack(pivot, a->rear->n))
    // {
    //     ft_cleanup_stack(pivot);
    //     ft_error_all(a, b, cmd);
    // }
// }

void    ft_quicksort(t_lstack *a, t_lstack *b, t_lstack *cmd, t_lstack *pivot)
{
    t_node *iter;
   // int c;
    int i;

    iter = a->front;
    i = 0;
    while (a->front)
    {
        while(a->front->n != pivot->front->n)
        {
            if (a->front->n > pivot->front->n)
            {
                // if (b->front && b->front->next && a->front) // faible gain de perf
                //     if (b->front->n < b->front->next->n 
                //         && a->front->n > a->front->next->n &&
                //         a->front->next->n > pivot->front->n)
                //             ft_exec_n_stash_cmd(a, b, cmd, SS);
                ft_exec_n_stash_cmd(a, b, cmd, RA);
                // if (a->front->next && a->front)
                    // if (a->front->n != pivot->front->n && a->front->n > a->front->next->n)
                        // ft_exec_n_stash_cmd(a, b, cmd, SA);
            }
            else if (a->front->n < pivot->front->n)
            {
                //printf("PB = %d\n", a->front->n);
                ft_exec_n_stash_cmd(a, b, cmd, PB);
                // if (b->front && b->front->next && a->front && a->front->next) // faible gain de perf
                //     if (b->front->n < b->front->next->n 
                //         && a->front->n > a->front->next->n &&
                //         a->front->next->n > pivot->front->n)
                //             ft_exec_n_stash_cmd(a, b, cmd, SS);
            }
            // if (b->front && b->front->next && a->front && a->front->next) // faible gain de perf
            //     if (b->front->n < b->front->next->n 
            //         && a->front->n > a->front->next->n &&
            //         a->front->next->n > pivot->front->n)
            //             ft_exec_n_stash_cmd(a, b, cmd, SS);
            // if (b->front && b->front->next)
            //     if (b->front->n < b->front->next->n)
            //         ft_exec_n_stash_cmd(a, b, cmd, SB);
        }
        //printf("RA p = %d, pivot = %d\n", a->front->n, pivot->front->n);
        ft_exec_n_stash_cmd(a, b, cmd, RA);
        while(a->front->n != pivot->front->n)
        {
            if (a->front->n > pivot->front->n)
            {
                ft_exec_n_stash_cmd(a, b, cmd, RA);
            }
            else if (a->front->n < pivot->front->n)
            {
                //printf("PB = %d\n", a->front->n);
                ft_exec_n_stash_cmd(a, b, cmd, PB);
               // if (b->front && b->front->next && a->front && a->front->next) // faible gain de perf
                //    if (b->front->n < b->front->next->n 
                        // && a->front->n > a->front->next->n &&
                        // a->front->next->n > pivot->front->n)
                            // ft_exec_n_stash_cmd(a, b, cmd, SS);
            }
            // if (b->front && b->front->next)
            //     if (b->front->n < b->front->next->n)
            //             ft_exec_n_stash_cmd(a, b, cmd, SB);
            // if (b->front && b->front->next && a->front && a->front->next) // faible gain de perf
            //     if (b->front->n < b->front->next->n 
            //         && a->front->n > a->front->next->n &&
            //         a->front->next->n > pivot->front->n)
            //             ft_exec_n_stash_cmd(a, b, cmd, SS);
        }
        //printf("PB p = %d, pivot = %d\n", a->front->n, pivot->front->n);
        ft_exec_n_stash_cmd(a, b, cmd, PB);
        ft_remove_from_stack(pivot);
        // while(pivot->front)
        // {
        //     if (pivot->front == NULL)
        //         break ;
        //     if (iter->n > pivot->front->n)
        //     {
        //         //printf("RA = %d\n", a->front->n);
        //         ft_exec_n_stash_cmd(a, b, cmd, RA);
        //     }
        //     else if (iter->n < pivot->front->n)
        //     {
        //         printf("PB = %d\n", a->front->n);
        //         ft_exec_n_stash_cmd(a, b, cmd, PB);
        //     }
        //     iter = a->front;
        //     if (iter->n == pivot->front->n)
        //     {
        //         i++;
        //         if (i == 2)
        //         {
        //             printf("check pivot = %d\n", pivot->front->n);
        //             ft_remove_from_stack(pivot);
        //             i = 0;
        //         }
        //     }
        // }
        // ft_exec_n_stash_cmd(a, b, cmd, PB);
        // printf("PB2 = %d\n", a->front->n);
        // if (b->front && b->front->next)
        //     if (b->front->n < b->front->next->n)
        //         ft_exec_n_stash_cmd(a, b, cmd, SB);
    }




    // FIRST TRY NOT QUITE WORKING
    // int size;
    // int flag;

    // flag = 0;
    // size = 0;
    // // printf("check stack a\n");
    // // t_node *iter = a->front;
    // // while (iter)
    // // {
    // //     printf("%d, ", iter->n);
    // //     iter = iter->next;
    // // }
    // // printf("\n\nMAX = %d\n\n", ft_stack_max_value(a));
    // while (a->front)
    // {
    //     //if (!pivot->front)
    //     //    ft_exec_n_stash_cmd(a, b, cmd, PB);
    //     size = ft_quantity_to_sort(a);
    //     //printf("\n\nsize each turn = %d\n", size);
    //     //printf("p = %d\n", pivot->front->n);
    //     //flag = 0;
    //     while (flag != 2)
    //     {
    //         //printf("a = %p\n", a->front);
    //         //printf("p = %p\n", pivot->front);

    //         if (a->front->n < pivot->front->n)
    //             ft_exec_n_stash_cmd(a, b, cmd, PB);
    //         else if (a->front->n > pivot->front->n)
    //             ft_exec_n_stash_cmd(a, b, cmd, RA);
    //         if (a->front->n == pivot->front->n)
    //         {
    //             if (flag == 0)
    //                 flag = 1;
    //             if (flag == 1 && pivot->front->next)
    //             {
    //                 ft_remove_from_stack(pivot);
    //                 flag = 0;
    //             }
    //             if (flag == 1 && !pivot->front->next)
    //             {
    //                 ft_remove_from_stack(pivot);
    //                 flag = 2;
    //             }

    //             // printf("what's left\n");
    //             // t_node *iter = a->front;
    //             // while (iter)
    //             // {
    //             //     printf("%d, ", iter->n);
    //             //     iter = iter->next;
    //             // }
    //             // ft_remove_from_stack(pivot);
    //         }
    //     }
    //     //ft_remove_from_stack(pivot);
    //     ft_exec_n_stash_cmd(a, b, cmd, PB);
    // }




    // MODELE QUI MARCHE A NE PAS MODIF
    // t_node *iter;

    // ft_get_pivot(a, b, cmd, pivot);
    // iter = a->front;
    // while (iter->n != pivot->front->n) // modif pour suppr iter ici
    // {
    //     // iter = a->front;
    //     if (iter->n > pivot->front->n)
    //     {
    //         // if (a->front->n > a->front->next->n && a->front->next->n > pivot->front->n)
    //         //     ft_exec_n_stash_cmd(a, b, cmd, SA);
    //         // if (b->front && b->front->next && a->front) // faible gain de perf
    //         //     if (b->front->n < b->front->next->n 
    //         //     && a->front->n > a->front->next->n &&
    //         //      a->front->next->n > pivot->front->n)
    //                 // ft_exec_n_stash_cmd(a, b, cmd, SS);
    //         ft_exec_n_stash_cmd(a, b, cmd, RA);
    //     }
    //     else if (iter->n < pivot->front->n)
    //     {
    //         ft_exec_n_stash_cmd(a, b, cmd, PB);
    //         //printf("PA -> value: %d\n", b->front->n);
    //     }
    //     iter = a->front;
    // }
    // //printf("check iter = %d == check pivot = %d\n", iter->n, pivot->front->n);
    // ft_exec_n_stash_cmd(a, b, cmd, PB);
    // if (b->front && b->front->next)
    //     if (b->front->n < b->front->next->n)
    //         ft_exec_n_stash_cmd(a, b, cmd, SB); // si num envoye sur b < a celui pop avant => switch
    // //printf("PA -> pivot: %d\n", b->front->n);
}

int     ft_get_pivot_range(t_lstack *b, t_lstack *pivot)
{
    t_node *iter;
    int c;

    c = 0;
    iter = b->front;
    if (!pivot->front)
        return (0);
    if (!pivot->front->next)
        return (1);
    while (iter)
    {
        if (b->front->n == pivot->front->next->n)
            break ;
        c++;
        iter = iter->next;
    }
    return (c - 1);
}

int     ft_is_pivot(t_node *iter, t_lstack *pivot)
{
    if (iter->n == pivot->front->n) // si je me trouve sur le 2e pivot
    {
        //printf("check break pivot");
        //ft_remove_from_stack(pivot); // j'elimine le 1er pivot
        return (1); // je sors de la 2e boucle pour revenir a la premiere
    }
    return (0);
}

int     ft_max_between_pivot(t_lstack *b, int pivot)
{
    t_node *iter;
    int max;
    int i;

    i = 0;
    iter = b->front;
    max = b->front->n;
    while (iter->n != pivot)
    {
        if (max < iter->n)
            max = iter->n;
        iter = iter->next;
    }
    iter = b->front;
    while (iter)
    {
        if (iter->n == max)
            return (i);
        i++;
        iter = iter->next;
    }
    return (i);
}

void    ft_sort_b(t_lstack *a, t_lstack *b, t_lstack *cmd, t_lstack *pivot)
{
    t_node *iter;
    int r;
    int s;
    int i;

    r = 0;
    s = 0;
    iter = b->front; // NB iter n'a pas l'air utile ici
    iter = pivot->front;
    s = ft_quantity_to_sort(b);
    while (!ft_stack_is_empty(b))
    {
        // prendre 1er pivot
        // push a
        // j'identifie le 2e pivot
        // j'identifie la valeur max au dessus du 2e pivot
        // je boucle a l'infini sur b?
        // si ma valeur est superieure au 2e pivot
        // push a
        // sinon RRB ou RB selon position de max
        // des que plus de valeur au dessus du 2e pivot - break pour revenir a la boucle ppale
        // 
        i = ft_index_value(b, ft_stack_max_value(b));
        if (i == 1)
            ft_exec_n_stash_cmd(a, b, cmd, SB);
        else if (i < s / 2)
            while (i--)
                ft_exec_n_stash_cmd(a, b, cmd, RB);
        else
            while (i++ < s)
                ft_exec_n_stash_cmd(a, b, cmd, RRB);
        if (b->front)
        {
            if (b->front->n == ft_stack_max_value(b))
            {
                //printf("PA -> value: %d\n", b->front->n);
                ft_exec_n_stash_cmd(a, b, cmd, PA);
                s--;
            }
        }
    }
        

        // if (pivot->front && pivot->front->next) // + de 2 pivot
        // {
        //     r = pivot->front->next->n; // r devient valeur du 2e pivot
        //     ft_exec_n_stash_cmd(a, b, cmd, PA);
        //     printf("PA -> pivot: %d\n", pivot->front->n);
        //     ft_remove_from_stack(pivot);
        //     s = ft_quantity_to_sort(b);
        //     while (b->front->n > r)
        //     {
        //         i = ft_max_between_pivot(b, r);
        //         if (i == 1)
        //             ft_exec_n_stash_cmd(a, b, cmd, SB);
        //         else if (i < s / 2)
        //             while (i--)
        //                 ft_exec_n_stash_cmd(a, b, cmd, RB);
        //         else if (i > s / 2)
        //             while (i++ < s)
        //                 ft_exec_n_stash_cmd(a, b, cmd, RRB);
        //         printf("PA1 -> value: %d\n", b->front->n);
        //         ft_exec_n_stash_cmd(a, b, cmd, PA);
        //     }
        // }
        // if (!pivot->front->next)
        // {
        //     //r = pivot->front->n; // r devient valeur du 2e pivot
        //     ft_exec_n_stash_cmd(a, b, cmd, PA);
        //     printf("PA2 -> pivot: %d\n", pivot->front->n);
        //     ft_remove_from_stack(pivot);
        //     s = ft_quantity_to_sort(b);
        //     r = s;
        //     while (r--)
        //     {
        //         i = 0;
        //         if (!pivot->front)
        //             break ;
        //         if (ft_is_pivot(b->front, pivot))
        //             break ;
        //         i = ft_max_between_pivot(b, pivot->front->n);
        //         if (i == 1)
        //             ft_exec_n_stash_cmd(a, b, cmd, SB);
        //         else if (i < s / 2)
        //             while (i--)
        //                 ft_exec_n_stash_cmd(a, b, cmd, RB);
        //         else if (i > s / 2)
        //             while (i++ < s)
        //                 ft_exec_n_stash_cmd(a, b, cmd, RRB);
        //         printf("PA2 -> value: %d\n", b->front->n);
        //         ft_exec_n_stash_cmd(a, b, cmd, PA);
        //     }
        // }






        // while (!ft_stack_is_empty(pivot)) // probleme pour dernier chunk
        // {
        //     r = ft_get_pivot_range(b, pivot);
        //     printf("PA -> pivot: %d\n", b->front->n);
        //     ft_exec_n_stash_cmd(a, b, cmd, PA);
        //     ft_remove_from_stack(pivot);
        //     //iter = b->front;
        //     s = ft_quantity_to_sort(b);
        //     while (r--)
        //     {
        //         i = 0;
        //         if (!pivot->front)
        //             break ;
        //         if (ft_is_pivot(b->front, pivot))
        //             break ;
        //         i = ft_max_between_pivot(b, pivot->front->n);
        //         if (i == 1)
        //             ft_exec_n_stash_cmd(a, b, cmd, SB);
        //         else if (i < s / 2)
        //             while (i--)
        //                 ft_exec_n_stash_cmd(a, b, cmd, RB);
        //         else if (i > s / 2)
        //             while (i++ < s)
        //                 ft_exec_n_stash_cmd(a, b, cmd, RRB);
        //         printf("PA1 -> value: %d\n", b->front->n);
        //         ft_exec_n_stash_cmd(a, b, cmd, PA);
        //         //iter = b->front;
        //     }
        // }


        // s = ft_quantity_to_sort(b);
        // i = ft_index_value(b, ft_stack_max_value(b));
        // if (i == 1)
        //     ft_exec_n_stash_cmd(a, b, cmd, SB);
        // else if (i < s / 2)
        //     while (i--)
        //         ft_exec_n_stash_cmd(a, b, cmd, RB);
        // else
        //     while (i++ < s)
        //         ft_exec_n_stash_cmd(a, b, cmd, RRB);
        // ft_exec_n_stash_cmd(a, b, cmd, PA);
        // if (b->front)
        //     printf("PA2 -> value: %d\n", b->front->n);
        // s--;
    //}
    //     while (!ft_stack_is_empty(pivot))
    //     {
    //         r = ft_get_pivot_range(b, pivot);
    //         printf("PA -> pivot: %d\n", b->front->n);
    //         ft_exec_n_stash_cmd(a, b, cmd, PA);
    //         ft_remove_from_stack(pivot);
    //         iter = b->front;
    //         s = ft_quantity_to_sort(b);
    //         while (r--)
    //         {
    //             i = 0;
    //             if (!iter || !pivot->front)
    //                 break ;
    //             if (ft_is_pivot(iter, pivot))
    //                 break ;
    //             i = ft_max_between_pivot(b, pivot->front->n);
    //             if (i == 1)
    //                 ft_exec_n_stash_cmd(a, b, cmd, SB);
    //             else if (i < s / 2)
    //                 while (i--)
    //                     ft_exec_n_stash_cmd(a, b, cmd, RB);
    //             else if (i > s / 2)
    //                 while (i++ < s)
    //                     ft_exec_n_stash_cmd(a, b, cmd, RRB);
    //             printf("PA1 -> value: %d\n", b->front->n);
    //             ft_exec_n_stash_cmd(a, b, cmd, PA);
    //             iter = b->front;
    //         }
    //     }
    //     s = ft_quantity_to_sort(b);
    //     i = ft_index_value(b, ft_stack_max_value(b));
    //     if (i == 1)
    //         ft_exec_n_stash_cmd(a, b, cmd, SB);
    //     else if (i < s / 2)
    //         while (i--)
    //             ft_exec_n_stash_cmd(a, b, cmd, RB);
    //     else
    //         while (i++ < s)
    //             ft_exec_n_stash_cmd(a, b, cmd, RRB);
    //     ft_exec_n_stash_cmd(a, b, cmd, PA);
    //     if (b->front)
    //         printf("PA2 -> value: %d\n", b->front->n);
    //     s--;
    // }
}

void    ft_sort_big_stack(t_lstack *a, t_lstack *b, t_lstack *cmd)
{
    t_lstack *pivot;

    pivot = ft_init_stack();
    if (!pivot)
        ft_error_all(a, b, cmd);
    ft_get_pivot(a, b, cmd, pivot);
    // t_node *test = pivot->front;
    // while (test)
    // {
    //     printf("pivot list : %d\n", test->n);
    //     test = test->next;
    // }
    //while (!ft_stack_is_empty(a))
    ft_quicksort(a, b, cmd, pivot);
    // t_node *test = pivot->front;
    // while (test)
    // {
    //     printf("pivot list : %d\n", test->n);
    //     test = test->next;
    // }
    
   ft_sort_b(a, b, cmd, pivot);
}

void    ft_print_cmd(t_lstack *cmd) // a ameliorer ou suppr pr privilegier impression directe
{
    t_node *iter;

    iter = cmd->front;
    while (iter)
    {
        if (iter->n == SA)
            ft_putstr("sa\n");
        else if (iter->n == SB)
            ft_putstr("sb\n");
        else if (iter->n == SS)
            ft_putstr("ss\n");
        else if (iter->n == RA)
            ft_putstr("ra\n");
        else if (iter->n == RB)
            ft_putstr("rb\n");
        else if (iter->n == RR)
            ft_putstr("rr\n");
        else if (iter->n == RRR)
            ft_putstr("rrr\n");
        else if (iter->n == RRA)
            ft_putstr("rra\n");
        else if (iter->n == RRB)
            ft_putstr("rrb\n");
        else if (iter->n == PA)
            ft_putstr("pa\n");
        else if (iter->n == PB)
            ft_putstr("pb\n");
        iter = iter->next;
    }
}

void    ft_evaluate_then_sort(t_lstack *a, t_lstack **cmd)
{
    t_lstack *b;
    int count;

    count = ft_quantity_to_sort(a);
    b = ft_init_stack();
    *cmd = ft_init_stack();
    if (!b || !*cmd)
        ft_error_all(a, b, *cmd);
    if (ft_evaluate_stack(a, b)) // si tout est trie je quit
        ft_exit(a, b, *cmd, "");
    if (count < 4)
        ft_sort_three(a, b, *cmd);
    else if (count > 3 && count < 11)
        ft_sort_small_stack(a, b, *cmd, count);
    else if (count >= 11)
        ft_sort_big_stack(a, b, *cmd);
    ft_print_cmd(*cmd);
    ft_exit(a, b, *cmd, "");
}