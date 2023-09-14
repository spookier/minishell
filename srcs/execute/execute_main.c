/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:28:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/14 21:04:38 by yhwang           ###   ########.fr       */
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

void	alloc_pipe(t_data **cmd, int (**_pipe)[2])
{
	int	i;

	i = 0;
	*_pipe = NULL;
	while (cmd[i + 1])
	{
		*_pipe = ft_realloc(*_pipe, sizeof(int *) * i,
	 		sizeof(int *) * (i + 1));
		pipe((*_pipe)[i]);
		printf("%dth: pipe created\n", i);//
		i++;
	}
}

void	close_pipe(t_data **cmd, int (**_pipe)[2])
{
	int	i;

	i = 0;
	while (cmd[i + 1])
	{
		close((*_pipe)[i][STDIN]);
		close((*_pipe)[i][STDOUT]);
		printf("%dth: pipe closed\n", i);//
		i++;
	}
}

int	is_builtin_cmd(char *command)
{
	if ((!ft_strncmp(command, "echo", 4) && ft_strlen(command) == 4)
		|| (!ft_strncmp(command, "env", 3) && ft_strlen(command) == 3)
		|| (!ft_strncmp(command, "unset", 5) && ft_strlen(command) == 5)
		|| (!ft_strncmp(command, "export", 6) && ft_strlen(command) == 6)
		|| (!ft_strncmp(command, "cd", 2) && ft_strlen(command) == 2)
		|| (!ft_strncmp(command, "pwd", 3) && ft_strlen(command) == 3)
		|| (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4))
		return (1);
	return (0);
}

int	redir_open_file(int *in_fd, int *out_fd, t_data *cmd)
{
	if (cmd->redir->redir_flag == IN)
	{
		*in_fd = open(cmd->redir->file_name, O_RDONLY);
		if (*in_fd == -1)
		{
			printf("%sminishell: No such file or directory%s\n", RED, BLACK);
			cmd->exit = 1;
			if (cmd->pid == 0)
				exit(1);
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
		}
		if (cmd->redir->redir_flag == OUT || cmd->redir->redir_flag == APPEND)
		{
			dup2(out_fd, STDOUT);
			close(out_fd);
		}
	}
	return (1);
}

void	execute_cmd(t_data *cmd, char **env)
{
	(void)env;

	if ((!ft_strncmp(cmd->command, "exit", 4) && ft_strlen(cmd->command) == 4))
		exit_builtin(cmd);
	if ((!ft_strncmp(cmd->command, "echo", 4) && ft_strlen(cmd->command) == 4))
		echo_builtin(cmd);
	// if (cmd->pid == 0)
	// 	exit(cmd->exit);
}

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

	int	(*_pipe)[2];
	// int	fd[2];
	int	i;

	_pipe = NULL;
	check_heredoc(cmd);
	alloc_pipe(cmd, &_pipe);
	i = 0;
	while (cmd[i])
	{
		if (!is_builtin_cmd(cmd[i]->command) || cmd[i + 1])
		{
			cmd[i]->pid = fork();
			printf("forked\n");
		}
		if (cmd[i]->pid == 0)
		{
			printf("this is child, pid %d\n", cmd[i]->pid);
			if (i > 0)
				dup2(_pipe[i][STDIN], STDIN);
			if (cmd[i + 1])
				dup2(_pipe[i][STDOUT], STDOUT);
			close_pipe(cmd, &_pipe);
			if (redir_set_fd(cmd[i]))


				execute_cmd(cmd[i], env);
				


			if (!is_builtin_cmd(cmd[i]->command) || (is_builtin_cmd(cmd[i]->command) && i > 0))//
				exit(0);//
		}
		i++;
	}

	int	j;
	int	status;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j + 1])
			waitpid(cmd[j]->pid, NULL, 0);
		else
		{
			waitpid(cmd[j]->pid, &status, 0);
			if (WIFEXITED(status))
			{
				g_exit_code = WEXITSTATUS(status);
				return ;
			}
		}
		j++;
	}
	if (g_exit_code == 0)
		g_exit_code = cmd[0]->exit;
	close_pipe(cmd, &_pipe);
	free((*_pipe));
}
