/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:53 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/12 20:00:41 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Input Redirections (<)

	Multiple < Redirections:
		Example: command < infile1 < infile2
		Behavior: Only the last redirection is used, so the command will read
			input from infile2.
		Effect on First Ones: The first redirections (< infile1) have no effect
			They are ignored.

Output Redirections (> and >>)

	Multiple > Redirections:
		Example: command > outfile1 > outfile2
		Behavior: Only the last redirection is used, so the command will write
			to outfile2, truncating it before writing.
		Effect on First Ones: The first redirections (> outfile1) have no
			effect. They are ignored.

	Multiple >> Redirections:
		Example: command >> appendfile1 >> appendfile2
		Behavior: Only the last redirection is used, so the command will append
			to appendfile2.
		Effect on First Ones: The first redirections (>> appendfile1) have no
			effect. They are ignored.

	Mixing > and >>:
		Example: command > outfile >> appendfile
		Behavior: Only the last redirection is used. Here, the command will
			append to appendfile.
		Effect on First Ones: The first redirection (> outfile) has no effect.
			It is ignored.

		Example: command >> appendfile > outfile
		Behavior: Only the last redirection is used. Here, the command will write
			to outfile, truncating it before writing.
		Effect on First Ones: The first redirection (>> appendfile) has no effect
			It is ignored.

Here Document Redirections (<<)

	Mixing < and <<:
		< infile is used to redirect input from a file.
		<< delimiter is used for here documents, where a block of text is
			provided directly in the command line until the delimiter is reached.

	Example: command < infile << EOF
		Behavior: The shell processes the input redirection (< infile) first,
			setting up the input from infile. The here document (<< EOF) is
			usually processed to provide input directly on the command line,
			which conflicts with reading from a file.
		Effect: the last one is used, but everything processed before that is
			ignored.
*/

/*
handle_input_redirections():
	1. Open the file for reading.
	2. Redirect the standard input to the file.
	3. Close the file.
	4. The command will read input from the file.
*/
void	handle_input_redirections(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_output_redirections(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_append_redirections(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

// void	andle_heredoc_redirections(char *delimiter)
// {

// }

void	handle_redirections(t_lexer *head)
{
	t_lexer	*curr;

	curr = head;
	while (curr)
	{
		if (curr->type == REDIR_INPUT)
		{
			handle_input_redirections(curr->next->word);
			//curr = take_out_node(curr);
		}
		else if (curr->type == REDIR_OUTPUT)
		{
			handle_output_redirections(curr->next->word);
			//curr = take_out_node(curr);
		}
		else if (curr->type == REDIR_APPEND)
		{
			handle_append_redirections(curr->next->word);
			//curr = take_out_node(curr);
		}
		// else if (curr->type == REDIR_HEREDOC)
		// 	handle_heredoc_redirections(curr->next->word);
		curr = curr->next;
	}
}

void	execute_command(t_lexer *head)
{
	t_lexer	*curr;
	char	*array[100]; //change to dynamic;
	int		i;

	curr = head;
	i = 0;
	while (curr)
	{
		if (curr->type == NO_REDIRECTION )
		{
			array[i] = ft_strdup(curr->word); //add to array
			i++;
		}
		curr = curr->next;
	}
	array[i] = NULL;
	execve(array[0], array, NULL);
	free_array(array);
}

void	my_execution(t_cmd *head)
{
	t_cmd	*curr;

	curr = head;
	while (curr)
	{
		handle_redirections(curr->lexer);
		
		execute_command(curr->lexer);
		curr = curr->next;
	}
}
