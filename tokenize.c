#include "shell.h"

/**
 * tokenize - Tokenizes a buffer using a delimiter.
 * @buffer: The buffer to tokenize.
 * @delimiter: The delimiter to split the buffer by.
 *
 * Return: A pointer to an array of pointers to the tokens.
 */
char **tokenize(char *buffer, char *delimiter)
{
char **tokens = NULL;
size_t i = 0, max_tokens = 10;

if (buffer == NULL)
return (NULL);

tokens = malloc(sizeof(char *) * max_tokens);
if (tokens == NULL)
{
perror("Fatal Error");
return (NULL);
}
while ((tokens[i] = custom_strtok(buffer, delimiter)) != NULL)
{
i++;
if (i == max_tokens)
{
tokens = _realloc(tokens, &max_tokens);
if (tokens == NULL)
{
perror("Fatal Error");
return (NULL);
}
}
buffer = NULL;
}
return (tokens);
}
