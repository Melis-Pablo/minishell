/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:28:46 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/09 16:40:58 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
get_var_name():	Get the name of the variable

Parameters:		char *start - the start of the variable
				char *end - the end of the variable

Return:			char * - the name of the variable

How it works:
	1. Calculate the length of the variable name
	2. Allocate memory for the variable name
	3. Copy the variable name to the new memory
	4. Return the variable name
*/
char	*get_var_name(char *start, char *end)
{
	size_t	var_name_len;
	char	*var_name;

	var_name_len = end - start - 1;
	var_name = (char *)malloc(var_name_len + 1);
	if (!var_name)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(var_name, start + 1, var_name_len);
	var_name[var_name_len] = '\0';
	return (var_name);
}

/*
var_to_value():	Replaces the variable in the word with the value

Parameters:		char *word - the word to replace the variable in
				char *start - the start of the variable
				char *end - the end of the variable
				char *var_value - the value to replace the variable with

Return:			char * - the new word

How it works:
	1. Allocate memory for the new word
	2. Copy the word up to the start of the variable
	3. Add the value to the new word
	4. Add the rest of the word to the new word
	5. Return the new word
*/
char	*var_to_value(char *word, char *start, char *end, char *var_value)
{
	size_t	new_word_len;
	char	*new_word;

	new_word_len = ft_strlen(word) - (end - start - 1) + ft_strlen(var_value);
	new_word = (char *)malloc(new_word_len + 1);
	if (!new_word)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strncpy(new_word, word, start - word);
	new_word[start - word] = '\0';
	ft_strcat(new_word, var_value);
	ft_strcat(new_word, end);
	return (new_word);
}

/*
ft_expand_exit_status():	Expands the exit status variable in the word

Parameters:					char *word - the word to expand
							char *start - the start of the variable
							char *end - the end of the variable

Return:						char * - the new word

How it works:
	1. Allocate memory for the variable value
	2. Convert the exit status to a string
	3. Replace the variable with the value
	4. Free the variable value
	5. Free the old word
	6. Return the new word
*/
char	*expand_exit_status(char *word, char *start, char *end)
{
	char	*var_value;
	char	*new_word;

	var_value = (char *)malloc(12);
	if (!var_value)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_itoa(g_signal_status, var_value);
	new_word = var_to_value(word, start, end + 1, var_value);
	free(var_value);
	free(word);
	return (new_word);
}

/*
expand_env_variables():	Expands environment variables in the word

Parameters:				char *word - the word to expand

Return:					char * - the new word

How it works:
	1. Find the start of the variable
	2. If no variable is found, return the word
	3. Find the end of the variable
	4. If the variable is the exit status, expand it
	5. Get the name of the variable
	6. Get the value of the variable
	7. Replace the variable with the value
	8. Free the variable name
	9. Free the old word
	10. Recursively call the function with the new word
*/
char	*expand_env_variables(char *word)
{
	char	*start;
	char	*end;
	char	*var_name;
	char	*var_value;
	char	*new_word;

	start = strchr(word, '$');
	if (!start)
		return (word);
	end = start + 1;
	if (*end == '?')
		return (expand_exit_status(word, start, end));
	while (*end && ((*end == '_') || isalnum(*end)))
		end++;
	var_name = get_var_name(start, end);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	new_word = var_to_value(word, start, end, var_value);
	free(var_name);
	free(word);
	return (expand_env_variables(new_word));
}
