#include "shell.h"

/**
 * _puts - Writes a string to standard output
 * @str: String to write
 *
 * Return: Number of characters printed or -1 on failure
 */
ssize_t _puts(char *str)
{
ssize_t num, len;

num = _strlen(str);
len = write(STDOUT_FILENO, str, num);
if (len != num)
{
perror("Fatal Error");
return (-1);
}
return (len);
}

/**
 * _strdup - Returns a pointer to newly allocated memory containing a copy
 * @src: String to be duplicated
 *
 * Return: Pointer to the new duplicated string
 */
char *_strdup(char *src)
{
char *copy;
int length, i;

if (src == 0)
return (NULL);

for (length = 0; src[length]; length++)
;

copy = malloc((length + 1) * sizeof(char));

for (i = 0; i <= length; i++)
copy[i] = src[i];

return (copy);
}

/**
 * _strcmpr - Compares two strings
 * @str1: First string to be compared
 * @str2: Second string to be compared
 *
 * Return: 0 on success, non-zero on failure
 */
int _strcmpr(char *str1, char *str2)
{
int i;

i = 0;
while (str1[i] == str2[i])
{
if (str1[i] == '\0')
return (0);
i++;
}
return (str1[i] - str2[i]);
}

/**
 * _strcat - Concatenates two strings
 * @str1: First string
 * @str2: Second string
 *
 * Return: Pointer to the concatenated string
 */
char *_strcat(char *str1, char *str2)
{
char *newstr;
unsigned int len1, len2, newlen, i, j;

len1 = (str1 == NULL) ? 0 : _strlen(str1);
len2 = (str2 == NULL) ? 0 : _strlen(str2);
newlen = len1 + len2 + 2;
newstr = malloc(newlen * sizeof(char));
if (newstr == NULL)
return (NULL);
for (i = 0; i < len1; i++)
newstr[i] = str1[i];
newstr[i] = '/';
for (j = 0; j < len2; j++)
newstr[i + 1 + j] = str2[j];
newstr[len1 + len2 + 1] = '\0';
return (newstr);
}

/**
 * _strlen - Returns the length of a string
 * @str: String to be measured
 *
 * Return: Length of the string
 */
unsigned int _strlen(char *str)
{
unsigned int len;

len = 0;

while (str[len])
len++;

return (len);
}
