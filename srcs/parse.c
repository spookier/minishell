/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:35:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/28 00:34:13 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_data	**alloc_cmd(t_data **cmd, int i)
{
	cmd = ft_realloc(cmd, sizeof(t_data *) * (i + 1),
			sizeof(t_data *) * (i + 2));
	if (!cmd)
		return (printf("%sError: malloc error%s\n", RED, BLACK), NULL);
	cmd[i] = (t_data *)ft_calloc(sizeof(t_data), 2);
	if (!cmd[i])
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		return (free_cmd(cmd), NULL);
	}
	return (cmd);
}

t_data	**parse(t_data **cmd, char **env, char *rdline)
{
	//todo: replace with value of env variable
	//don't free cmd, env
	//echo "$HOME": /home/chloe
	//echo "'$HOME'": '/home/chloe'
	//echo ""$HOME"": /home/chloe
	//echo "$'HOME'": $'HOME'
	//echo $'HOME': HOME
	//echo $"A": A
	//ls $ABC: incs  libft  Makefile  minishell  srcs
	//ls $PATH: ls: cannot access '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin': No such file or directory
	char	**split_pipe;
	int		i;

	if (token_quote_err(rdline) || token_err(rdline) || pos_err(rdline))
		return (free_cmd(cmd), NULL);
	printf("%srdline: %s%s\n", CYAN, rdline, BLACK);//
	split_pipe = ft_split(rdline, '|');
	i = -1;
	while (split_pipe[++i])
	{
		cmd = alloc_cmd(cmd, i);
		if (!cmd)
			return (free_2d_arr(split_pipe), NULL);
		cmd[i]->command = split_pipe[i];
	}
	free_2d_arr(split_pipe);
	(void)env;
	return (cmd);
}
