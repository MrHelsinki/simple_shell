
#include "shell.h"

/**
 * my_memset - fills memory with a constant byte
 * @mem: pointer to the memory area
 * @val: the byte value to fill *mem with
 * @size: the number of bytes to be filled
 * Return: a pointer to the memory area mem
 */
char *my_memset(char *mem, char val, unsigned int size)
{
    unsigned int i;
    
    for (i = 0; i < size; i++) {
        *(mem + i) = val;
    }
    return mem;
}

/**
 * free_s - frees an array of strings
 * @str_arr: array of strings
 */
void free_s(char **str_arr)
{
    char **temp;
    
    if (str_arr == NULL) {
        return;
    }
    temp = str_arr;
    while (*str_arr != NULL) {
        free(*str_arr);
        str_arr++;
    }
    free(temp);
}

/**
 * my_realloc - reallocates a block of memory
 * @ptr: pointer to previously allocated block
 * @old_size: size of the previous block in bytes
 * @new_size: size of the new block in bytes
 *
 * Return: pointer to the old block.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;
    unsigned int i;
    unsigned int min_size;
    
    if (ptr == NULL) {
        return malloc(new_size);
    }
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    if (new_size == old_size) {
        return ptr;
    }
    new_ptr = malloc(new_size);
    
    if (new_ptr == NULL) {
        return NULL;
    }
    min_size = old_size < new_size ? old_size : new_size;
    for (i = 0; i < min_size; i++) {
        *(new_ptr + i) = *((char *)ptr + i);
    }
    free(ptr);
    return new_ptr;
}
