#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @inform: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: number of bytes read
 */
ssize_t buffer_input(inform_t *inform, char **buffer, size_t *length)
{
    ssize_t bytesRead = 0;
    size_t bufferLength = 0;

    if (!*length) /* If there is nothing left in the buffer, fill it */
    {
        /*bfree((void **)inform->cmd_buf);*/
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, signal_Handler);
#if USE_GETLINE
        bytesRead = getline(buffer, &bufferLength, stdin);
#else
        bytesRead = getline(buffer, &bufferLength, stdin);
#endif
        if (bytesRead > 0)
        {
            if ((*buffer)[bytesRead - 1] == '\n')
            {
                (*buffer)[bytesRead - 1] = '\0'; /* Remove trailing newline */
                bytesRead--;
            }
            inform->linecount_flag = 1;
            remove_comments_from_string(*buffer);
            buildHistoryList(inform, *buffer, inform->historyCount++);
            /* Check if this is a command chain */
            if (_strchr(*buffer, ';'))
            {
                *length = bytesRead;
                inform->commandBuffer = *buffer;
            }
        }
    }
    return bytesRead;
}
/**
 * get_input - gets a line without the newline character
 * @inform: parameter struct
 *
 * Return: number of bytes read
 */
ssize_t get_input(inform_t *inform)
{
    static char *buffer; /* The buffer for command chains separated by ';' */
    static size_t bufferIndex, j, bufferLength;
    ssize_t bytesRead = 0;
    char **argBuffer = &(inform->argument), *p;

    _putchar(BUF_FLUSH);

    while (1)
    {
         bytesRead = buffer_input(inform, &buffer, &bufferLength);
       
        if (bytesRead == -1) /* EOF */
            return -1;

        if (bufferLength) /* There are commands left in the chain buffer */
        {
            j = bufferIndex; /* Initialize a new iterator to the current buffer position */
            p = buffer + bufferIndex; /* Get a pointer for return */

            the_check_chain(inform, buffer, &j, bufferIndex, bufferLength);
            while (j < bufferLength) /* Iterate to find a semicolon or the end */
            {
                if (is_chain_char(inform, buffer, &j))
                    break;
                j++;
            }

            bufferIndex = j + 1; /* Increment past the nulled semicolon */
            if (bufferIndex >= bufferLength) /* Reached the end of the buffer? */
            {
                bufferIndex = bufferLength = 0; /* Reset the position and length */
                inform->cmd_buffer_type = CMD_NORM;
            }

            *argBuffer = p; /* Pass back a pointer to the current command position */
            return _strlen(p); /* Return the length of the current command */
        }
        else
        {
            *argBuffer = buffer; /* Not a command chain, pass back the buffer from _getline() */
            return bytesRead; /* Return the length of the buffer from _getline() */
        }
    }
}

/**
 * read_Buffer - Reads a buffer from the specified file descriptor.
 * @inform: Pointer to the parameter struct.
 * @buffer: Buffer to store the data.
 * @size: Pointer to the size of the buffer.
 *
 * Return: The number of bytes read, or 0 if the buffer is already filled.
 */
ssize_t read_Buffer(inform_t *inform, char *buffer, size_t *size)
{
    ssize_t bytesRead = 0;

    if (*size)
        return 0;

    bytesRead = read(inform->readfd, buffer, READ_BUF_SIZE);
    if (bytesRead >= 0)
        *size = bytesRead;
    return bytesRead;
}

/**
 * get_the_Line - Gets the next line of input from STDIN.
 * @inform: Pointer to the parameter struct.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated buffer if not NULL.
 *
 * Return: The number of bytes read, or -1 on failure.
 */
int get_the_Line(inform_t *inform, char **ptr, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t currentIndex, bufferSize;
    size_t endIndex;
    ssize_t bytesRead = 0, totalBytesRead = 0;
    char *inputPtr = NULL, *newInputPtr = NULL, *newlinePtr;

    inputPtr = *ptr;
    if (inputPtr && length)
        totalBytesRead = *length;

    while (1)
    {
        if (currentIndex == bufferSize)
            currentIndex = bufferSize = 0;

        bytesRead = read_Buffer(inform, buffer, &bufferSize);
        if (bytesRead == -1 || (bytesRead == 0 && bufferSize == 0))
            return -1;

        newlinePtr = _strchr(buffer + currentIndex, '\n');
        endIndex = newlinePtr ? 1 + (unsigned int)(newlinePtr - buffer) : bufferSize;
        newInputPtr = my_realloc(inputPtr, totalBytesRead, totalBytesRead ? totalBytesRead + endIndex : endIndex + 1);
        if (!newInputPtr) /* MALLOC FAILURE! */
            return inputPtr ? (free(inputPtr), -1) : -1;

        if (totalBytesRead)
            _strncat(newInputPtr, buffer + currentIndex, endIndex - currentIndex);
        else
            _strncpy(newInputPtr, buffer + currentIndex, endIndex - currentIndex + 1);

        totalBytesRead += endIndex - currentIndex;
        currentIndex = endIndex;
        inputPtr = newInputPtr;

        if (newlinePtr)
            break;
    }

    if (length)
        *length = totalBytesRead;
    *ptr = inputPtr;
    return totalBytesRead;
}

/**
 * signal_Handler - Signal handler for SIGINT (Ctrl+C).
 * @signalNum: The signal number.
 *
 * Return: void
 */
void signal_Handler(__attribute__((unused))int signalNum)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
