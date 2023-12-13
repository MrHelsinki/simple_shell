#include "shell.h"
/**
 * print_error_message - prints an error message
 * @inform: the parameter and return inform struct
 * @error_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error_message(inform_t *inform, char *error_str)
{
    int file_des = 0;
    
    _eputs(inform->file_name);
    _eputs(": ");
    print_decimal_number(inform->line_count, file_des);
    _eputs(": ");
    _eputs(inform->arguments[0]);
    _eputs(": ");
    _eputs(error_str);
}
/**
 * print_decimal_number - function prints a decimal (integer) number (base 10)
 * @n: the input
 * @file_des: the file descriptor to write to
 *
 * Return: number of characters printed
 */

int print_decimal_number(int n, int file_des)
{
    int count = 0;
    unsigned int absolute, current;
    int (*_putchar)(char) = _putchar;
    
    if (file_des == STDERR_FILENO)
        _putchar = _eputchar;
        
    if (n < 0) {
        absolute = -n;
        _putchar('-');
        count++;
    } else {
        absolute = n;
    }
    
    current = absolute;
    
    do {
        _putchar('0' + current % 10);
        count++;
        current /= 10;
    } while (current != 0);
    
    return count;
}

/**
 * convert_number_to_string - converter function, a clone of itoa
 * @number: number
 * @b: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number_to_string(long int number, int b, int flags)
{
    static char *char_array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long num = number;

    if (!(flags & CONVERT_UNSIGNED) && number < 0)
    {
        num = -number;
        sign = '-';
    }
    char_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = char_array[num % b];
        num /= b;
    } while (num != 0);

    if (sign)
        *--ptr = sign;
    return ptr;
}

/**
 * remove_comments_from_string - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments_from_string(char *buffer)
{
    int i;

    for (i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
        {
            buffer[i] = '\0';
            break;
        }
}
