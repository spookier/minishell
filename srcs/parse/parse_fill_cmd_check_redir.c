/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_cmd_check_redir.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:58:08 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/22 00:59:14 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fill_redir(t_data **cmd, char **split_cmd, int cmd_i)
{
	int	i;

	if (cmd[cmd_i]->redir->redir_flag == NONE)
	{
		cmd[cmd_i]->redir->file_name = ft_strdup("");
		return ;
	}
	i = -1;
	while (split_cmd[++i])
	{
		if (is_redir(split_cmd[i]))
			break ;
	}
	i++;
	cmd[cmd_i]->redir->file_name = ft_strdup(split_cmd[i]);
}

void	check_redir(t_data **cmd, char *each_cmd, char **split_cmd, int cmd_i)
{
	int	i;

	i = 0;
	cmd[cmd_i]->redir->redir_flag = -1;
	while (each_cmd[i] && cmd[cmd_i]->redir->redir_flag == -1)
	{
		if (each_cmd[i] == '<')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '<')
				cmd[cmd_i]->redir->redir_flag = HEREDOC;
			else
				cmd[cmd_i]->redir->redir_flag = IN;
		}
		if (each_cmd[i] == '>')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '>')
				cmd[cmd_i]->redir->redir_flag = APPEND;
			else
				cmd[cmd_i]->redir->redir_flag = OUT;
		}
		i++;
	}
	if (cmd[cmd_i]->redir->redir_flag == -1)
		cmd[cmd_i]->redir->redir_flag = NONE;
	fill_redir(cmd, split_cmd, cmd_i);
}
