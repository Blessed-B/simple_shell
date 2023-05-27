#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".ss_his"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;	/* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT                                                             \
	{                                                                          \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			 0, 0, 0                                                             \
	}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

ssize_t input_buffer(info_t *info, char **buffer, size_t *length);
ssize_t fetch_inp(info_t *info);
ssize_t read_buffer(info_t *info, char *buffer, size_t *index);
int custom_getline(info_t *info, char **pointer, size_t *length);
void sigint_handler(__attribute__((unused)) int sig_num);
int _putchar(char c);
int main(int argc, char **argv);
char **split_string_into_words(char *input_string, char *delimiter);
char **split_string_into_words2(char *input_string, char delimiter);
int my_exit(info_t *info);
int _cd(info_t *info);
int cd_helper(info_t *info);
int display_history(info_t *info);
int remove_alias(info_t *info, char *str);
int _alias(info_t *info, char *str);
int display_alias(list_t *node);
int my_alias(info_t *info);
int display_env(info_t *info);
int set_env(info_t *info);
int unset_env(info_t *info);
int populate_environ_list(info_t *info);
void print_string(char *str);
int write_char(char c);
int write_char_fd(char c, int fd);
int writes_fd(char *str, int fd);
int convert_string_to_int(char *s);
void print_err(info_t *info, char *estr);
int print_decimal(int input, int fd);
char *_itoa(long int number, int base, int flags);
void com_void(char *buffer);
char *_strncpy(char *destination, char *source, int n);
char *_strncat(char *destination, char *source, int n);
char *_strchr(char *string, char character);
char **get_environment(info_t *info);
int unset_environment(info_t *info, char *variable);
int set_environment(info_t *info, char *variable, char *value);
void innit_info(info_t *info);
void set_struct_info(info_t *info, char **av);
void free_struct_info(info_t *info, int all);
char *retrieve_history_file(info_t *info);
int save_history(info_t *info);
int load_history(info_t *info);
int add_entry_to_history_list(info_t *info, char *buffer, int line_count);
int renhis(info_t *info);
int check_interactive(info_t *info);
int check_delim(char c, char *delim);
int check_alpha(int c);
int string_to_int(char *s);
list_t *add_node_to_start(list_t **head, const char *string, int number);
size_t write_linked_list_stringing(const list_t *h);
int remove_current_node(list_t **head, unsigned int index);
void free_current_list(list_t **head_pointer);
size_t linked_list_length(const list_t *head);
char **linkd_li_to_str(list_t *head);
size_t write_linked_list(const list_t *head);
list_t *find_node_with_prefix(list_t *node, char *prefix, char next_char);
ssize_t retrieve_index(list_t *head, list_t *node);
int is_chain_delimiter(info_t *info, char *buffer, size_t *position);
void chain_checker(info_t *info, char *buffer, size_t *position, size_t start_position, size_t length);
int change_alias(info_t *info);
int change_variables(info_t *info);
int change_string(char **old_string, char *new_string);
int free_pointer(void **pointer);
char *fill_memory(char *memory, char byte, unsigned int num_bytes);
void free_strings(char **strings);
void *reallocate_memory(void *pointer, unsigned int old_size, unsigned int new_size) int is_executable_command(info_t *info, char *file_path);
char *duplicate_characters(char *path_string, int start_index, int stop_index);
char *find_command_path(info_t *info, char *path_string, char *command);
int string_length(char *string);
int string_compare(char *string1, char *string2);
char *starts_with_string(const char *haystack, const char *needle);
char *concatenate_strings(char *destination, char *source);
char *_strcpy(char *destination, char *source);
char *_strdup(const char *str);
void _puts(char *string);

#endif /* SHELL_H */
