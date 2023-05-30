/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:35:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/30 04:56:56 by yhwang           ###   ########.fr       */
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

char	*remove_str_from_line(char *line, int str_start_pos, int str_len)
{
	//edit from here
	int	i;

	i = str_start_pos + str_len - 1;
	while (line[++i] != '\0')
		line[str_start_pos] = line[i];
	line[str_start_pos] = '\0';
	return (line);
}

char	*remove_dollar(char *line)
{
	int	i;
	//int	j;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{	
			if (line[i + 1] != '\0'
				&& (line[i + 1] == '\'' || line[i + 1] == '"'))
			{
				line = remove_str_from_line(line, i, 1);
				// j = i;
				// while (line[++j] != '\0')
				// 	line[j - 1] = line[j];
				// line[j - 1] = '\0';
			}
		}
		i++;
	}
	return (line);
}

char	*remove_quote(char *line)
{
	char	quote;
	int		i;
	int		j;
	int		pos;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			j = i;
			while (line[++j] != '\0')
				line[j - 1] = line[j];
			line[j - 1] = '\0';
			pos = find_c_pos(line, quote, i);
			j = pos;
			while (line[++j] != '\0')
				line[j - 1] = line[j];
			line[j - 1] = '\0';
			i = pos - 1;
		}
		i++;
	}
	return (line);
}

// char	*handle_env_var(char *line)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (line[i] != '\0')
// 	{

// 	}
// 	return (line);
// }

t_data	**parse(t_data **cmd, char **env, char *rdline)
{
	char	**split_pipe;
	int		i;

	if (token_quote_err(rdline) || token_err(rdline) || pos_err(rdline))
		return (free_cmd(cmd), NULL);
	rdline = remove_dollar(rdline);
	rdline = remove_quote(rdline);
	//rdline = handle_env_var(rdline);
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
