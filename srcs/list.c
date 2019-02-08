#include "../includes/ft_select.h"

t_options *copy_arguments_to_linked_list(char **av, int ac)
{
    t_options *ret;
    int count;

    count = 1;
    ret = NULL;
    while (count != ac )
        create_and_push_list_nodes(&ret, av[count++]);
    return (ret);
}

void create_and_push_list_nodes(t_options **ret, char *name)
{
    t_options *new;
    t_options *ptr;

    ptr = *ret;
    new = malloc(sizeof(t_options));
    new->name = ft_strdup(name);
    new->next = NULL;
    new->cursor = 0;
    new->selected = 0;
    new->deleted = 0;
    if (*ret == NULL)
    {
        new->cursor = 1;
        *ret = new;  
    }  
    else
    {
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = new;
    }
}

void duplicate_node(t_options *node_ptr, t_options **ptr_to_head)
{
    t_options *new;
    t_options *list;

    list = *ptr_to_head;
    new = malloc(sizeof(t_options));
    new->name = ft_strdup(node_ptr->name);
    new->next = NULL;
    new->selected = 0;
    new->cursor = 0;
    new->deleted = 0;
    if(list == NULL)
        *ptr_to_head = new;
    else
    {
        while (list->next)
            list = list->next;
        list->next = new;
    }
}
void duplicate_list(t_options *original, t_options **ptr_to_head)
{
    t_options *list;

    list = original;
    while(list->next != NULL)
    {
        duplicate_node(list, ptr_to_head);
            list = list->next;
    }
}

void free_option_node(t_options *node)
{
    free(node->name);
    node->name = NULL;
    free(node);
}