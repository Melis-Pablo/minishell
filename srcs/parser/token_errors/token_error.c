/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:39:05 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 16:52:10 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	check_redir(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	if (len > 0)
	{
		if (word[0] == '>' || word[0] == '<')
			return (1);
	}
	return (0);
}

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
	if (check_redir(word))
		i = 7;
	return (i);
}
