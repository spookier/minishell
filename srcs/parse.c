/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:35:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/31 05:13:41 by yhwang           ###   ########.fr       */
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

char	*remove_dollar(char *line)
{
	int	i;
	int	pos;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i++;
			pos = find_c_pos(line, line[i - 1], i);
			i = (pos + 1);
			continue ;
		}
		if (line[i] == '$')
		{
			if (line[i + 1] != '\0'
				&& (line[i + 1] == '\'' || line[i + 1] == '"'))
				line = remove_str_from_line(line, i, 1);
		}
		i++;
	}
	return (line);
}

char	*remove_quote(char *line)
{
	char	quote;
	int		i;
	int		pos;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			line = remove_str_from_line(line, i, 1);
			pos = find_c_pos(line, quote, i);
			line = remove_str_from_line(line, pos, 1);
			i = pos - 1;
		}
		i++;
	}
	return (line);
}

char	*change_key_to_value(char *line, char *key, char *value)
{
	printf("key: %s\n", key);
	printf("value: %s\n", value);
	return (line);
}

char	*convert_env(char **env, char *line, int start, int end)
{
	char	*key;
	char	*value;
	char	*temp;
	int		pos;
	int		i;

	while (line[end - 1] == '"' || line[end - 1] == '\'')
		end--;
	key = ft_substr(line, start, end - start);
	value = NULL;
	i = -1;
	while (env[++i])
	{
		pos = find_c_pos(env[i], '=', 0);
		temp = ft_substr(env[i], 0, pos);
		if (!ft_strncmp(temp, key, ft_strlen(temp)) && ft_strlen(temp) == ft_strlen(key))
		{
			value = ft_substr(env[i], pos + 1, ft_strlen(env[i]) - (pos + 1));
			free(temp);
			break ;
		}
		free(temp);
	}
	if (!value)
		value = ft_strdup("");
	line = change_key_to_value(line, key, value);
	free(key);
	free(value);
	return (line);
}

char	*handle_env_var(char **env, char *line)
{
	int	i;
	int	pos;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			quote = line[i];
			i++;
		}
		if (line[i] == '\'')
		{
			if (quote == '"')
			{
				i++;
				if (line[i] == '$')
				{
					if (!line[i + 1]
						|| (line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == ' ')))
						break ;
					remove_str_from_line(line, i, 1);
					pos = find_c_pos(line, ' ', i);
					if (pos == -1)
						pos = ft_strlen(line);
					line = convert_env(env, line, i, pos);
					break ;
				}
			}
			i++;
			pos = find_c_pos(line, line[i - 1], i);
			i = (pos + 1);
			continue ;
		}
		if (line[i] == '$')
		{
			if (!line[i + 1]
				|| (line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == ' ')))
				break ;
			remove_str_from_line(line, i, 1);
			pos = find_c_pos(line, ' ', i);
			if (pos == -1)
				pos = ft_strlen(line);
			line = convert_env(env, line, i, pos);
		}
		i++;
	}
	return (line);
}

t_data	**parse(t_data **cmd, char **env, char *rdline)
{
	char	**split_pipe;
	int		i;

	if (token_quote_err(rdline) || token_err(rdline) || pos_err(rdline))
		return (free_cmd(cmd), NULL);
	rdline = remove_dollar(rdline);
	rdline = handle_env_var(env, rdline);
	rdline = remove_quote(rdline);
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
