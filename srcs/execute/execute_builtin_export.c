/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:15 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/21 15:50:15 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int check_if_env_exists(char *env, char *str)
{
	int		i;
	char	*env_to_find;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	env_to_find = malloc((sizeof(char) * i) + 1);
	if (!env_to_find)
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		env_to_find[i] = env[i];
		i++;
	}
	env_to_find[i] = 0x00;

	// IF ENV ALREADY EXISTS, RET 1
	if(ft_strcmp(env_to_find, str) == 0)
	{
		free(env_to_find);
		return(1);
	}
	else
	{
		free(env_to_find);
		return(0);
	}
}

void	builtin_export(t_data *cmd, char ***env)
{
	int i;
	int k;

	k = 0;
	while (cmd->option && cmd->option[k])
	{
		i = 0;
		while ((*env)[i])
		{
			if (check_if_env_exists((*env)[i], cmd->option[k]) == 1)
			{
				// MODIFY EXISTING ENV VALUE HERE
				printf("Export command already exists\n");
				break ;
			}
			i++;
		}
		if(check_if_env_exists((*env)[i], cmd->option[k]) == 0)
		{
			printf("NEW ENV ADDED\n");
		}
		k++;
	}
}
