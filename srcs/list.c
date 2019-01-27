#include "../includes/ft_select.h"

t_options *copy_arguments_to_linked_list(char **av)
{
    t_options *ret;
    int count;

    count = 0;
    ret = NULL;
    while (av[count] != NULL)
        create_and_push_list_nodes(&ret, av[count]);
    return (ret);
}

void create_and_push_list_nodes(t_options **ret, char *name)
{
    t_options *new;
    t_options *ptr;

    ptr = *ret;
    new = malloc(sizeof(t_options));
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