/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:28:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/15 03:47:01 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute_cmd(t_data *cmd, char **env)
{
	// if ((!ft_strncmp(cmd->command, "echo", 4) && ft_strlen(cmd->command) == 4))
	// 	exit_builtin(cmd);
	// else if ((!ft_strncmp(cmd->command, "env", 3) && ft_strlen(cmd->command) == 3))
	// 	env_builtin(env);
	// else if ((!ft_strncmp(cmd->command, "unset", 5) && ft_strlen(cmd->command) == 5))
	// 	unset_builtin(cmd, env);
	// else if ((!ft_strncmp(cmd->command, "export", 6) && ft_strlen(cmd->command) == 6))
	// 	export_builtin(cmd, env);
	// else if ((!ft_strncmp(cmd->command, "cd", 2) && ft_strlen(cmd->command) == 2))
	// 	cd_builtin(cmd, env);
	// else if ((!ft_strncmp(cmd->command, "pwd", 3) && ft_strlen(cmd->command) == 3))
	// 	pwd_builtin();
	// else if (!is_builtin_cmd(cmd->command))
	if (!is_builtin_cmd(cmd->command))
		non_builtin(cmd, env);
	else
		printf("prepared builtin execution\n");
	// if (cmd->pid == 0)
	// 	exit(cmd->exit);
}

void	wait_pid(t_data **cmd)
{
	int	i;
	int	status;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i + 1])
			waitpid(cmd[i]->pid, NULL, 0);
		else
		{
			waitpid(cmd[i]->pid, &status, 0);
			// if (WIFEXITED(status))
			// {
			// 	g_exit_code = WEXITSTATUS(status);
			// 	return ;
			// }
		}
		i++;
	}
	if (g_exit_code == 0)
		g_exit_code = cmd[0]->exit;
}

void	exec_main(t_data **cmd, char **env)
{
	//erase
	// int	ii;
	// int	jj;

	// (void)env;
	// ii = -1;
	// printf("%s", YELLOW);
	// while (cmd[++ii])
	// {
	// 	printf("cmd[%d] command: %s\n", ii, cmd[ii]->command);
	// 	jj = -1;
	// 	while (cmd[ii]->option[++jj])
	// 		printf("  option[%d]: %s\n", jj, cmd[ii]->option[jj]);
	// 	if (cmd[ii]->redir->redir_flag == IN)
	// 		printf("  redir: IN, filename: %s\n", cmd[ii]->redir->file_name);
	// 	else if (cmd[ii]->redir->redir_flag == OUT)
	// 		printf("  redir: OUT, filename: %s\n", cmd[ii]->redir->file_name);
	// 	else if (cmd[ii]->redir->redir_flag == HEREDOC)
	// 		printf("  redir: HEREDOC, filename: %s\n", cmd[ii]->redir->file_name);
	// 	else if (cmd[ii]->redir->redir_flag == APPEND)
	// 		printf("  redir: APPEND, filename: %s\n", cmd[ii]->redir->file_name);
	// 	else
	// 		printf("  redir: NONE\n");
	// }
	// printf("%s", BLACK);
	//until here

	int	(*_pipe)[2];
	int	i;

	_pipe = NULL;
	check_heredoc(cmd);
	alloc_pipe(cmd, &_pipe);
	i = 0;
	while (cmd[i])
	{
		if (!is_builtin_cmd(cmd[i]->command) || i > 0 )
			cmd[i]->pid = fork();
		if (cmd[i]->pid == 0 || cmd[i]->pid == -1)
		{
			if (i > 0)
				dup2(_pipe[i - i][STDIN], STDIN);
			if (cmd[i + 1])
				dup2(_pipe[i][STDOUT], STDOUT);
			close_pipe(cmd, &_pipe);
			if (redir_set_fd(cmd[i]))
				execute_cmd(cmd[i], env);
			if (is_builtin_cmd(cmd[i]->command) && i > 0)//
				exit(0);//
		}
		i++;
	}
	close_pipe(cmd, &_pipe);
	free((*_pipe));
	wait_pid(cmd);
}
