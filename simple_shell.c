#include "custom_shell.h"

/**
 * initialize_shell - Allocates memory for the shell and sets
 * initial values.
 * @shell: double pointer to the custom shell.
 * @envp: Environment variables passed from the main function.
 *
 * Return: Success status on creation.
 */
void initialize_shell(ShellState_t **shell, char **envp)
{
    *shell = malloc(sizeof(ShellState_t));
    if (*shell == NULL)
        return;

    (*shell)->line_number = 0;
    (*shell)->exit_status = 0;
    (*shell)->is_active = TRUE;
    (*shell)->environment_variables = envp;
    (*shell)->path_directories = split_string_by_delimiter(getenv("PATH"), ":");
    (*shell)->executable_command_path = NULL;
    (*shell)->builtin_command = NULL;
}

/**
 * parse_input_line - Parse and interprete a command line
 * taken from a script or the REPL.
 * @shell: A pointer to the custom shell's state.
 * @input_line: The command line input to be parsed.
 *
 * Description:
 * This function is responsible for parsing and interpreting
 * a command line provided within the script or during the
 * Read-Eval-Print Loop (REPL). It analyzes the input line,
 * detects whether the command is a built-in or an external
 * executable, and executes the appropriate action accordingly.
 * This however does not support advanced features such as command piping.
 */
void parse_input_line(ShellState_t *shell, char *input_line)
{
    shell->line_number++;
    shell->command_arguments = split_string_by_delimiter(input_line, " ");

    shell->builtin_command = find_builtin_command(shell->command_arguments[0]);

    shell->executable_command_path = find_executable_path(shell);

    if (shell->builtin_command != NULL)
        shell->builtin_command(shell);
    else if (shell->executable_command_path != NULL)
        create_new_child_process(shell);
    else
        handle_error(shell, 2);

    free_string_array(shell->command_arguments);
    free(shell->executable_command_path);
}

/**
 * release_shell - Deallocates memory used by the custom
 * shell and its associated properties.
 * @shell: Double pointer to the custom shell's state.
 * Description: This function is responsible for freeing
 * the memory allocated for the custom shell's state and its related properties.
 * It ensures that no memory leaks occur. It's called when shell's execution is complete
 * or when cleaning up resources before exiting.
 */
void release_shell(ShellState_t *shell)
{
    free_string_array(shell->path_directories);
    free(shell);
}

/**
 * free_string_array - deallocate memory allocated through split_string_by_delimiter function
 * @array: the array to be deallocated.
 */
void free_string_array(char **array)
{
    int index;

    for (index = 0; array[index]; index++)
        free(array[index]);

    free(array);
}
/**
 * find_builtin_command - Find a built-in command based on its name.
 * @command_name: The name of the command to find.
 *
 * Return: Function pointer to the corresponding command's execution function.
 */
void (*find_builtin_command(char *command_name))(ShellState_t *)
{
    int index;
    BuiltInCommand_t builtins[] = {
        {"exit", exit_shell},
        {"quit", exit_shell},
        {"env", print_environment_variables},
        {NULL, NULL}};

    for (index = 0; builtins[index].name; index++)
    {
        if (strcmp(command_name, builtins[index].name) == 0)
            return (builtins[index].execute);
    }
    return (NULL);
}
