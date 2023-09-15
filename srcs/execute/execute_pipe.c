/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:43:17 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/15 03:43:26 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	alloc_pipe(t_data **cmd, int (**_pipe)[2])
{
	int	i;

	i = 0;
	*_pipe = NULL;
	while (cmd[i + 1])
	{
		*_pipe = ft_realloc(*_pipe, sizeof(int *) * i,
	 		sizeof(int *) * (i + 1));
		pipe((*_pipe)[i]);
		i++;
	}
}

void	close_pipe(t_data **cmd, int (**_pipe)[2])
{
	int	i;

	i = 0;
	while (cmd[i + 1])
	{
		close((*_pipe)[i][STDIN]);
		close((*_pipe)[i][STDOUT]);
		i++;
	}
}
