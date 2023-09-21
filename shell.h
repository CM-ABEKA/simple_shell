#ifndef _SHELL_H_
#define _SHELL_H_

#define PROMPT "$ "

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct variables - Variables
 * @av: Command line arguments
 * @buffer: Buffer of command
 * @env: Environment variables
 * @count: Count of commands entered
 * @argv: Arguments at the opening of the shell
 * @status: Exit status
 * @commands: Parsed commands
 */
typedef struct variables
{
    char **av;
    char *buffer;
    char **env;
    size_t count;
    char **argv;
    int status;
    char **commands;
} vars_t;

/**
 * struct builtins - Struct for the builtin functions
 * @name: Name of builtin command
 * @f: Function for corresponding builtin
 */
typedef struct builtins
{
    char *name;
    void (*f)(vars_t *);
} builtins_t;

char **create_environment(char **env);
void free_environment(char **env);

ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *custom_strtok(char *str, const char *delim);

void (*check_builtins(vars_t *vars))(vars_t *vars);
void shell_exit(vars_t *vars);
void print_environment(vars_t *vars);
void set_environment(vars_t *vars);
void unset_environment(vars_t *vars);
void add_env_key(vars_t *vars);
char **find_env_key(char **env, char *key);
char *add_env_value(char *key, char *value);
int _atoi(char *str);

void search_path(vars_t *vars);
int execute_command(char *command, vars_t *vars);
char *find_env_path(char **env);
int execute_cmd_in_cwd(vars_t *vars);
int check_cmd_in_cwd(char *str);

int read_command(vars_t *vars);
void parse_and_execute(vars_t *vars);
void display_prompt(vars_t *vars);

void print_error(vars_t *vars, char *msg);
void _puts2(char *str);
char *_uitoa(unsigned int count);


#endif /* _SHELL_H_ */
