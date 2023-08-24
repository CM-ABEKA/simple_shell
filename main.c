#include "custom_shell.h"

/**
 * main - Entry point for the program.
 * @argc: Number of arguments passed to the program.
 * @argv: Array of arguments passed to the program.
 * @envp: Complete list of environmental variables.
 *
 * Return: EXIT_SUCCESS (0) or EXIT_FAILURE (1).
 */
int main(
    __attribute__ ((unused)) int argc,
    __attribute__ ((unused)) char *argv[],
    char **envp
)
{
    ShellState_t *shell = NULL;
    int exit_status = 0;
    int is_interactive = isatty(STDIN_FILENO);

    initialize_shell(&shell, envp);

    if (is_interactive)
        run_shell(shell);
    else
        execute_script(shell);

    release_shell(shell);

    return (exit_status);
}

/**
 * run_shell - Opens a Read-Evaluate-Print Loop (REPL) with the interpreter.
 * @shell: Pointer to the ShellState.
 *
 * Return: void.
 */
void run_shell(ShellState_t *shell)
{
    char *line = NULL;

    while (shell->is_active == TRUE)
    {
        printf("($) ");
        line = take_input();
        parse_input_line(shell, line);
        free(line);
        fflush(NULL);
    }
}

/**
 * execute_script - Reads and executes a script from standard input.
 * @shell: Pointer to the ShellState.
 *
 * Return: void.
 */
void execute_script(ShellState_t *shell)
{
    char *current_line = NULL;

    do {
        current_line = take_input();

        if (current_line != NULL)
            parse_input_line(shell, current_line);
        else
            shell->is_active = FALSE;

        free(current_line);
        fflush(NULL);

    } while (shell->is_active == TRUE);
}