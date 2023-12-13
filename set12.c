#include "shell.h"

/**
 * add_newnode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *add_newnode(list_t **head, const char *str, int number)
{
    list_t *new_head;

    if (!head)
        return NULL;
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return NULL;
    my_memset((void *)new_head, 0, sizeof(list_t));
    new_head->number = number;
    if (str)
    {
        new_head->str = strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return NULL;
        }
    }
    new_head->next = *head;
    *head = new_head;
    return new_head;
}

/**
 * addnode_tothe_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *addnode_tothe_end(list_t **head, const char *str, int number)
{
    list_t *new_node, *node;

    if (!head)
        return NULL;

    node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;
    my_memset((void *)new_node, 0, sizeof(list_t));
    new_node->number = number;
    if (str)
    {
        new_node->str = strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return NULL;
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return new_node;
}

/**
 * print_liststr - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_liststr(const list_t *head)
{
    size_t k = 0;

    while (head)
    {
        puts(head->str ? head->str : "(nil)");
        puts("\n");
        head= head->next;
        k++;
    }
    return k;
}

/**
 * delete_nodeindex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nodeindex(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i;

    if (!head || !*head)
        return 0;

    if (index == 0)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    prev_node = NULL;
    node = *head;
    i = 0;
    for (; node; node = node->next)
    {
        if (i == index - 1)
        {
            prev_node = node;
            break;
        }
        i++;
    }

    if (!prev_node)
        return 0;

    node = prev_node->next;
    if (!node)
        return 0;

    prev_node->next = node->next;
    free(node->str);
    free(node);
    return 1;
}
