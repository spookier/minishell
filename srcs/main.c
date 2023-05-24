/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/24 16:07:51 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/minishell.h"

int	minishell_main(char **env)
{
	char	*rdline;
	
	while (1)
	{
		//ft_signal();
		printf("%s", CYAN);
		rdline = readline("minishell$ ");
		printf("%s", BLACK);
		add_history(rdline);
		printf("%s\n", rdline);
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
