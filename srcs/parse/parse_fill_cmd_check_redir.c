/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_cmd_check_redir.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:58:08 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 06:02:52 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fill_redir(t_data **cmd, char **split_cmd, int cmd_i)
{
	int	i;
	int	j;
	int	flag;

	if (cmd[cmd_i]->redir[0]->redir_flag == NONE)
		return ;
	i = -1;
	flag = 0;
	while (split_cmd[++i])
	{
		if (is_redir(split_cmd[i]))
		{
			flag++;
			continue ;
		}
	}
	if (flag == 1)
		cmd[cmd_i]->redir[0]->file_name = ft_strdup(split_cmd[--i]);
	else
	{
		cmd[cmd_i]->redir = ft_realloc(cmd[cmd_i]->redir, sizeof(t_redir **) * 2,
					sizeof(t_redir **) * (flag + 1));
		j = 0;
		while (j < flag)
		{
			if (j > 0)
				cmd[cmd_i]->redir[j] = ft_calloc(sizeof(t_redir *), 2);
			printf("flag: %d\n", cmd[cmd_i]->redir[j]->redir_flag);
			cmd[cmd_i]->redir[j]->redir_flag = -1;
			if (split_cmd[(j + 1) * 2 - 1][0] == '<')
			{
				if (split_cmd[(j + 1) * 2 - 1][1]
					&& split_cmd[(j + 1) * 2 - 1][1] == '<')
					cmd[cmd_i]->redir[j]->redir_flag = HEREDOC;
				else
					cmd[cmd_i]->redir[j]->redir_flag = IN;
			}
			else if (split_cmd[(j + 1) * 2 - 1][0] == '>')
			{
				if (split_cmd[(j + 1) * 2 - 1][1]
					&& split_cmd[(j + 1) * 2 - 1][1] == '>')
					cmd[cmd_i]->redir[j]->redir_flag = APPEND;
				else
					cmd[cmd_i]->redir[j]->redir_flag = OUT;
			}
			if (cmd[cmd_i]->redir[j]->redir_flag == -1)
				cmd[cmd_i]->redir[j]->redir_flag = NONE;
			cmd[cmd_i]->redir[j]->file_name = ft_strdup(split_cmd[(j + 1) * 2]);
			j++;
		}
	}
}

void	check_redir(t_data **cmd, char *each_cmd, char **split_cmd, int cmd_i)
{
	int	i;

	i = 0;
	cmd[cmd_i]->redir[0]->redir_flag = -1;
	while (each_cmd[i] && cmd[cmd_i]->redir[0]->redir_flag == -1)
	{
		if (each_cmd[i] == '<')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '<')
				cmd[cmd_i]->redir[0]->redir_flag = HEREDOC;
			else
				cmd[cmd_i]->redir[0]->redir_flag = IN;
		}
		if (each_cmd[i] == '>')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '>')
				cmd[cmd_i]->redir[0]->redir_flag = APPEND;
			else
				cmd[cmd_i]->redir[0]->redir_flag = OUT;
		}
		i++;
	}
	if (cmd[cmd_i]->redir[0]->redir_flag == -1)
		cmd[cmd_i]->redir[0]->redir_flag = NONE;
	fill_redir(cmd, split_cmd, cmd_i);
}
