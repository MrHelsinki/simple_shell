#include "shell.h"


void print_error(inform_t *inform, const char *message);  
/**
 * exit_shell - Exits the shell
 * @inform: Structure containing potential arguments. Used to maintain
 * a constant function prototype.
 * Return: Exits the shell with a given exit status.
 * Returns 0 if inform.arguments[0] is not "exit".
 */
int exit_shell(inform_t *inform)
{
    int exit_status;
    int input_valid;

    do
    {
        input_valid = 1;  /* Assume input is valid */

        if (inform->arguments[1])  /* If there is an exit argument */
        {
            exit_status = str_integer(inform->arguments[1]);
            if (exit_status == -1)
            {
                inform->status = 2;
                print_error(inform, "Illegal number: ");
                _eputs(inform->arguments[1]);
                _eputchar('\n');
                input_valid = 0;  /* Invalid input, repeat the loop */
            }
            else
            {
                inform->error_num = exit_status;
            }
        }
        else
        {
            inform->error_num = -1;
        }
    } while (!input_valid);

    return -2;
}
/**
 * change_Directory - Changes the current directory of the process.
 * @inform: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: Always 0.
 */
int change_Directory(inform_t *inform)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    while (1) {
        s = getcwd(buffer, 1024);
        if (!s)
            _puts("ERROR: Failed to retrieve current working directory\n");

        if (!inform->arguments[1]) {
            dir = _getenv(inform, "HOME=");
            if (!dir)
                chdir_ret = chdir((dir = _getenv(inform, "PWD=")) ? dir : "/");
            else
                chdir_ret = chdir(dir);
        }
        else if (_strcmp(inform->arguments[1], "-") == 0) {
            if (!_getenv(inform, "OLDPWD=")) {
                _puts(s);
                _putchar('\n');
                break;
            }
            _puts(_getenv(inform, "OLDPWD="));
            _putchar('\n');
            chdir_ret = chdir((dir = _getenv(inform, "OLDPWD=")) ? dir : "/");
        }
        else {
            chdir_ret = chdir(inform->arguments[1]);
        }

        if (chdir_ret == -1) {
            print_error(inform, "Failed to change directory to ");
            _eputs(inform->arguments[1]);
            _eputchar('\n');
        }
        else {
            _setenv(inform, "OLDPWD", _getenv(inform, "PWD="));
            _setenv(inform, "PWD", getcwd(buffer, 1024));
        }

        break;
    }

    return (0);
}
/**
 * custom_help - changes the current directory of the process
 * @inform: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int custom_help(inform_t *inform)
{
    char *argument = inform->argument;
    int i;

    _puts("The help command is called. This function is not implemented yet.\n");

    for (i = 0; argument[i] != '\0'; i++)
    {
        _puts(&argument[i]);
    }

    return 0;
}

/**
 * display_history - Displays the history list, one command per line, with line numbers starting at 0.
 * @inform: Structure containing potential arguments. Used to maintain constant function prototype.
 * Return: Always 0.
 */
int display_history(inform_t *inform)
{
	print_liststr(inform->history);
	return 0;
}

/**
 * remove_alias - Removes an alias from the alias list.
 * @inform: Parameter struct.
 * @alias: The alias string to be removed.
 *
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(inform_t *inform, char *alias)
{
	char *p, c;
	int ret;

	while (1) {
		p = _strchr(alias, '=');
		if (!p)
			return 1;
		c = *p;
		*p = '\0';
		ret =  delete_nodeindex(&(inform->alias),
		 get_nodeindex(inform->alias, find_node_starts_with(inform->alias, alias, -1)));
		*p = c;
		if (ret == 0)
			break;
	}
	
	return ret;
}
