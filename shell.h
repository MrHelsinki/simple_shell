#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define  HISTORY_MAX	4096

extern char **environment;


/**
 * struct liststr - this is singly linked list
 * @number: the  number is a field
 * @str: this is a  string
 * @next: this points to the next node
 */
typedef struct liststr
{
	int number;
	char *str;
	struct liststr *next;
} list_t;
/**
 * struct passinginform - Contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct.
 * @argument: A string generated from `getline` containing arguments.
 * @arguments: An array of strings generated from `argument`.
 * @path: A string path for the current command.
 * @argumentCount: The count of arguments.
 * @line_count: The line count.
 * @error_num: The error code for `exit()`.
 * @linecount_flag: If on, count this line of input.
 * @file_name: The program filename.
 * @env: Linked list local copy of `environ`.
 * @history: The history node.
 * @alias: The alias node.
 * @environment: Custom modified copy of `environ` from linked list `env`.
 * @env_changed: On if `environ` was changed.
 * @status: The return status of the last executed command.
 * @commandBuffer: Address of pointer to command buffer, on if chaining.
 * @cmd_buffer_type: Command type (`CMD_type`), `||`, `&&`, or `;`.
 * @readfd: The file descriptor from which to read line input.
 * @historyCount: The history line number count.
 */
typedef struct passinginform
{
    char *argument;
    char **arguments;
    char *path;
    int argumentCount;
    unsigned int line_count;
    int file_des;
    int error_num;
    int linecount_flag;
    char *file_name;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environment;
    int env_changed;
    int status;

    char *commandBuffer; 
    int cmd_buffer_type;
    int readfd;
    int historyCount;
} inform_t;

#define INFO_INIT \
{ \
    NULL,       /* argument */ \
    NULL,       /* arguments */ \
    NULL,       /* path */ \
    0,          /* argumentCount */ \
    0,          /* line_count */ \
    0,          /* file_des */ \
    0,          /* error_num */ \
    0,          /* linecount_flag */\
    NULL,       /* file_name */ \
    NULL,       /* env */ \
    NULL,       /* history */ \
    NULL,       /* alias */ \
    NULL,       /* environment */ \
    0,          /* env_changed */ \
    0,          /* status */ \
    NULL,       /* commandBuffer */ \
    0,          /* cmd_buffer_type */ \
    0,          /* readfd */ \
    0           /* historyCount */ \
}


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inform_t *);
} builtin_table;


int checkInteractiveMode(inform_t *infoPtr);
int checkDelimiter(char ch, char *delimStr);
int isAlphabetic(int ch);
int convertStringToInteger(char *str);
int exit_shell(inform_t *inform);
int change_Directory(inform_t *inform);
int custom_help(inform_t *inform);
int display_history(inform_t *inform);
int remove_alias(inform_t *inform, char *alias);
int setAlias(inform_t *inform, char *str);

int printAlias(list_t *node);
int myAlias(inform_t *inform);
int printEnvironment(inform_t *inform);
char *_getenv(inform_t *inform, const char *name);
int setEnvironment(inform_t *inform);
int removeEnvironmentVariable(inform_t *inform);
int populateEnvironmentList(inform_t *inform);
void _eputs(char *str);
int _eputchar(char ch);
int _putfd(char ch, int file_des);
int _putsfd(char *str, int file_des);
int str_integer(char *str);
void print_error_message(inform_t *inform, char *error_str);
int print_decimal_number(int n, int file_des);
char *convert_number_to_string(long int n, int b, int flags);
void remove_comments_from_string(char *buffer);
char *_strncpy(char *str, const char *src, int n);
char *_strncat(char *str, const char *src, int n);
char *_strchr(const char *str, char ch);
ssize_t buffer_input(inform_t *inform, char **buffer, size_t *length);
ssize_t get_input(inform_t *inform);
ssize_t read_Buffer(inform_t *inform, char *buffer, size_t *size);

int get_the_Line(inform_t *inform, char **ptr, size_t *length);
void signal_Handler(__attribute__((unused))int signalNum);
char **get_environment(inform_t *inform);
int _unsetenv(inform_t *inform, char *var);
int _setenv(inform_t *inform, char *var, char *value);
void initialize_shell_inform(inform_t *inform);

void set_shell_inform(inform_t *inform, char **arguments);
void free_shell_info(inform_t *inform, int freeAll);
char *gethistory_file(inform_t *inform);
int write_the_history(inform_t *inform);
int readHistoryFromFile(inform_t *inform);
int buildHistoryList(inform_t *inform, char *buffer, int line_count);
int renumberHistory(inform_t *inform);
void freeList(list_t **headPtr);
list_t *add_newnode(list_t **head, const char *str, int num);
list_t *addnode_tothe_end(list_t **head, const char *str, int num);
size_t print_liststr(const list_t *head);
int delete_nodeindex(list_t **head, unsigned int index);
size_t get_list_length(const list_t *head);
char **convert_list_to_strings(list_t *head);
size_t print_linked_list(const list_t *head);
list_t *find_node_starts_with(list_t *head, char *prefix, char c);
ssize_t get_nodeindex(list_t *head, list_t *node);
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *it_starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char ch);
int bfree(void **ptr, int count);
int isExecutableCmd(inform_t *inform, char *path);
char *duplicateChars(const char *pathstring, int start, int stop);
char *findCmdPath(inform_t *inform, char *pathstring, char *command);
char *my_memset(char *mem, char val, unsigned int size);
void free_s(char **str_arr);
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int is_chain_char(inform_t *inform, char *buffer, size_t *adr);
void the_check_chain(inform_t *inform, char *buffer,
size_t *adr, size_t index, size_t length);
int replacealias(inform_t *inform);
int replacevariables(inform_t *inform);
int replace_string(char **oldString, char *newString);
char **strttok(char *str, char *delimiter);
char **strttok2(char *str, char delimiter);
int shellLoop(inform_t *inform, char **args);
int findBuiltinCommand(inform_t *inform);
void searchAndExecuteCommand(inform_t *inform);
void executeCommand(inform_t *inform);


#endif
