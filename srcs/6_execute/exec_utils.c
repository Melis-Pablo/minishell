/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:10:08 by pmelis            #+#    #+#             */
/*   Updated: 2024/08/02 15:10:08 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
merge_args():	combines args and flags into one array and put it inside
						the cmd struct cmd->args array

Parameters:				t_cmd *cmd:	pointer to the cmd struct

Return value:			int:			0 if success, 1 if malloc error

How it works:
*/
int	merge_args(t_cmd *cmd)
{
	int		i;
	int		j;
	int		t_len;
	char	**merged;

	if (!cmd)
		return (1);
	t_len = 1 + array_len(cmd->args) + array_len(cmd->flags);
	merged = (char **)malloc(sizeof(char *) * (t_len + 1));
	if (!merged)
		return (1);
	i = 0;
	merged[i++] = ft_strdup(cmd->cmd);
	j = 0;
	while (cmd->args && cmd->args[j])
		merged[i++] = ft_strdup(cmd->args[j++]);
	j = 0;
	while (cmd->flags && cmd->flags[j])
		merged[i++] = ft_strdup(cmd->flags[j++]);
	merged[i] = NULL;
	free_array(cmd->args);
	cmd->args = merged;
	return (0);
}












// //change to put flags in to args array
// char	**merge_args(t_cmd *cmd)
// {
// 	int		i;
// 	int		j;
// 	int		t_len;
// 	char	**merged;

// 	if (!cmd)
// 		return (NULL);
// 	t_len = 1 + array_len(cmd->args) + array_len(cmd->flags);
// 	merged = (char **)malloc(sizeof(char *) * (t_len + 1));
// 	if (!merged)
// 		return (NULL);
// 	i = 0;
// 	merged[i++] = ft_strdup(cmd->cmd);
// 	j = 0;
// 	while (cmd->args && cmd->args[j])
// 		merged[i++] = ft_strdup(cmd->args[j++]);
// 	j = 0;
// 	while (cmd->flags && cmd->flags[j])
// 		merged[i++] = ft_strdup(cmd->flags[j++]);
// 	merged[i] = NULL;
// 	return (merged);
// }