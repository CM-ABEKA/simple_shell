#include "shell.h"

/**
 * _realloc - Reallocates a pointer to double the space
 * @ptr: Pointer to the old array
 * @size: Pointer to number of elements in the old array
 *
 * Returns: Pointer to the new array
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new_arr;
	size_t i;

	new_arr = malloc(sizeof(char *) * ((*size) + 10));
	if (new_arr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new_arr[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new_arr);
}
