/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:12:22 by pmelis            #+#    #+#             */
/*   Updated: 2024/05/30 23:58:43 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#count_until_pipe():	counts the number of characters until a pipe character

#Parameters:			char *input	- the string to count characters in

#Return value:			int - the number of characters until a pipe character

#How it works:		
	1. Initialize count to 0
	2. Initialize in_quote to 0
	3. Initialize quote to 0
	4. Initialize i to 0
	5. While input[i] is not NULL
		1. If input[i] is a quote character
			1. If in_quote is true and input[i] is the same as quote, set in_quote to false
			2. If not in_quote, set quote to input[i] and in_quote to true
		2. If input[i] is a pipe character and not in_quote, break
		3. Increment count
		4. Increment i
	6. Return count
*/
int	count_until_pipe(char *input)
{
	int		count;
	int		in_quote;
	char	quote;
	int		i;

	count = 0;
	in_quote = 0;
	quote = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (in_quote && input[i] == quote)
				in_quote = 0;
			else if (!in_quote)
			{
				quote = input[i];
				in_quote = 1;
			}
		}
		else if (input[i] == '|' && !in_quote)
			break ;
		count++;
		i++;
	}
	return (count);
}

/*
#count_pipes():	counts the number of pipe characters in a string

#Parameters:	char *input	- the string to count pipe characters in

#Return value:	int - the number of pipe characters in the string

#How it works:	
	1. Initialize count to 0
	2. Initialize in_quote to 0
	3. Initialize quote to 0
	4. Initialize i to 0
	5. While input[i] is not NULL
		1. If input[i] is a quote character
			1. If in_quote is true and input[i] is the same as quote, set in_quote to false
			2. If not in_quote, set quote to input[i] and in_quote to true
		2. If input[i] is a pipe character and not in_quote, increment count
		3. Increment i
	6. Return count
*/
int	count_pipes(char *input)
{
	int		count;
	int		in_quote;
	char	quote;
	int		i;

	count = 0;
	in_quote = 0;
	quote = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (in_quote && input[i] == quote)
				in_quote = 0;
			else if (!in_quote)
			{
				quote = input[i];
				in_quote = 1;
			}
		}
		else if (input[i] == '|' && !in_quote)
			count++;
		i++;
	}
	return (count);
}

/*
#copy_until_pipe():	copies characters from a string until a pipe character

#Parameters:		char *start	- the string to copy characters from

#Return value:		char* - the copied string

#How it works:	
	1. Initialize count to the number of characters until a pipe character
	2. Allocate memory for a new string of size count + 1
	3. Initialize i to 0
	4. While i is less than count
		1. Copy start[i] to str[i]
		2. Increment i
	5. Set str[i] to NULL
	6. Return str
*/
char	*copy_until_pipe(char *start)
{
	int		count;
	char	*str;
	int		i;

	i = 0;
	count = count_until_pipe(start);
	str = malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < count)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);

}

/*
#str_blocks():	splits a string into blocks separated by pipe characters

#Parameters:	char *input	- the string to split

#Return value:	char** - an array of strings

#How it works:	
	1. Initialize pipe_count to the number of pipe characters in input
	2. Initialize i to 0
	3. Allocate memory for blocks
	4. While i is less than or equal to pipe_count
		1. Copy characters from input until a pipe character
		2. Increment i
	5. Set the last element of blocks to NULL
	6. Return blocks
*/
char	**str_blocks(char *input)
{
	int		pipe_count;
	int		i;
	char	**blocks;

	i = 0;
	pipe_count = count_pipes(input);
	blocks = malloc((pipe_count + 1) * sizeof(char *));
	if (!blocks)
		return (NULL);
	while (i <= pipe_count)
	{
		blocks[i] = copy_until_pipe(input);
		input += strlen(blocks[i]) + 1;
		i++;
	}
	blocks[i] = NULL;
	return (blocks);
}
