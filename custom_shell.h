#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

#define MAX_PATH_LENGTH 4096

/**
 * struct ShellState - Represents the current state of the
 * custom shell.
 * @line_number: Current line in the script or input.
 * @exit_status: The exit status of last excecuted command.
 * @is_active: Indicates whether Read-Eval-Print Loop (REPL)
 * is active.
 * @path_directories: Array of strings representing directories
 * in the PATH variable.
 * @environment_variables: Array of strings representing
 * environmental variables.
 * @builtin_command: Function pointer to a built-in command (if any).
 * @excecutable_command_path: Path to excecutable file to
 * invoke (if any).
 * @command_arguments: Strings containing arguments parsed
 * from the last input.
 * Description: This struct defines core parameters for the
 * shell's interpreter.
*/
typedef struct ShellState {
    int line_number;
    int exit_status;
    int is_active;
    char **path_directories;
    char **environment_variables;
    void (*builtin_command)(struct ShellState *);
    char *executable_command_path;
    char **command_arguments;
} ShellState_t;

/**
 * struct BuiltInCommand - Contains information to build a
 * table of built-in commands.
 * @name: Name of the built-in command.
 * @excecute: Function pointer to the function that excecutes
 * the command.
 * 
 * Description: This holds necessary information to construct
 * a table of built-in commands specifying its name and function responsible for its execution.
*/
typedef struct BuiltInCommand {
    char *name;
    void (*execute)(ShellState_t *shell);
} BuiltInCommand_t;


void run_shell(ShellState_t *shell);
void execute_script(ShellState_t *shell);

void initialize_shell(ShellState_t **shell, char **envp);
void parse_input_line(ShellState_t *shell, char *input_line);
void release_shell(ShellState_t *shell);
void free_string_array(char **array);

char *take_input();
int contains_only_spaces(char *string);
int count_occurrences(char *string, char *delimiter);
char **split_string_by_delimiter(char *string_to_split, char *delimiter);

void (*find_builtin_command(char *command))(ShellState_t *);
void clear_shell_screen(ShellState_t *self);
void exit_shell(ShellState_t *self);
void print_environment_variables(ShellState_t *self);
char *get_environment_variable(char **envp, char *key);

char *find_executable_path(ShellState_t *self);
char *compose_test_path(char *directory_path, char *command);
void create_new_child_process(ShellState_t *shell);

void handle_error(ShellState_t *shell, int error_code);
/* int compare_checks(int chars_read, char *line_ptr); */

#endif /* SHELL_H */
