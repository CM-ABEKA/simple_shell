#include "shell.h"

/**
 * execute_command - Executes a command with the provided arguments
 * @command: Full path to the command
 * @vars: Pointer to struct of variables
 *
 * Returns: 0 on success, 1 on failure
 */
int execute_command(char *command, vars_t *vars)
{
pid_t child_pid;

if (access(command, X_OK) == 0)
{
child_pid = fork();
if (child_pid == -1)
print_error(vars, NULL);

if (child_pid == 0)
{
if (execve(command, vars->av, vars->env) == -1)
print_error(vars, NULL);
}
else
{
wait(&vars->status);
if (WIFEXITED(vars->status))
vars->status = WEXITSTATUS(vars->status);
else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
vars->status = 130;
return (0);
}
vars->status = 127;
return (1);
}
else
{
print_error(vars, ": Permission denied\n");
vars->status = 126;
}
return (0);
}

/**
 * find_env_path - Finds the PATH variable in the environment
 * @env: Array of environment variables
 *
 * Returns: Pointer to the PATH variable, or NULL on failure
 */
char *find_env_path(char **env)
{
char *path = "PATH=";
unsigned int i, j;

for (i = 0; env[i] != NULL; i++)
{
for (j = 0; j < 5; j++)
{
if (path[j] != env[i][j])
break;
}
if (j == 5)
break;
}
return (env[i]);
}

/**
 * search_path - Search for the command in the directories specified in PATH
 * @vars: Pointer to struct of variables
 *
 * Returns: void
 */
void search_path(vars_t *vars)
{
char *path, *path_dup = NULL, *check = NULL;
unsigned int i = 0, r = 0;
char **path_tokens;
struct stat buf;

if (check_cmd_in_cwd(vars->av[0]))
r = execute_cmd_in_cwd(vars);
else
{
path = find_env_path(vars->env);
if (path != NULL)
{
path_dup = _strdup(path + 5);
path_tokens = tokenize(path_dup, ":");
for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
{
check = _strcat(path_tokens[i], vars->av[0]);
if (stat(check, &buf) == 0)
{
r = execute_command(check, vars);
free(check);
break;
}
}
free(path_dup);
if (path_tokens == NULL)
{
vars->status = 127;
shell_exit(vars);
}
}
if (path == NULL || path_tokens[i] == NULL)
{
print_error(vars, ": not found\n");
vars->status = 127;
}
free(path_tokens);
}
if (r == 1)
shell_exit(vars);
}

/**
 * execute_cmd_in_cwd - Execute the command in the current working directory
 * @vars: Pointer to struct of variables
 *
 * Returns: 0 on success, 1 on failure
 */
int execute_cmd_in_cwd(vars_t *vars)
{
pid_t child_pid;
struct stat buf;

if (stat(vars->av[0], &buf) == 0)
{
if (access(vars->av[0], X_OK) == 0)
{
child_pid = fork();
if (child_pid == -1)
print_error(vars, NULL);

if (child_pid == 0)
{
if (execve(vars->av[0], vars->av, vars->env) == -1)
print_error(vars, NULL);
}
else
{
wait(&vars->status);
if (WIFEXITED(vars->status))
vars->status = WEXITSTATUS(vars->status);
else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
vars->status = 130;
return (0);
}
vars->status = 127;
return (1);
}
else
{
print_error(vars, ": Permission denied\n");
vars->status = 126;
}
return (0);
}
print_error(vars, ": not found\n");
vars->status = 127;
return (0);
}

/**
 * check_command_in_current_directory - Checks if the command is in the current directory
 * @str: Command
 *
 * Returns: 1 on success, 0 on failure
 */
int check_cmd_in_cwd(char *str)
{
unsigned int i;

for (i = 0; str[i]; i++)
{
if (str[i] == '/')
return (1);
}
return (0);
}

