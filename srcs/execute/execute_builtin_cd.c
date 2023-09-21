/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:11 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/21 16:00:21 by yhwang           ###   ########.fr       */
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

void	add_element_to_env(char ***env, char *element_to_add)
{
	char	**new_env;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = (char **)ft_calloc(sizeof(char *), i + 2);
	i = -1;
	while ((*env)[++i])
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = element_to_add;
	free_2d_arr(*env);
	*env = new_env;
}

void	update_pwd_oldpwd(char ***env, char *absolute_path)
{
	char	*pwd;
	char	*oldpwd;
	int		i;

	pwd = ft_strjoin("PWD=", absolute_path);
	oldpwd = NULL;
	i = -1;
	*env = remove_element_from_env(*env, "OLDPWD");
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], "PWD", 3) && (*env)[i][3] == '=')
		{
			oldpwd = ft_strjoin("OLD", (*env)[i]);
			free((*env)[i]);
			(*env)[i] = oldpwd;
		}
	}
	add_element_to_env(env, pwd);
}

void	run_cd(t_data *cmd, char ***env, char *option)
{
	char	absolute_path[1024];

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
		getcwd(absolute_path, sizeof(absolute_path));
		update_pwd_oldpwd(env, absolute_path);
	}
}

void	builtin_cd(t_data *cmd, char ***env)
{
	char	*home_value;

	
	if (!cmd->option[0])
	{
		home_value = get_env_value(*env, "HOME");
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
