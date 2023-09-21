/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:25 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/21 15:33:37 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (find_c_pos(env[i], '=', 0) != -1)
			printf("%s\n", env[i]);
		i++;
	}
}
