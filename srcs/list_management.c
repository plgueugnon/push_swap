#include "pushswap.h"

t_lstack    *ft_init_stack(void)
{
    t_lstack *s;

    s = malloc(sizeof(t_lstack));
    if (!s)
        return (0);
    s->front = NULL;
    s->rear = NULL;
    return (s);
}

void    ft_remove_from_stack(t_lstack *s)
{
    t_node *tmp;

    if (s->front == s->rear)
    {
        s->front->n = 0;
        free(s->front);
        s->front = NULL;
        //s->rear = NULL; // a priori redondant peut e suppr
    }
    else
    {
        tmp = s->front;
        s->front = s->front->next; // verif si pas besoin modif s->front->next
        free(tmp);
        tmp = NULL;
    }
}

void    ft_cleanup_stack(t_lstack *s)
{
    while (!ft_stack_is_empty(s))
        ft_remove_from_stack(s);
    if (s)
        free(s);
    s = NULL;
}

int     ft_stack_is_empty(t_lstack *s)
{
    if (s->front == NULL)
        return (1);
    return (0);
}

int    ft_add_to_stack(t_lstack *s, int n)
{
    t_node  *tmp;

    tmp = malloc(sizeof(t_list));
    if (tmp == NULL)
        return (0);
    if (tmp)
    {
        tmp->n = n;
        tmp->next = NULL;
    }
    if (!ft_stack_is_empty(s))
    {
        tmp->next = s->front;
        s->front = tmp;
        s->front->next = tmp->next;
    }
    else
    {
        s->front = s->rear;
        s->front = tmp;
        s->rear = s->front;
        s->rear = tmp;
    }
    return (1);
}

int    ft_queue_to_stack(t_lstack *s, int n)
{
    t_node *tmp;

    tmp = malloc(sizeof(t_list));
    if (tmp == NULL)
        return (0);
    if (tmp)
    {
        tmp->n = n;
        tmp->next = NULL;
    }
    if (!ft_stack_is_empty(s))
    {
        s->rear->next = tmp;
        s->rear = tmp;
    }
    else
    {
        s->front = s->rear;
        s->front = tmp;
        s->rear = s->front;
        s->rear = tmp;
    }
    return (1);
}

int    ft_find_in_stack_range(t_lstack *s, int rstart, int rend)
{
    t_node *iter;
    int count;

    count = 1;
    iter = s->front;
    while (iter)
    {
        if (iter->n >= rstart && iter->n <= rend)
            return (count);
        iter = iter->next;
        count++;
    }
    return (0);
}