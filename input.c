#include "custom_shell.h"

/**
 * take_input - Read user input and sanitize it for processing.
 * Return: Parsed input from the user, or NULL on error.
 */
char *take_input()
{
	char *buffer;
	size_t buffer_size = 0;
	ssize_t read_result;
	char new_line[] = {'\n', '\0'};

	buffer = malloc(sizeof(char) * 255);
	read_result = getline(&buffer, &buffer_size, stdin);
	if (read_result == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[0] == '\n' && buffer[1] == '\0')
		;
	else
	{
		buffer = strtok(buffer, new_line);
		if (contains_only_spaces(buffer))
		{
			buffer[0] = '\n';
			buffer[1] = '\0';
		}
	}
	return (buffer);
}
/**
 * contains_only_spaces - Check if a string contains only spaces.
 * @string: The string to check.
 * Return: 1 if the string contains only spaces, 0 otherwise.
 */
int contains_only_spaces(char *string)
{
	int i = 0;

	while (string[i] != '\0')
	{
		if (string[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
/**
 * split_string_by_delimiter - Split a string into an array of strings.
 * @string_to_split: The string to break up.
 * @delimiter: The character where the string is split.
 * Return: A double pointer which is a list of split strings.
 */
char **split_string_by_delimiter(char *string_to_split, char *delimiter)
{
	char **result_array;
	int i = 0;
	long int length = count_occurrences(string_to_split, delimiter);
	char copy_of_string[255];
	char *save_pointer;
	char *token;

	snprintf(copy_of_string, 255, "%s", string_to_split);
	result_array = malloc(sizeof(char *) * (length + 1));
	save_pointer = copy_of_string;

	for (i = 0; i < length; i++)
	{
		token = strtok_r(save_pointer, delimiter, &save_pointer);
		result_array[i] = malloc(sizeof(char) * 255);
		snprintf(result_array[i], 255, "%s", token);
	}
	result_array[i] = NULL;

	return (result_array);
}

/**
 * count_occurrences - Count the number of occurrences
 * of a delimiter in a string.
 * @string: The string to evaluate.
 * @delimiter: The delimiter used to split the string.
 * Return: The number of occurrences.
 */
int count_occurrences(char *string, char *delimiter)
{
	int i = 0;
	int count = 1;
	int has_delimiter = TRUE;
	char delim = delimiter[0];

	if (string[i] == '\0' || string == NULL)
		return (0);

	while (string[i] != '\0')
	{
		if (string[i] == delim)
		{
			if (has_delimiter == 0)
			{
				count++;
				has_delimiter = TRUE;
			}
		}
		else
			has_delimiter = FALSE;
		i++;
	}
	return (count);
}
