/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/28 00:41:05 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
	return (arr_env);
}

void	minishell_header(void)
{
	printf("%s\n", YELLOW);
	printf("╔════╦════╦══╦════════╦══╦═══════╦══╗  ╔══╦═══════╦══╗  ╔══╗   \n");
	printf("║    ║    ║  ║        ║  ║       ║  ║  ║  ║       ║  ║  ║  ║   \n");
	printf("║    ║    ║  ║  ╔══╗  ║  ║   ════╣  ╚══╝  ║   ════╣  ║  ║  ║   \n");
	printf("║  ║ ║ ║  ║  ║  ║  ║  ║  ║       ║        ║       ║  ║  ║  ║   \n");
	printf("║  ║ ║ ║  ║  ║  ║  ║  ║  ╠════   ║  ╔══╗  ║   ════╣  ╚══╣  ╚══╗\n");
	printf("║  ║   ║  ║  ║  ║  ║  ║  ║       ║  ║  ║  ║       ║     ║     ║\n");
	printf("╚══╩═══╩══╩══╩══╝  ╚══╩══╩═══════╩══╝  ╚══╩═══════╩═════╩═════╝\n");
	printf("                                                               \n");
	printf("                                      by. acostin, yhwang 🐣🐥 \n");
	printf("%s\n", BLACK);
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
		rdline = readline("minishell$ ");
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
		free(rdline);
		free_cmd(cmd);
	}
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
		return (free_2d_arr(env), 1);
	free_2d_arr(env);
	return (0);
}
