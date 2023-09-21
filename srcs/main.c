/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/21 23:55:09 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit_code;

char	**alloc_env(char **env)
{
	char	**arr_env;
	int		i;

	arr_env = (char **)ft_calloc(sizeof(char *), 2);
	if (!arr_env)
		return (printf("%sError: malloc error%s\n", RED, BLACK), NULL);
	i = -1;
	while (env[++i])
	{
		arr_env = ft_realloc(arr_env, sizeof(char *) * (i + 1),
				sizeof(char *) * (i + 2));
		arr_env[i] = strdup(env[i]);
		if (!arr_env[i])
		{
			printf("%sError: malloc error%s\n", RED, BLACK);
			return (free_2d_arr(env), NULL);
		}
	}
	arr_env = remove_element_from_env(arr_env, "OLDPWD");
	return (arr_env);
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

int	minishell_main(t_data **cmd, char **env)
{
	char	*rdline;

	while (1)
	{
		signal_detect();
		cmd = ft_calloc(sizeof(t_data *), 2);
		if (!cmd)
			return (printf("%sError: malloc error%s\n", RED, BLACK), 1);
		rdline = readline("\x1b[36mminishell$\x1b[0m ");
		if (!rdline)
		{
			printf("exit\n");
			return (free_cmd(cmd), 1);
		}
		add_history(rdline);
		cmd = parse(cmd, env, rdline);
		if (!cmd)
		{
			free(rdline);
			continue ;
		}
		exec_main(cmd, &env);
		free_cmd(cmd);
	}
	free_2d_arr(env);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	**cmd;

	(void)argv;
	if (argc != 1)
		return (printf("%sArgument error\nUseage: ./minishell%s\n",
				RED, BLACK), 1);
	env = alloc_env(env);
	if (!env)
		return (1);
	minishell_header();
	cmd = NULL;
	if (minishell_main(cmd, env))
		return (1);
	return (0);
}
