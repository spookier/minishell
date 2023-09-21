/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:15 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/21 20:16:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	run_export_no_option(char **env)
{
	int	i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		key = ft_substr(env[i], 0, find_c_pos(env[i], '=', 0) + 1);
		value = ft_strdup(env[i]);
		value = remove_str_from_line(value, 0, find_c_pos(env[i], '=', 0) + 1);
		printf("declare -x %s\"%s\"\n", key, value);
		free(key);
		free(value);
		i++;
	}
}


void	run_export(char ***env, char *key_value)
{
	char	*key;
	int	i;

	key = ft_substr(key_value, 0, find_c_pos(key_value, '=', 0));
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], key, ft_strlen(key))
			&& (*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = key_value;
			free(key);
			return ;
		}
	}
	free(key);
	add_element_to_env(env, key_value);
}

void	builtin_export(t_data *cmd, char ***env)
{
	int	i;

	if (!cmd->option[0])
		run_export_no_option(*env);
	else
	{
		i = 0;
		while (cmd->option[i])
		{
			if (find_c_pos(cmd->option[i], '=', 0) != -1)
				run_export(env, ft_strdup(cmd->option[i]));
			i++;
		}
	}
}
	
	
