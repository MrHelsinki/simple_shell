/*  #include "shell.h"

int main(void)
{
    inform_t inform = INFO_INIT;
    ssize_t input_size;
    pid_t pid;
     int status;
    char **command_args;

    /* Initialize shell environment and read history*/
   /* initialize_shell_inform(&inform);
    readHistoryFromFile(&inform);

    /* Main shell loop*/
    while (1)
    {
        /* Display prompt and get user input*/
        _puts("$ ");
        input_size = get_input(&inform);

        if (input_size == -1)
            break; /* Exit the shell on EOF*/

        if (input_size > 1)
        {
            /*Process the command buffer*/
            remove_comments_from_string(inform.commandBuffer);
            if (replacealias(&inform))
                continue;

            if (replacevariables(&inform))
                continue;

            /* Add the command to history*/
            buildHistoryList(&inform, inform.commandBuffer, inform.line_count);

            /* Execute the command*/
pid = fork();

if (pid == -1)
{
    perror("fork");
}
else if (pid == 0) /* Child process*/
{
    /* Convert the command string to an array of strings*/
    command_args = strttok(inform.commandBuffer, " ");

    if (command_args != NULL)
    {
        /* Try to execute the command*/
        if (execve(command_args[0], command_args, inform.environment) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }

    /* Cleanup in the child process*/
    free_shell_info(&inform, 0);
    free(command_args);

    exit(EXIT_SUCCESS);
}
else /* Parent process*/
{
    /*Wait for the child process to complete*/
    waitpid(pid, &status, 0);

    /* Update the status in the inform structure*/
    inform.status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
            free(inform.commandBuffer);
         //   inform.commandBuffer = NULL;
        }
    }

    /* Write history to file before exiting*/
   // write_the_history(&inform);

    /*Free allocated memory*/
   // free_shell_info(&inform, 1);

    return 0;
}
*/
