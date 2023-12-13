#include "shell.h"

/**
 * checkInteractiveMode - returns true if the shell is in interactive mode
 * @infoPtr: pointer to info struct
 * Return: 1 if in interactive mode, 0 otherwise
 */
int checkInteractiveMode(inform_t *infoPtr)
{
    return (isatty(STDIN_FILENO) && infoPtr->readfd <= 2);
}

/**
 * checkDelimiter - checks if a character is a delimiter
 * @ch: the character to check
 * @delimStr: the delimiter string
 * Return: 1 if true, 0 if false
 */
int checkDelimiter(char ch, char *delimStr)
{
    int i = 0;
    while (delimStr[i] != '\0')
    {
        if (delimStr[i] == ch)
            return 1;
        i++;
    }
    return 0;
}

/**
 * isAlphabetic - checks for an alphabetic character
 * @ch: The character to check
 * Return: result , 1  if ch is alphabetic, 0 otherwise
 */
int isAlphabetic(int ch)
{
    int result = 0;

    /*Loop to handle multiple characters */
  
    do {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            result = 1;
        else
            result = 0;
    } while (0);

    return result;
}

/**
 * convertStringToInteger - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convertStringToInteger(char *str)
{
    int i = 0;
    int sign = 1;
    int flag = 0;
    int output = 0;
    unsigned int result = 0;

    while (str[i] != '\0' && flag != 2)
    {
        if (str[i] == '-')
            sign *= -1;

        if (str[i] >= '0' && str[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (str[i] - '0');
        }
        else if (flag == 1)
            flag = 2;

        i++;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return output;
}
