#include "../includes/ft_select.h"

t_list *copy_arguments_to_linked_list(char ** av)
{
    t_list *ret;
    int count;

    count = 0;
    ret = NULL;
    while (av[count] != NULL)
        create_and_push_list_nodes(&ret, av[count]);
    return (ret);
}

void create_and_push_list_nodes(t_list **ret, char *name)
{
    t_list *new;
    t_list *ptr;

    ptr = *ret;
    new->name = name;
    new->next = NULL;
    if (*ret == NULL)
      *ret = new;
    else
    {
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = new;
    }
}