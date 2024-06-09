/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:51:57 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/09 17:51:33 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
check_or:	Checks if a word contains a double special character
			like '||'

parameters:	char *word - the word to check

return:		int - 1 if the word contains the double special character
				0 otherwise

How it works:	
	1. Get the length of the word
	2. If the word is the same as the special character, return 1
	3. If the word starts or ends with the special character, return 1
	4. Return 0
*/
int	check_or(char *word)
{
	size_t	len;

	len = strlen(word);
	if (strcmp(word, "||") == 0)
		return (1);
	if (len > 0)
	{
		if (word[0] == '|' && word[1] == '|')
			return (1);
		if (word[len - 1] == '|' && word[len - 2] == '|')
			return (1);
	}
	return (0);
}

/*
word_error:	Prints an error message if a word contains an invalid character

parameters:	char *word - the word to check
			int error_code - the error code to print

return:		void

How it works:
	1. If the error code is 0, return
	2. Set the error message based on the error code
	3. Free the word
	4. Print the error message
*/
void	word_error(char *word, int error_code)
{
	char	*error_msg;

	if (error_code == 0)
		return ;
	else if (error_code == 1)
		error_msg = "Error: Invalid character detected ';'\n";
	else if (error_code == 2)
		error_msg = "Error: Invalid character detected '&&'\n";
	else if (error_code == 3)
		error_msg = "Error: Invalid character detected '||'\n";
	else if (error_code == 4)
		error_msg = "Error: Invalid character detected '()'\n";
	else if (error_code == 5)
		error_msg = "Error: Invalid character detected '*'\n";
	else if (error_code == 6)
		error_msg = "Error: Invalid character detected '\\'\n";
	free(word);
	perror(error_msg);
}

/*
check_invalid_char:	Checks if a word contains an invalid character

parameters:			char *word - the word to check

return:				int - 1 if the word contains an invalid character
						0 otherwise

How it works:	
	1. Check if the word contains a single special character
	2. Check if the word contains a double special character
	3. Check if the word contains '||'
	4. Check if the word contains '()'
	5. Check if the word contains '*'
	6. Check if the word contains '\'
	7. If any of the checks return 1, print an error message
	8. Return the result of the checks
*/
int	check_invalid_char(char *word)
{
	int	i;

	i = 0;
	if (check_semicolon(word))
		i = 1;
	if (check_and(word))
		i = 2;
	if (check_or(word))
		i = 3;
	if (check_parentheses(word))
		i = 4;
	if (check_wildcard(word))
		i = 5;
	if (check_backslash_word(word))
		i = 6;
	if (i)
		word_error(word, i);
	return (i);
}
