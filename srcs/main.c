/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 01:17:25 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit_code;

int	alloc_env(char ***env)
{
	char	**arr_env;
	int		i;

	arr_env = (char **)ft_calloc(sizeof(char *), 2);
	if (!arr_env)
		return (printf("%sError: malloc error%s\n", RED, BLACK), 1);
	i = -1;
	while ((*env)[++i] && find_c_pos((*env)[i], '=', 0) != -1)
	{
		if (i > 0)
			arr_env = ft_realloc(arr_env, sizeof(char *) * (i + 1),
					sizeof(char *) * (i + 2));
		arr_env[i] = ft_strdup((*env)[i]);
		if (!arr_env[i])
		{
			printf("%sError: malloc error%s\n", RED, BLACK);
			return (free_2d_arr(arr_env), 1);
		}
	}
	arr_env = remove_element_from_env(arr_env, "OLDPWD");
	*env = arr_env;
	return (0);
}

void	signal_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == CHILD)
			printf("\n");
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_code = 130;
	}
	else if (signo == SIGQUIT)
	{
		if (pid == CHILD)
			printf("Quit\n");
	}
}

void	signal_detect(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	minishell_main(t_data **cmd, char ***env)
{
	char	*rdline;

	while (1)
	{
		signal_detect();
		cmd = ft_calloc(sizeof(t_data *), 2);
		if (!cmd)
		{
			return (printf("%sError: malloc error%s\n", RED, BLACK), 1);
			free_2d_arr(*env);
		}
		rdline = readline("\001\x1b[36m\002minishell$\001\x1b[0m\002 ");
		if (!rdline)
		{
			printf("exit\n");
			free_2d_arr(*env);
			return (free_cmd(cmd), 2);
		}
		add_history(rdline);
		cmd = parse(cmd, *env, rdline);
		if (!cmd)
		{
			free(rdline);
			continue ;
		}
		exec_main(cmd, env);
		free_cmd(cmd);
	}
	return (free_2d_arr(*env), 0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	**cmd;

	(void)argv;
	if (argc != 1)
		return (printf("%sArgument error\nUseage: ./minishell%s\n",
				RED, BLACK), 1);
	if (alloc_env(&env))
		return (1);
	if (!env)
		return (1);
	minishell_header();
	cmd = NULL;
	if (minishell_main(cmd, &env))
		return (1);
	return (0);
}
