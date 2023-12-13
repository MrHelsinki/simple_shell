#include "shell.h"

/**
 * setAlias - it is to Sets an alias to a given string.
 * @inform: when Pointer point to the parameter struct.
 * @str: this refers to The string representing the alias.
 * Return: Always 0 on success, 1 on error.
 */
int setAlias(inform_t *inform, char *str)
{
    char *equalPos;

    equalPos = _strchr(str, '=');
    if (!equalPos)
        return 1;
    if (!*++equalPos)
        return   remove_alias(inform, str);

      remove_alias(inform, str);
    return add_newnode(&(inform->alias), str, 0) == NULL;
}

/**
 * printAlias - it is Printing an alias string.
 * @node: well this is the alias node.
 *
 * Return: will Always 0 on success, 1 on error.
 */
int printAlias(list_t *node)
{
    char *equalPos = NULL, *alias = NULL;

    if (node)
    {
        equalPos = _strchr(node->str, '=');
        for (alias = node->str; alias <= equalPos; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(equalPos + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * myAlias - this will Mimics the alias builtin (man alias).
 * @inform: it is the Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0.
 */
int myAlias(inform_t *inform)
{
    int i;
    char *equalPos;
    list_t *node;

    if (inform->argumentCount== 1)
    {
        node = inform->alias;
        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; inform->arguments[i]; i++)
    {
        equalPos = _strchr(inform->arguments[i], '=');
        if (equalPos)
        {
            setAlias(inform, inform->arguments[i]);
        }
    }

    for (i = 1; inform->arguments[i]; i++)
    {
        equalPos = _strchr(inform->arguments[i], '=');
        if (!equalPos)
        {
            node = find_node_starts_with(inform->alias, inform->arguments[i], '=');
            printAlias(node);
        }
    }

    return 0;
}
