#include "custom_shell.h"

/**
 * find_executable_path - Attempts to find the executable
 * path to argv[0].
 * @shell: Pointer to the ShellState.
 * Return: Pointer to the path if found, NULL if not found.
 */
char *find_executable_path(ShellState_t *shell)
{
struct stat file_info;
char *command_path;
char *test_path;
int i = 0;

command_path = malloc(sizeof(char) * 255);
snprintf(command_path, 255, "%s", shell->command_arguments[0]);

while (shell->path_directories[i])
{
if (stat(command_path, &file_info) == 0)
return (command_path);

test_path = compose_test_path(
shell->path_directories[i++],
shell->command_arguments[0]
);
snprintf(command_path, 255, "%s", test_path);
free(test_path);
}
free(command_path);

return (NULL);
}

/**
 * compose_test_path - Concatenate command argv[0] to each
 * directory path.
 * @directory_path: Pointer to a directory in the PATH.
 * @command: The command.
 * Return: Pointer to the concatenated path or NULL on error.
 */
char *compose_test_path(char *directory_path, char *command)
{
int directory_path_len, command_len, total_path_len;
int i = 0, j = 0;
char *test_path;

directory_path_len = strlen(directory_path);
command_len = strlen(command);
total_path_len = directory_path_len + command_len;

test_path = malloc(sizeof(char) * total_path_len + 2);

while (directory_path[i])
{
test_path[i] = directory_path[i];
i++;
}
test_path[i] = '/';
i++;
while (command[j])
test_path[i++] = command[j++];

test_path[i] = '\0';

return (test_path);
}

/**
 * create_new_child_process - Forks a child process to
 * execute a command.
 * @shell: Pointer to the ShellState.
 * Return: void
 */
void create_new_child_process(ShellState_t *shell)
{
pid_t child_pid;
int status;

child_pid = fork();
if (child_pid == -1)
{
perror("Fork failed");
}
else if (child_pid > 0)
{
wait(&status);
}
else if (child_pid == 0)
{
execve(
shell->executable_command_path,
shell->command_arguments,
shell->environment_variables
);
}

if (WIFEXITED(status))
{
shell->exit_status = WEXITSTATUS(status);
}

if (child_pid != 0)
{
fflush(stdout);
fflush(stdin);
}
}

/**
 * handle_error - Display an error message based on the error code.
 * @shell: Pointer to the ShellState (includes error code).
 * @error_code: Code to invoke corresponding error.
 */
void handle_error(ShellState_t *shell, int error_code)
{
char specific_error[20];
char error_message[255];

switch (error_code)
{
case 1:
snprintf(specific_error, 20, "%s", "Permission denied\n");
break;
case 2:
snprintf(specific_error, 20, "%s", "not found\n");
break;
case 3:
snprintf(specific_error, 20, "%s", "Can't open\n");
break;
default:
snprintf(specific_error, 20, "%s", "Unknown Error\n");
break;
}

snprintf(
error_message,
255,
"%s: %d: %s: %s",
getenv("_"),
shell->line_number,
shell->command_arguments[0],
specific_error
);

fprintf(stderr, "%s", error_message);

}
