#include "shell.h"

/**
 * char_in_string - Checks if a character matches any in a string
 * @c: Character to check
 * @str: String to check against
 *
 * Returns: 1 if there is a match, 0 if not
 */
unsigned int char_in_string(char c, const char *str)
{
unsigned int i;

for (i = 0; str[i] != '\0'; i++)
{
if (c == str[i])
return (1);
}
return (0);
}

/**
 * custom_strtok - Custom implementation of strtok
 * @str: String to tokenize
 * @delim: Delimiter to tokenize against
 *
 * Returns: Pointer to the next token or NULL
 */
char *custom_strtok(char *str, const char *delim)
{
static char *token_start;
static char *next_token;
unsigned int i;

if (str != NULL)
next_token = str;
token_start = next_token;
if (token_start == NULL)
return (NULL);
for (i = 0; next_token[i] != '\0'; i++)
{
if (!char_in_string(next_token[i], delim))
break;
}
if (next_token[i] == '\0' || next_token[i] == '#')
{
next_token = NULL;
return (NULL);
}
token_start = next_token + i;
next_token = token_start;
for (i = 0; next_token[i] != '\0'; i++)
{
if (char_in_string(next_token[i], delim))
break;
}
if (next_token[i] == '\0')
next_token = NULL;
else
{
next_token[i] = '\0';
next_token = next_token + i + 1;
if (*next_token == '\0')
next_token = NULL;
}
return (token_start);
}
