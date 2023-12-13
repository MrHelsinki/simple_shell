#include "shell.h"

/**
 * printEnvironment - Prints the current environment.
 * @inform: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int printEnvironment(inform_t *inform)
{
    list_t *node = inform->env;

    while (node != NULL)
    {
        printf("%s\n", node->str);
        node = node->next;
    }

    return 0;
}

/**
 * getenvValue - Gets the value of an environment variable.
 * @inform: Structure containing potential arguments. Used to maintain
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(inform_t *inform, const char *name)
{
    list_t *node = inform->env;
    char *value = NULL;

    while (node != NULL)
    {
        if (it_starts_with(node->str, name))
        {
            value = strchr(node->str, '=');
            if (value != NULL)
            {
                value++;
                return value;
            }
        }
        node = node->next;
    }

    return NULL;
}

/**
 * setEnvironment - Initializes a new environment variable or modifies an existing one.
 * @inform: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on success, 0 on failure.
 */
int setEnvironment(inform_t *inform)
{
    if (inform->argumentCount != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(inform, inform->arguments[1], inform->arguments[2]))
        return 0;
    return 1;
}
/**
 * removeEnvironmentVariable - Removes an environment variable
 * @inform: Structure containing relevant information. Used to maintain
 *        consistent function prototype.
 * Return: Always 0
 */
int removeEnvironmentVariable(inform_t *inform)
{
    int i;

    if (inform->argumentCount <= 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i < inform->argumentCount; i++)
        _unsetenv(inform, inform->arguments[i]);

    return (0);
}

/**
 * populateEnvironmentList - Populates the environment linked list
 * @inform: Structure containing relevant information. Used to maintain
 *          consistent function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(inform_t *inform)
{
    list_t *node = NULL;
    size_t i = 0;

    while (environment[i])
    {
        add_newnode(&node, environment[i], 0);
        i++;
    }
    inform->env = node;
    return (0);
}
