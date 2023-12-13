#include "shell.h"

/**
 * get_environment - Returns a copy of the environment variables as a string array.
 * @inform: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: The string array copy of the environment variables.
 */
char **get_environment(inform_t *inform)
{
    if (!inform->environment || inform->env_changed)
    {
        inform->environment= convert_list_to_strings(inform->env);
        inform->env_changed = 0;
    }

    return (inform->environment);
}

/**
 * _unsetenv - Removes an environment variable.
 * @inform: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @var: The environment variable to be removed.
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenv(inform_t *inform, char *var)
{
    list_t *node = inform->env;
    list_t *prev = NULL;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = it_starts_with(node->str, var);
        if (p && *p == '=')
        {
            if (!prev)
                inform->env = node->next;
            else
                prev->next = node->next;
            free(node->str);
            free(node);
            inform->env_changed = 1;
            return (1);
        }
        prev = node;
        node = node->next;
    }

    return (0);
}

/**
 * _setenv - Initializes a new environment variable or modifies an existing one.
 * @inform: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @var: The environment variable to be initialized or modified.
 * @value: The value of the environment variable.
 * Return: Always 0.
 */
int _setenv(inform_t *inform, char *var, char *value)
{
    char *buff = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buff = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buff)
        return (1);
    _strcpy(buff, var);
    _strcat(buff, "=");
    _strcat(buff, value);
    node = inform->env;
    while (node)
    {
        p = it_starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buff;
            inform->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_newnode(&(inform->env), buff, 0);
    free(buff);
    inform->env_changed = 1;
    return (0);
}
