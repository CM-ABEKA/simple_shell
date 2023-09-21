#include "shell.h"

/**
 * display_prompt - Display the shell prompt.
 * @vars: Pointer to the shell variables structure.
 */
void display_prompt(vars_t *vars __attribute__((unused))) {
if (isatty(STDIN_FILENO)) {
_puts(PROMPT);
}
}

/**
 * read_command - Read a line of input from the user.
 * @vars: Pointer to the shell variables structure.
 *
 * Return:
 *   -1 on failure or end of input, 0 on success.
 */
int read_command(vars_t *vars) {
ssize_t read_bytes;
size_t bufsize = 0;

if (!vars->buffer)
return -1;

/* Display the prompt if we haven't already */
if (isatty(STDIN_FILENO)) {
_puts(PROMPT);
}

read_bytes = getline(&(vars->buffer), &bufsize, stdin);

if (read_bytes == -1 || read_bytes == 0) {
if (read_bytes == -1) {
perror("getline");
}
return -1;
}

if (vars->buffer[read_bytes - 1] == '\n') {
vars->buffer[read_bytes - 1] = '\0';
}

return 0;
}

/**
 * parse_and_execute - Parse and execute a command.
 * @vars: Pointer to the shell variables structure.
 */
void parse_and_execute(vars_t *vars) {
char **tokens = NULL;
void (*builtin_func)(vars_t *vars);

tokens = tokenize(vars->buffer, " ");
if (tokens == NULL || tokens[0] == NULL) {
return;
}

builtin_func = check_builtins(vars);
if (builtin_func != NULL) {
builtin_func(vars);
} else {

}

free(tokens);
}
