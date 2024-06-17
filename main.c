/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:15:11 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/17 13:16:05 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal_status = 420;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signal_status = signo;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		g_signal_status = signo;
	}
}

int	minishell_loop(void)
{
	char	*input;
	int		i;

	i = 0;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		input = readline(PROMPT);
		if (!input)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		if (*input)
		{
			add_history(input);
			//split tokens
			char **token_array = split_tokens(input);
			//lexer / tokenization
			t_token *token_list = lexer(token_array);
			//syntax error check
			if (syntax_error(token_list))
			{
				free_array_and_tokens(token_array, token_list);
				continue ;
			}
			free_array(token_array);
			// print_tokens(token_list);
			// free_array_and_tokens(token_array, token_list);
			//parser
			token_list = env_expand(token_list);
			t_cmd *cmd_list = parser(token_list);
			//print_cmds(cmd_list);
			i = exec_cmds(cmd_list);
			free_tokens(token_list);
			free_cmd(cmd_list);
			//execute
			//free / clean up
		}
		free(input);
	}
	return (i);
}

//int argc, char **argv
int	main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	return (minishell_loop());
}

/*
Sample execute:
int execute_command(char *input)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		// Child process
		char *argv[] = {"/bin/sh", "-c", input, NULL};
		execve("/bin/sh", argv, NULL);
		exit(127); // If execve fails
	}
	else if (pid < 0)
	{
		// Fork failed
		perror("fork");
		return 1;
	}
	else
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
}
*/
