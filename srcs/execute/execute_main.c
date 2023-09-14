/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:28:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/13 01:43:52 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	write_heredoc(int fd_heredoc, char *delim, char *file_name)
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
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0 && ft_strlen(line) == ft_strlen(delim))
		{
			free(line);
			unlink(file_name);
			break ;
		}
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		free(line);
	}
	close(fd_heredoc);
}

void	handle_fd_heredoc(char *delim)
{
	int		fd_heredoc;
	char	*file_name;

	file_name = "/tmp/.heredoc";
	fd_heredoc = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	write_heredoc(fd_heredoc, delim, file_name);
}

void	check_heredoc(t_data **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->redir->redir_flag == HEREDOC)
		{
			printf("	this is heredoc\n");
			handle_fd_heredoc(cmd[i]->redir->file_name);
		}
		i++;
	}
}

// void	alloc_pipe(t_data **cmd, int (*_pipe)[2])
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
		
// 	}
// }

void	exec_main(t_data **cmd, char **env)
{
	//erase
	int	ii;
	int	jj;

	(void)env;
	ii = -1;
	printf("%s", YELLOW);
	while (cmd[++ii])
	{
		printf("cmd[%d] command: %s\n", ii, cmd[ii]->command);
		jj = -1;
		while (cmd[ii]->option[++jj])
			printf("  option[%d]: %s\n", jj, cmd[ii]->option[jj]);
		if (cmd[ii]->redir->redir_flag == IN)
			printf("  redir: IN, filename: %s\n", cmd[ii]->redir->file_name);
		else if (cmd[ii]->redir->redir_flag == OUT)
			printf("  redir: OUT, filename: %s\n", cmd[ii]->redir->file_name);
		else if (cmd[ii]->redir->redir_flag == HEREDOC)
			printf("  redir: HEREDOC, filename: %s\n", cmd[ii]->redir->file_name);
		else if (cmd[ii]->redir->redir_flag == APPEND)
			printf("  redir: APPEND, filename: %s\n", cmd[ii]->redir->file_name);
		else
			printf("  redir: NONE\n");
	}
	printf("%s", BLACK);
	//until here

	//int	_pipe[2];
	//int	fd[2];
	// int	i;

	check_heredoc(cmd);
	//alloc_pipe(cmd, &_pipe);
}
