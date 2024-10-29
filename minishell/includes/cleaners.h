/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:44:36 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/08 13:56:27 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANERS_H
# define CLEANERS_H

# include "minishell.h"
# include "types.h"

void	free_env(t_env *env);
void	free_array(char **arr);
void	free_tokens(t_token *head);
void	cleanup_heredocs(t_cmd *cmd);
void	free_cmds(t_cmd *head);

#endif