#include "shell.h"
/**
 * readHistoryFromFile - reads the history from a file and updates the history list
 * @inform: the parameter struct
 *
 * This function reads the contents of a history file specified in the inform struct
 * and updates the history list accordingly. It returns the number of history entries
 * read from the file on success, or 0 otherwise.
 */
int readHistoryFromFile(inform_t *inform)
{
    int line_count = 0;
    ssize_t fileDescriptor, bytesRead;
    struct stat fileInfo;
    char *buffer = NULL, *file_name = gethistory_file(inform);
    int last, i;

    if (!file_name)
        return 0;

    fileDescriptor = open(file_name, O_RDONLY);
    free(file_name);
    if (fileDescriptor == -1)
        return 0;
    if (fstat(fileDescriptor, &fileInfo) != 0)
    {
        close(fileDescriptor);
        return 0;
    }
    if (fileInfo.st_size < 2)
    {
        close(fileDescriptor);
        return 0;
    }

    buffer = malloc(sizeof(char) * (fileInfo.st_size + 1));
    if (!buffer)
    {
        close(fileDescriptor);
        return 0;
    }

    bytesRead = read(fileDescriptor, buffer, fileInfo.st_size);
    close(fileDescriptor);
    if (bytesRead <= 0)
    {
        free(buffer);
        return 0;
    }

    buffer[bytesRead] = '\0';

    last = 0;
    
    for (i = 0; i < bytesRead; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            buildHistoryList(inform, buffer + last, line_count++);
            last = i + 1;
        }
    }

    if (last != bytesRead)
        buildHistoryList(inform, buffer + last, line_count++);

    free(buffer);

    inform->historyCount = line_count;
    while (inform->historyCount >= HISTORY_MAX)
         delete_nodeindex(&(inform->history), 0);

    renumberHistory(inform);

    return inform->historyCount;
}

/**
 * buildHistoryList - adds an entry to the history linked list
 * @inform: the parameter struct
 * @buffer: the buffer containing the history entry
 * @line_count: the line count of the history entry
 *
 * This function adds a new entry to the history linked list. If the list is empty,
 * a new list node is created and assigned to the inform struct. Otherwise, the new
 * entry is appended to the end of the existing list.
 *
 * Return: Always 0
 */
int buildHistoryList(inform_t *inform, char *buffer, int line_count)
{
    list_t *node = malloc(sizeof(list_t));
    if (!node)
        return 0;

    node->str = strdup(buffer);
    node->number = line_count;
    node->next = NULL;

    if (!inform->history)
    {
        inform->history = node;
    }
    else
    {
        list_t *last = inform->history;
        while (last->next)
            last = last->next;
        last->next = node;
    }

    return 0;
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @inform: the parameter struct
 *
 * This function renumbers the history linked list after changes have been made.
 * It assigns new line count values to each node in the list, starting from 0.
 * The function returns the updated history count value.
 */
int renumberHistory(inform_t *inform)
{
    list_t *node = inform->history;
    int line_count = 0;

    while (node)
    {
        node->number = line_count++;
        node = node->next;
    }

    inform->historyCount = line_count;
    return line_count;
}

/**
 * freeList - frees all nodes of a list
 * @headPtr: address of the pointer to the head node
 *
 * This function frees all the nodes of a linked list, starting from the head node.
 * It also frees the memory allocated for the strings stored in each node.
 * After freeing all the nodes, it sets the head pointer to NULL.
 */
void freeList(list_t **headPtr)
{
    list_t *currentNode, *nextNode;

    if (!headPtr || !*headPtr)
        return;

    currentNode = *headPtr;

    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode->str);
        free(currentNode);
        currentNode = nextNode;
    }

    *headPtr = NULL;
}
