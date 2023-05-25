/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 04:11:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/25 05:22:04 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	token_quote_err(char *line)
{
	char	quote;
	int		i;
	int		pos;

	i = 0;
	quote = 0;
	pos = 0;
	while (line[i] != '\0' && pos >= 0)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			pos = find_c_pos(line, quote, i);
			i = (pos + 1);
			continue ;
		}
		i++;
	}
	if (pos == -1)
	{
		token_err_msg(quote);
		return (1);
	}
	return (0);
}

int	pipe_err(char *line, int i)
{
	if (line[i + 1] != '\0'
		&& (line[i + 1] == '|' || line[i + 1] == '<' || line[i + 1] == '>'))
	{
		token_err_msg('|');
		return (1);
	}
	return (0);
}

int	redir_in_err(char *line, int i)
{
	if (line[i + 1] != '\0'
		&& (line[i + 1] == '>' || line[i + 1] == '|'))
	{
		if (line[i + 1] == '|')
			token_err_msg('|');
		else
			token_err_msg('<');
		return (1);
	}
	if ((line[i + 1] != '\0' && line[i + 1] == '<')
		&& line[i + 2] != '\0'
		&& (line[i + 2] == '|' || line[i + 2] == '<' || line[i + 2] == '>'))
	{
		if (line[i + 2] != '\0' && line[i + 2] == '|')
			token_err_msg('|');
		else
			token_err_msg('<');
		return (1);
	}
	return (0);
}

int	redir_out_err(char *line, int i)
{
	if (line[i + 1] != '\0'
		&& (line[i + 1] == '<' || line[i + 1] == '|'))
	{
		if (line[i + 1] == '|')
			token_err_msg('|');
		else
			token_err_msg('>');
		return (1);
	}
	if ((line[i + 1] != '\0' && line[i + 1] == '>')
		&& line[i + 2] != '\0'
		&& (line[i + 2] == '|' || line[i + 2] == '<' || line[i + 2] == '>'))
	{
		if (line[i + 2] != '\0' && line[i + 2] == '|')
			token_err_msg('|');
		else
			token_err_msg('>');
		return (1);
	}
	return (0);
}

int	token_err(char *line)
{
	int		i;
	int		pos;

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
		if ((line[i] == '|' && pipe_err(line, i))
			|| (line[i] == '<' && redir_in_err(line, i))
			|| (line[i] == '>' && redir_out_err(line, i)))
			return (1);
		if (line[i] == ';' || line[i] == '\\')
		{
			token_err_msg(line[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
