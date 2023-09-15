/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:42:19 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/15 03:42:47 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	write_heredoc(int fd_heredoc, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("%sminishell: warning: here-document delimited by end-of-file%s\n", RED, BLACK);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0
			&& ft_strlen(line) == ft_strlen(delim))
		{
			free(line);
			break ;
		}
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		free(line);
	}
	close(fd_heredoc);
}

void	check_heredoc(t_data **cmd)
{
	int		i;
	int		fd_heredoc;
	char	*file_name;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->redir->redir_flag == HEREDOC)
		{
			file_name = ft_strdup("/tmp/.heredoc_");
			file_name = append_num_to_alloced_str(file_name, i);
			fd_heredoc = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			write_heredoc(fd_heredoc, cmd[i]->redir->file_name);
			free(cmd[i]->redir->file_name);
			cmd[i]->redir->file_name = file_name;
		}
		i++;
	}
}
