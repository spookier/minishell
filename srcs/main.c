/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/24 16:18:39 by yhwang           ###   ########.fr       */
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

int	minishell_main(char **env)
{
	char	*rdline;
	t_Error *error;
	
	error = malloc(sizeof(t_Error));
	if(!error)
		return(-1);
	error->error_str = NULL;

	minishell_header();
	while (1)
	{
		//ft_signal();
		printf("%s", CYAN);
		rdline = readline("minishell$ ");
		printf("%s", BLACK);
		add_history(rdline);
		printf("%s\n", rdline);
		parse_rdline(rdline, error);
		if(error->error_str)
			printf("%s\n", error->error_str);
		free(rdline);
	}
	free(error);
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
