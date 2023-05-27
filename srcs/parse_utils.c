/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 04:10:48 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/27 22:19:54 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	find_c_pos(char *str, char c, int start)
{
	int	i;

	i = start;
	if ((int)ft_strlen(str) <= start)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	token_err_msg(char *s)
{
	printf("%sminishell: syntax error near unexpected token `%s'%s\n",
		RED, s, BLACK);
}
