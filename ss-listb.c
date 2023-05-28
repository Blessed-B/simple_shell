#include "shell.h"

/**
 * linked_list_length - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t linked_list_length(const list_t *head)
{
	size_t count = 0;
	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * linkd_li_to_str - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **linkd_li_to_str(list_t *head)
{
	list_t *current_node = head;
	size_t length = linked_list_length(head), index;
	char **strings;
	char *string;

	if (!head || !length)
		return (NULL);

	strings = malloc(sizeof(char *) * (length + 1));
	if (!strings)
		return (NULL);

	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		string = malloc(string_length(current_node->str) + 1);
		if (!string)
		{
			for (index = 0; index < length; index++)
				free(strings[index]);
			free(strings);
			return (NULL);
		}
		string = _strcpy(string, current_node->str);
		strings[index] = string;
	}
	strings[index] = NULL;
	return (strings);
}

/**
 * write_linked_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t write_linked_list(const list_t *head)
{
	size_t count = 0;
	while (head)
	{
		_puts(_itoa(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * find_node_with_prefix - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char next_char)
{
	char *p = NULL;
	while (node)
	{
		p = starts_with_string(node->str, prefix);
		if (p && ((next_char == -1) || (*p == next_char)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * retrieve_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t retrieve_index(list_t *head, list_t *node)
{
	size_t index = 0;
	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
