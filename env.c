#include "shell.h"

/**
 * create_environment - Create the shell environment from the environment passed to main
 * @env: Environment passed to main
 *
 * Returns: Pointer to the new environment
 */
char **create_environment(char **env)
{
	char **new_env = NULL;
	size_t i;

	for (i = 0; env[i] != NULL; i++)
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; env[i] != NULL; i++)
		new_env[i] = _strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}

/**
 * free_environment - Free the shell's environment
 * @env: Shell's environment
 *
 * Frees the memory allocated for the shell's environment.
 */
void free_environment(char **env)
{
	unsigned int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env);
}
