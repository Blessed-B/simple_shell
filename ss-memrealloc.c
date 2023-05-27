#include "shell.h"

/**
 * fill_memory - write constant byte to memory
 * @memory: the pointer to the memory area
 * @byte: the byte to fill *memory with
 * @num_bytes: the amount of bytes to be filled
 * Return: (memory) a pointer to the memory area memory
 */
char *fill_memory(char *memory, char byte, unsigned int num_bytes)
{
	unsigned int index;

	for (index = 0; index < num_bytes; index++)
		memory[index] = byte;
	return (memory);
}

/**
 * free_strings - frees a string of strings
 * @strings: string of strings
 */
void free_strings(char **strings)
{
	char **temp = strings;

	if (!strings)
		return;
	while (*strings)
		free(*strings++);
	free(temp);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *reallocate_memory(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *new_pointer;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(pointer), NULL);
	if (new_size == old_size)
		return (pointer);

	new_pointer = malloc(new_size);
	if (!new_pointer)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_pointer[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (new_pointer);
}
