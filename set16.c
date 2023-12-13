#include "shell.h"

/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 * @count: number of pointers to free
 *
 * Return: number of pointers successfully freed.
 */
int bfree(void **ptr, int count)
{
  int freed_count = 0;
  int i;

  for (i = 0; i < count; i++)
  {
    if (ptr[i] != NULL)
    {
      free(ptr[i]); /* Free the memory pointed to by ptr[i] */
      ptr[i] = NULL; /* Set ptr[i] to NULL */
      freed_count++; /* Increment the counter*/
    }
  }

  return freed_count; /* Return the number of pointers successfully freed */
}
/**
 * isExecutableCmd - determines if a file is an executable command
 * @inform: the inform struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutableCmd(inform_t *inform, char *path)
{
    struct stat st;

    (void)inform;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * duplicateChars - duplicates characters
 * @pathstring: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicateChars(const char *pathstring, int start, int stop)
{
    int length = stop - start;
    char *buffer = (char *)malloc((length + 1) * sizeof(char));
  int k = 0;
  int i;

    if (buffer == NULL) {
        return NULL;
    }
  
    for (i = start; i < stop; i++)
    {
        if (pathstring[i] != ':')
        {
            buffer[k] = pathstring[i];
            k++;
        }
    }
    buffer[k] = '\0';
    return buffer;
}
/**
 * findCmdPath - finds this command in the PATH string
 * @inform: the inform struct
 * @pathstring: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *findCmdPath(inform_t *inform, char *pathstring, char *command)
{
    int current_pos = 0;
    char *path = NULL;
  int i;

    if (!pathstring)
        return NULL;

    if (_strlen(command) > 2 && it_starts_with(command, "./"))
    {
        if (isExecutableCmd(inform, command))
            return command;
    }

    for (i = 0; pathstring[i]; i++)
    {
        int j = i;
        while (pathstring[j] && pathstring[j] != ':')
            j++;

        path = duplicateChars(pathstring, current_pos, j);

        if (!*path)
            _strcat(path, command);
        else
        {
            _strcat(path, "/");
            _strcat(path, command);
        }

        if (isExecutableCmd(inform, path))
            return path;

        if (pathstring[j] == ':')
        {
            i = j + 1;
            current_pos = i;
        }
        else
        {
            break;
        }
    }

    return NULL;
}
