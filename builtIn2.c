#include "shell.h"

/**
 * add_env_key - Create a new environment variable
 * @vars: Shell variables
 *
 * Creates a new environment variable and adds it to the environment.
 */
void add_env_key(vars_t *vars)
{
unsigned int i;
char **newenv;

for (i = 0; vars->env[i] != NULL; i++)
;
newenv = malloc(sizeof(char *) * (i + 2));
if (newenv == NULL)
{
print_error(vars, NULL);
vars->status = 127;
shell_exit(vars);
}
for (i = 0; vars->env[i] != NULL; i++)
newenv[i] = vars->env[i];
newenv[i] = add_env_value(vars->av[1], vars->av[2]);
if (newenv[i] == NULL)
{
print_error(vars, NULL);
free(vars->buffer);
free(vars->commands);
free(vars->av);
free_environment(vars->env);
free(newenv);
exit(127);
}
newenv[i + 1] = NULL;
free(vars->env);
vars->env = newenv;
}

/**
 * find_env_key - Find an environment variable
 * @env: Array of environment variables
 * @key: Environment variable to find
 *
 * Returns: Pointer to the address of the environment variable
 */
char **find_env_key(char **env, char *key)
{
unsigned int i, j, len;

len = _strlen(key);
for (i = 0; env[i] != NULL; i++)
{
for (j = 0; j < len; j++)
if (key[j] != env[i][j])
break;
if (j == len && env[i][j] == '=')
return (&env[i]);
}
return (NULL);
}

/**
 * add_env_value - Create a new environment variable string
 * @key: Variable name
 * @value: Variable value
 *
 * Returns: Pointer to the new string
 */
char *add_env_value(char *key, char *value)
{
unsigned int len1, len2, i, j;
char *new;

len1 = _strlen(key);
len2 = _strlen(value);
new = malloc(sizeof(char) * (len1 + len2 + 2));
if (new == NULL)
return (NULL);
for (i = 0; key[i] != '\0'; i++)
new[i] = key[i];
new[i] = '=';
for (j = 0; value[j] != '\0'; j++)
new[i + 1 + j] = value[j];
new[i + 1 + j] = '\0';
return (new);
}

/**
 * _atoi - Convert a string into an integer
 * @str: String to convert
 *
 * Returns: The integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
unsigned int i, digits;
int num = 0, num_test;

num_test = INT_MAX;
for (digits = 0; num_test != 0; digits++)
num_test /= 10;
for (i = 0; str[i] != '\0' && i < digits; i++)
{
num *= 10;
if (str[i] < '0' || str[i] > '9')
return (-1);
if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
return (-1);
num += str[i] - '0';
if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
return (-1);
}
if (i > digits)
return (-1);
return (num);
}
