/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:28:48 by pmelis            #+#    #+#             */
/*   Updated: 2024/07/29 18:16:07 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(void)
{
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
