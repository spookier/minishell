/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/21 20:09:30 by yhwang           ###   ########.fr       */
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
		/* detect signal */
		signal_detect();
		/* alloc cmd */
		cmd = ft_calloc(sizeof(t_data *), 2);
		/* error check: malloc */
		if (!cmd)
			return (printf("%sError: malloc error%s\n", RED, BLACK), 1);
		/* read command  */
		rdline = readline("\x1b[36mminishell$\x1b[0m ");
		/*  */
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
	/* error check: argument */
	if (argc != 1)
		return (printf("%sArgument error\nUseage: ./minishell%s\n",
				RED, BLACK), 1);
	/* alloc env variable */
	env = alloc_env(env);
	/* error check: malloc */
	if (!env)
		return (1);
	/* print our minishell header */
	minishell_header();
	cmd = NULL;
	/* normal operation: in case of any error, free env variable and return 1 */
	if (minishell_main(cmd, env))
		return (free_2d_arr(env), 1);
	/* run command */
	exec(cmd, env);
	/* free: env variable */
	free_2d_arr(env);
	return (0);
}
