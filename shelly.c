#include "main.h"

/**
*main - func
*Return: int
*/

int main(void)
{
	int nR, pid, exit_status;
	char *line = NULL;
	size_t size;
	char *argv[] = {NULL, NULL};

	while (1)
	{
		write(STDOUT_FILENO,"$ ", 2);
		nR = getline(&line, &size, stdin);
		if (nR >= 0)
		{
			line[nR - 1] = '\0';
			argv[0] = line;
			pid = fork();
			if (pid == 0)
				execve(line, argv, NULL);
			else if (pid > 0)
			{
				free(line);
				line = NULL;
				wait(&exit_status);
			}
			free(line);
			line = NULL;
		} else
		{
			free(line);
			break;
		}
	}
	return (1);
}
