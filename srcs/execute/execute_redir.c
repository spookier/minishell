/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:43:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/15 03:43:48 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	redir_open_file(int *in_fd, int *out_fd, t_data *cmd)
{
	if (cmd->redir->redir_flag == IN || cmd->redir->redir_flag == HEREDOC)
	{
		*in_fd = open(cmd->redir->file_name, O_RDONLY);
		if (*in_fd == -1)
		{
			printf("%sminishell: No such file or directory%s\n", RED, BLACK);
			if (cmd->pid == 0)
				exit(1);
			cmd->exit = 1;
			return (0);
		}
	}
	if (cmd->redir->redir_flag == OUT)
		*out_fd = open(cmd->redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (cmd->redir->redir_flag == APPEND)
		*out_fd = open(cmd->redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0664);
	return (1);
}

int	redir_set_fd(t_data *cmd)
{
	int	in_fd;
	int	out_fd;

	if (cmd->redir->redir_flag != NONE)
	{
		if (!redir_open_file(&in_fd, &out_fd, cmd))
			return (0);
		if (cmd->redir->redir_flag == IN || cmd->redir->redir_flag == HEREDOC)
		{
			dup2(in_fd, STDIN);
			close(in_fd);
			if (cmd->redir->redir_flag == HEREDOC)
				unlink(cmd->redir->file_name);
		}
		if (cmd->redir->redir_flag == OUT || cmd->redir->redir_flag == APPEND)
		{
			dup2(out_fd, STDOUT);
			close(out_fd);
		}
	}
	return (1);
}
