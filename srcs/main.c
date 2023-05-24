/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/25 00:19:48 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/minishell.h"

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

int	check_valid_input(char *str)
{
	if (str == NULL)
	{
		printf("exit\n");
		exit(0);
		return (0);
	}
	return (1);
}

t_data	**alloc_cmd(t_data **cmd, int i)
{
	cmd = ft_realloc(cmd, sizeof(t_data *) * (i + 1),
				sizeof(t_data *) * (i + 2));
	if (!cmd)
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		exit(1);
	}
	cmd[i] = (t_data *)ft_calloc(sizeof(t_data), 2);
	if (!cmd[i])
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		free_cmd(cmd);
		exit(1);
	}
	return (cmd);
}

int	minishell_main(char **env)
{
	char	*rdline;
	t_data	**cmd;
	char	**split_pipe;
	int	i;

	minishell_header();
	while (1)
	{
		signal_detect();
		cmd = ft_calloc(sizeof(t_data *), 2);
		if (!cmd)
		{
			printf("%sError: malloc error%s\n", RED, BLACK);
			exit(1);
		}
		rdline = readline("minishell$ ");
		if (check_valid_input(rdline))
		{
			add_history(rdline);
			split_pipe = ft_split(rdline, '|');
			i = -1;
			while (split_pipe[++i])
			{
				cmd = alloc_cmd(cmd, i);
				cmd[i]->command = split_pipe[i];
			}
			free_2d_arr(split_pipe);
		}
		free_cmd(cmd);
		free(rdline);
	}
	(void)env;
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
	minishell_main(env);
	return (0);
}
