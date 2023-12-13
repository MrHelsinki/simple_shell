#include "shell.h"

/**
 * is_chain_char - tests if the current character in the buffer is a chain delimiter
 * @inform: the parameter struct
 * @buffer: the character buffer
 * @adr: address of the current position in buffer
 *
 * Return: 1 if it is a chain delimiter, 0 otherwise
 */
int is_chain_char(inform_t *inform, char *buffer, size_t *adr)
{
    size_t i = *adr;

    while (buffer[i] != '\0') {
        if (buffer[i] == '|' && buffer[i + 1] == '|') {
            buffer[i] = 0;
            i++;
            inform->cmd_buffer_type = CMD_OR;
            *adr = i;
            return 1;
        } else if (buffer[i] == '&' && buffer[i + 1] == '&') {
            buffer[i] = 0;
            i++;
            inform->cmd_buffer_type = CMD_AND;
            *adr = i;
            return 1;
        } else if (buffer[i] == ';') { /* found end of this command */
            buffer[i] = 0; /* replace semicolon with null */
            inform->cmd_buffer_type = CMD_CHAIN;
            *adr = i;
            return 1;
        }
        i++;
    }

    *adr = i;
    return 0;
}

/**
 * the_check_chain - checks if we should continue chaining based on the last status
 * @inform: the parameter struct
 * @buffer: the character buffer
 * @adr: address of the current position in buffer
 * @index: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void the_check_chain(inform_t *inform, char *buffer, size_t *adr, size_t index, size_t length)
{
    size_t i = *adr;

    while (buffer[i] != '\0') {
        if (inform->cmd_buffer_type == CMD_AND) {
            if (inform->status) {
                buffer[index] = 0;
                i = length;
                *adr = i;
                return;
            }
        }

        if (inform->cmd_buffer_type == CMD_OR) {
            if (!inform->status) {
                buffer[index] = 0;
                i = length;
                *adr = i;
                return;
            }
        }

        i++;
    }

    *adr = i;
}

/**
 * replacealias - Replaces an alias in the tokenized string.
 * @inform: The parameter struct.
 *
 * Return: 1 if the alias is replaced, 0 otherwise.
 */
int replacealias(inform_t *inform)
{
    list_t *node;
    char *ps;
    int replaced = 0;

    node = find_node_starts_with(inform->alias, inform->arguments[0], '=');
    if (node)
    {
        free(inform->arguments[0]);
        ps = _strchr(node->str, '=');
        if (ps)
        {
            ps = _strdup(ps + 1);
            if (ps)
            {
                inform->arguments[0] = ps;
                replaced = 1;
            }
        }
    }

    return replaced;
}

/**
 * replacevariables - Replaces variables in the tokenized string.
 * @inform: The parameter struct.
 *
 * Return: 1 if variables are replaced, 0 otherwise.
 */
int replacevariables(inform_t *inform)
{
    list_t *node;
    int index, replaced = 0;

    for (index = 0; inform->arguments[index]; index++)
    {
        if (inform->arguments[index][0] == '$' && inform->arguments[index][1])
        {
            if (!_strcmp(inform->arguments[index], "$?"))
            {
                replace_string(&(inform->arguments[index]), _strdup(convert_number_to_string(inform->status, 10, 0)));
                replaced = 1;
            }
            else if (!_strcmp(inform->arguments[index], "$$"))
            {
                replace_string(&(inform->arguments[index]), _strdup(convert_number_to_string(getpid(), 10, 0)));
                replaced = 1;
            }
            else
            {
                node = find_node_starts_with(inform->env, &inform->arguments[index][1], '=');
                if (node)
                {
                    replace_string(&(inform->arguments[index]), _strdup(_strchr(node->str, '=') + 1));
                    replaced = 1;
                }
                else
                {
                    replace_string(&inform->arguments[index], _strdup(""));
                    replaced = 1;
                }
            }
        }
    }

    return replaced;
}
/**
 * replace_string - Replaces a string with a new string.
 * @oldString: Pointer to the address of the old string.
 * @newString: Pointer to the new string.
 *
 * Returns: 1 if the replacement is successful, 0 otherwise.
 */

int replace_string(char **oldString, char *newString)
{
    free(*oldString); /* Free the memory occupied by the old string. */
    *oldString = newString; /* Assign the new string to the address of the old string. */
    
    return 1; /* Return 1 to indicate successful replacement.*/
}
