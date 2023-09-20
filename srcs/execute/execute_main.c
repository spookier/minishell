/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:28:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/18 05:18:30 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute_cmd(t_data **cmd_struct,
			t_data *cmd, char **env, int (*_pipe)[2])
{
	if ((!ft_strncmp(cmd->command, "echo", 4)
			&& ft_strlen(cmd->command) == 4))
		builtin_echo(cmd);
	else if ((!ft_strncmp(cmd->command, "env", 3)
			&& ft_strlen(cmd->command) == 3))
		builtin_env(env);
	else if ((!ft_strncmp(cmd->command, "unset", 5)
			&& ft_strlen(cmd->command) == 5))
		builtin_unset(cmd, env);
	else if ((!ft_strncmp(cmd->command, "export", 6)
			&& ft_strlen(cmd->command) == 6))
		builtin_export(cmd, env);
	else if ((!ft_strncmp(cmd->command, "cd", 2)
			&& ft_strlen(cmd->command) == 2))
		builtin_cd(cmd, env);
	else if ((!ft_strncmp(cmd->command, "pwd", 3)
			&& ft_strlen(cmd->command) == 3))
		builtin_pwd();
	else if ((!ft_strncmp(cmd->command, "exit", 4)
			&& ft_strlen(cmd->command) == 4))
		builtin_exit(cmd_struct, cmd, env, _pipe);
	else
		non_builtin(cmd, env);
	if (cmd->pid == 0)
		exit(cmd->exit);
}

void	wait_pid(t_data **cmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (cmd[i])
	{
		if (cmd[i + 1])
			waitpid(cmd[i]->pid, NULL, 0);
		else
		{
			waitpid(cmd[i]->pid, &status, 0);
			if (WIFEXITED(status))
			{
				g_exit_code = WEXITSTATUS(status);
				return ;
			}
		}
		i++;
	}
}

void	exec_main(t_data **cmd, char **env)
{
	int	(*_pipe)[2];
	int	fd[2];
	int	i;

	check_heredoc(cmd);
	alloc_pipe(cmd, &_pipe);
	i = -1;
	while (cmd[++i])
	{
		if (!is_builtin_cmd(cmd[i]->command) || i > 0 || cmd[i + 1])
			cmd[i]->pid = fork();
		else
			cmd[i]->pid = PARENTS;
		if (cmd[i]->pid == CHILD || cmd[i]->pid == PARENTS)
		{
			set_fd_close_pipe(cmd, &_pipe, i);
			set_fd_stdio(fd);
			if (redir_set_fd(cmd[i]))
				execute_cmd(cmd, cmd[i], env, _pipe);
			close_fd_stdio(fd);
		}
	}
	close_pipe(cmd, &_pipe);
	free((*_pipe));
	wait_pid(cmd);
}
