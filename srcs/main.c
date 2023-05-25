/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/25 05:06:37 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

char	**alloc_env(char **env)
{
	char	**arr_env;
	int		i;

	arr_env = (char **)ft_calloc(sizeof(char *), 2);
	if (!arr_env)
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		exit(1);
	}
	i = -1;
	while (env[++i])
	{
		arr_env = ft_realloc(arr_env, sizeof(char *) * (i + 1),
				sizeof(char *) * (i + 2));
		arr_env[i] = strdup(env[i]);
		if (!arr_env[i])
		{
			printf("%sError: malloc error%s\n", RED, BLACK);
			free_2d_arr(env);
			exit(1);
		}
	}
	return (arr_env);
}

int	minishell_main(char **env)
{
	char	*rdline;
	t_data	**cmd;

	minishell_header();
	while (1)
	{
		signal_detect();
		cmd = ft_calloc(sizeof(t_data *), 2);
		if (!cmd)
		{
			printf("%sError: malloc error%s\n", RED, BLACK);
			free_2d_arr(env);
			exit(1);
		}
		rdline = readline("minishell$ ");
		if (check_valid_input(rdline, env))
		{
			add_history(rdline);
			cmd = parse(cmd, env, rdline);
		}
		free(rdline);
		if (cmd)
			free_cmd(cmd);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
	{
		printf("%sArgument error%s\n", RED, BLACK);
		printf("%sUseage: ./minishell%s\n", RED, BLACK);
		return (1);
	}
	env = alloc_env(env);
	minishell_main(env);
	free_2d_arr(env);
	return (0);
}
