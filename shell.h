#ifndef _SHELL_H_
#define _SHELL_H_

/**
 *  MACROS
 */

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"
#define printer (c) (write(STDOUT_FILENO, c, _strlen(c)))

/** 
 * LIB USED
*/
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define END_OF_FILE -2
#define EXIT -3

/**
 * environ var
*/
extern char **environ;
char *name;
int history_counter;

/**
 * struct order_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct order_s
{
	char *dir;
	struct order_s *next;
} order_t;

/**
 * struct built_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct built_s
{
	char *name;
	int (*f)(char **argv, char **ptr);
} builtin_t;

/**
 * struct char_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct char_s.
 */
typedef struct char_s
{
	char *name;
	char *value;
	struct char_s *next;
} char_t;

char_t *aliases;

ssize_t mygetln(char **lnptr, size_t *ptr_size, FILE *fd);
void *myrealloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **mystrtok(char *ln, char *delim);
char *_locate(char *command);
order_t *mypath(char *path);
int myexecve(char **ag, char **ptr);
void myflist(order_t *head);
char *myitoa(int num);

void _get_ln(char **ln, ssize_t read);
void myvariable(char **ag, int *exect);
char *get_command(char *ln, int *exect);
int call_command(char **ag, char **ptr, int *exect);
int execute_command(char **ag, char **ptr, int *exect);
int handle_command(int *exect);
int check_command(char **ag);
void free_memory(char **ag, char **ptr);
char **myalias(char **ag);

int mystrlen(const char *s);
char *mystrcat(char *dest, const char *src);
char *mystrncat(char *dest, const char *src, size_t n);
char *mystrcpy(char *dest, const char *src);
char *mystrchr(char *s, char ch);
int mystrspn(char *s, char *accept);
int mystrcmp(char *s1, char *s2);
int mystrncmp(const char *s1, const char *s2, size_t n);

int (*_builtin(char *command))(char **ag, char **ptr);
int myexit(char **ag, char **ptr);
int myenv(char **ag, char __attribute__((__unused__)) **ptr);
int _setenv(char **ag, char __attribute__((__unused__)) **ptr);
int _unsetenv(char **ag, char __attribute__((__unused__)) **ptr);
int mycd(char **ag, char __attribute__((__unused__)) **ptr);
int _alias(char **ag, char __attribute__((__unused__)) **ptr);
int _help(char **ag, char __attribute__((__unused__)) **ptr);

char **copy_env(void);
void _free_env(void);
char **get_env(const char *env_var);

int myerror(char **ag, int error);
char *_env_error(char **ag);
char *_error(char **ag);
char *_exit_error(char **ag);
char *directory_error(char **ag);
char *mysyntax(char **ag);
char *permission_denied(char **ag);
char *command_not_found(char **ag);

char_t *add_node_list(char_t **head, char *name, char *value);
void free_alias(char_t *head);
order_t *add_list_end(order_t **head, char *dir);
void myflist(order_t *head);

void print_builtin(void);
void print_alias(void);
void print_cd(void);
void print_exit(void);
void print_help(void);
void print_env(void);
void print_setenv(void);
void print_unsetenv(void);
void print_history(void);

int run_command(char *file_path, int *exect);

#endif
