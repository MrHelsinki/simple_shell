#include "shell.h"

/**
 * get_list_length - Determines the length of a linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t get_list_length(const list_t *head)
{
    size_t count = 0;
    const list_t *current = head;

    for (; current != NULL; current = current->next)
        count++;

    return count;
}

/**
 * convert_list_to_strings - Returns an array of strings from the list->str
 * @head: Pointer to the first node
 *
 * Return: Array of strings
 */
char **convert_list_to_strings(list_t *head)
{
    size_t count = get_list_length(head);
    char **str_array = NULL;
    size_t i, j;

    if (head == NULL || count == 0)
        return NULL;

    str_array = malloc(sizeof(char *) * (count + 1));
    if (str_array == NULL)
        return NULL;

    i = 0;
    for (; head != NULL; head = head->next, i++)
    {
        str_array[i] = malloc(_strlen(head->str) + 1);
        if (str_array[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(str_array[j]);
            free(str_array);
            return NULL;
        }

        _strcpy(str_array[i], head->str);
    }

    str_array[i] = NULL;
    return str_array;
}

/**
 * print_linked_list - Prints all elements of a list_t linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_linked_list(const list_t *head)
{
    size_t count = 0;
    const list_t *current = head;

    for (; current != NULL; current = current->next)
    {
        _puts(convert_number_to_string(current->number, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(current->str ? current->str : "(nil)");
        _puts("\n");
        count++;
    }

    return count;
}

/**
 * find_node_starts_with - Returns the node whose string starts with a prefix
 * @head: Pointer to the list head
 * @prefix: String to match
 * @c: The next character after the prefix to match
 *
 * Return: Matched node or NULL
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char c)
{
    for (; head != NULL; head = head->next)
    {
        char *p = it_starts_with(head->str, prefix);
        if (p != NULL && ((c == -1) || (*p == c)))
            return head;
    }

    return NULL;
}

/**
 * get_node_index - Gets the index of a node
 * @head: Pointer to the list head
 * @node: Pointer to the node
 *
 * Return: Index of the node or -1
 */
ssize_t get_nodeindex(list_t *head, list_t *node)
{
    size_t index = 0;

    for (; head != NULL; head = head->next, index++)
    {
        if (head == node)
            return index;
    }

    return -1;
}
