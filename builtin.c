#include "custom_shell.h"

/**
 * exit_shell - Exits the interactive mode of the shell.
 * @shell: Pointer to the ShellState.
 * Description: Placeholder function for quitting the interactive mode.
 */
void exit_shell(ShellState_t *shell)
{
	shell->is_active = FALSE;
}

/**
 * print_environment_variables - Print list of environmental variables.
 * @shell: Pointer to the ShellState.
 * Description: Placeholder function for printing environmental variables.
 */
void print_environment_variables(ShellState_t *shell)
{
	int i = 0;

	while (shell->environment_variables[i])
	{
		printf("%s\n", shell->environment_variables[i++]);
	}
}
