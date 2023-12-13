#include "shell.h"

/**
 * _eputs - it prints an input string
 * @str: this is  string to be printed
 * Return: automatically return  Nothing
 */
void _eputs(char *str)
{
    if (!str)
        return;

    for (; *str != '\0'; str++)
        _eputchar(*str);
}

/**
 * _eputchar - it is writes the character to stderr
 * @ch: This is character to print
 *
 * Return: return On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char ch)
{
    static int i;
    static char buff[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buff, i);
        i = 0;
    }
    if (ch != BUF_FLUSH)
        buff[i++] = ch;
    return 1;
}

/**
 * _putfd - it will write the character to given file descriptor
 * @ch: This is  character to print
 * @file_des: This is  file descriptor to write to
 * Return: returns  On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char ch, int file_des)
{
    static int i;
    static char buff[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(file_des, buff, i);
        i = 0;
    }
    if (ch != BUF_FLUSH)
        buff[i++] = ch;
    return 1;
}

/**
 * _putsfd - it prints an input string
 * @str: this is the string to be printed
 * @file_des: this is  file descriptor to write to
 * Return: the number of characters put
 */
int _putsfd(char *str, int file_des)
{
    int count = 0;

    if (!str)
        return 0;

    for (; *str != '\0'; str++)
        count += _putfd(*str, file_des);

    return count;
}

/**
 * str_integer - Converts a string to an integer.
 * @str: The string to be converted.
 * Return: The converted number if there are numbers in the string,
 *         otherwise 0.
 *         Returns -1 on error.
 */
int str_integer(char *str)
{
    int index = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;  /* Skipping the plus sign to handle positive numbers correctly */
    while (str[index] != '\0')
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            result = result * 10 + (str[index] - '0');  /* Shifting digits and adding the current digit */
            if (result > INT_MAX)
                return -1;  /* Returning -1 if the result exceeds INT_MAX */
        }
        else
        {
            return -1;  /* Returning -1 if a non-digit character is encountered */
        }
        index++;
    }
    return result;
}
