/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pos_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:23:23 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/27 20:18:53 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	convert_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			line[i] = SPACE;
		else if (line[i] == '|')
			line[i] = PIPE;
		else if (line[i] == '<')
			line[i] = IN;
		else if (line[i] == '>')
			line[i] = OUT;
		i++;
	}
	line[i] = END;
}

void	pos_err_msg(int flag)
{
	if (flag == PIPE)
		token_err_msg("|");
	else if (flag == IN)
		token_err_msg("<");
	else if (flag == OUT)
		token_err_msg(">");
	else if (flag == HEREDOC)
		token_err_msg("<<");
	else
		token_err_msg(">>");
}

void	revert_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != END)
	{
		if (line[i] == SPACE)
			line[i] = ' ';
		else if (line[i] == PIPE)
			line[i] = '|';
		else if (line[i] == IN)
			line[i] = '<';
		else if (line[i] == OUT)
			line[i] = '>';
		i++;
	}
	line[i] = '\0';
}

int	check_pos_err(char *line, int flag, int i)
{
	while (line[i] != END)
	{
		if (line[i] == PIPE || line[i] == IN || line[i] == OUT)
		{
			flag = line[i];
			i++;
			if (line[i] == IN || line[i] == OUT)
			{
				if (line[i] == IN)
					flag = HEREDOC;
				else
					flag = APPEND;
				i++;
			}
			while (line[i] == SPACE)
				i++;
			if (line[i] == END || line[i] == PIPE
				|| line[i] == IN || line[i] == OUT)
				return (pos_err_msg(flag), 1);
		}
		i++;
	}
	return (0);
}

int	pos_err(char *line)
{
	int	i;
	int	pos;
	int	flag;
	int	len;

	i = 0;
	flag = 0;
	len = ft_strlen(line);
	convert_line(line);
	while (line[i] != END)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i++;
			pos = find_c_pos_err(line, line[i - 1], i, len);
			i = (pos + 1);
			continue ;
		}
		if (check_pos_err(line, flag, i))
			return (1);
		i++;
	}
	revert_line(line);
	return (0);
}
