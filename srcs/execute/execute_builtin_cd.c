/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:11 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/20 19:30:04 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char *get_env_value(char **env, char *key)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)) && env[i][ft_strlen(key)] == '=')
		{
			value = ft_strdup(env[i]);
			break ;
		}
		i++;
	}
	if (value)
		value = remove_str_from_line(value, 0, ft_strlen(key) + 1);
	return (value);
}

void	run_cd(t_data *cmd, char **env, char *option)
{
	//char	*dir;
	char	path[1024];

	if (chdir(option) == -1)
	{
		stderr_msg("minishell: cd: ");
		stderr_msg(option);
		if (access(option, F_OK) == 0)
			stderr_msg(": Not a directory\n");
		else
			stderr_msg(": No such file or directory\n");
		cmd->exit = 1;
	}
	else
	{
		getcwd(path, sizeof(path));//to get absolute path to update env
		printf("absolute path: %s\n", path);
	}
	(void)env;
}

void	builtin_cd(t_data *cmd, char **env)
{
	char	*home_value;

	
	if (!cmd->option[0])
	{
		home_value = get_env_value(env, "HOME");
		if (!home_value)
		{
			stderr_msg("minishell: cd: HOME not set\n");
			cmd->exit = 1;
		}
		else
		{
			run_cd(cmd, env, home_value);
			free(home_value);
		}
	}
	else if (cmd->option[1])
	{
		stderr_msg("minishell: cd: too many arguments\n");
		cmd->exit = 1;
	}
	else
		run_cd(cmd, env, cmd->option[0]);
}
