/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 04:14:28 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/31 18:20:13 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	next_run(t_shell *shell)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
	{
		shell->exit = 1;
		return ;
	}
	if (*input)
		add_history(input);
	execute(shell, input, &shell->last_status);
	free(input);
}

int	miniloop(char **envp)
{
	t_shell	shell;

	//ft_bzero(&shell, sizeof(t_shell));
	shell.first_run = 1;
	//load_env(&shell, environ);
	//using_history();
	//register_signals();
	while (!shell.exit)
		next_run(&shell);
	//clear_history();
	//clear_env(&shell.env);
	//clear_env(&shell.secret_env);
	return (shell.last_status);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	return (miniloop(envp));
}

/*
static char	*show_prompt(t_shell *shell)
{
	char		prompt[1024];
	const char	*shell_dir;

	*prompt = 0;
	if (shell->first_run)
	{
		printf("Welcome to minishell v1.0 by mdoll and kschmidt!\n");
		shell->first_run = 0;
	}
	else
	{
		if (shell->last_status)
			ft_strlcat(prompt, "KO ", 1024);
		else
			ft_strlcat(prompt, "OK ", 1024);
	}
	shell_dir = get_shell_dir(shell);
	ft_strlcat(prompt, "minishell [", 1024);
	ft_strlcat(prompt, shell_dir, 1024);
	ft_strlcat(prompt, "] $ ", 1024);
	free((char *)shell_dir);
	return (readline(prompt));
}
*/