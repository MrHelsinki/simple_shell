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

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


/**
 * struct liststr - linked list for strings
 * @num: number
 * @str: string
 * @next: next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - to pass into a function,
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, 0, 0, NULL, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

extern char **environ;

/* execute.c functions */
int shell_loop(info_t *, char **);
int check_builtin(info_t *);
void cmd_path(info_t *);
void fork_exec(info_t *);

/* command.c functions */
int is_exec(info_t *, char *);
char *dup_chars(char *, int, int);
char *get_path(info_t *, char *, char *);
int chain_str(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

/* env.c functions */
char *_getenv(info_t *, const char *);
int _env(info_t *);
int env_list(info_t *);
char **get_environ(info_t *);

/* errorhandling.c */
void _eputs(char *);
int _eputchar(char);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);

/* getinfo.c functions */
void info_init(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_strchr(char *, char);

/* getline.c functions */
ssize_t input_buf(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* builtin.c functions */
int builtin_exit(info_t *);


/* str_functions.c functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strncat(char *, char *, int);

/* help_functions.c functions */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);

/* memory_control.c functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int set_free(void **);

/* support_functions.c functions */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
char **strtow(char *, char *);


/* lists_functions.c functions */
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);

#endif
