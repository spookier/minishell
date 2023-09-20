/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:21 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/18 05:08:04 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int compare_env_var_name(char *env, char *str, char *env_to_find)
{
	int i;
	
	i = 0;

	while(env[i] && env[i] != '=')
		i++;
	env_to_find = malloc((sizeof(char) * i) + 1);
	env_to_find[i] = 0x00;
	i = 0;
	while(env[i] && env[i] != '=')
	{
		env_to_find[i] = env[i];
		i++;
	}
	if(ft_strcmp(env_to_find, str) == 0)
	{
		// EXECUTE UNSET COMMAND HERE
		printf("------------------- COMMAND FOUND!\n");
		return(free(env_to_find), 1);
	}
	free(env_to_find);
	return (0);
}

void	builtin_unset(t_data *cmd, char **env)
{
	int	i;
	int j;
	char *env_to_find;

	i = 0;
	env_to_find = NULL;
	while (env[i])
	{
		if(compare_env_var_name(env[i], cmd->option[0], env_to_find) == 1)
		{
			j = i;
			while(env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			// free(env_to_find);
		}
		i++;
	}
}
