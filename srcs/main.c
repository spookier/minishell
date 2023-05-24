/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/24 20:55:41 by yhwang           ###   ########.fr       */
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
	}
	return (1);
}

int	minishell_main(char **env)
{
	char	*rdline;
	char	**split_pipe;

	minishell_header();
	while (1)
	{
		signal_detect();
		rdline = readline("minishell$ ");
		if (check_valid_input(rdline))
		{
			add_history(rdline);
			split_pipe = ft_split(rdline, '|');
			int	i = 0;
			while (split_pipe[i] != NULL)
			{
				printf("split_pipe[%d]: %s\n\n", i, split_pipe[i]);
				i++;
			}
			printf("\n");
			free_2d_arr(split_pipe);
		}
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
