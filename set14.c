#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string whose length to calculate
 * Return: integer length of the string
 */
int _strlen(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (str[length] != '\0')
    {
        length++;
    }

    return length;
}

/**
 * _strcmp - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative value if str1 < str2, positive
 * value if str1 > str2, 0 if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
    int i = 0;

    while (str1[i] && str2[i] && str1[i] == str2[i])
    {
        i++;
    }

    if (str1[i] == str2[i])
        return 0;
    else
        return (str1[i] < str2[i] ? -1 : 1);
}

/**
 * it_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *it_starts_with(const char *haystack, const char *needle)
{
    int i = 0;

    while (needle[i] && haystack[i] && needle[i] == haystack[i])
    {
        i++;
    }

    if (needle[i] == '\0')
        return (char *)&haystack[i];
    else
        return NULL;
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
    int dest_len = _strlen(dest);
    int i = 0;

    while (src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i++;
    }

    dest[dest_len + i] = '\0';
    return dest;
}
