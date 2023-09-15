/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:42:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/15 03:43:06 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*gain_env_value(char *key, char **env)
{
	int	i;
	char	*value;

	i = 0;
	value = NULL;
	while (env[i])
	{
		if (strncmp(env[i], key, ft_strlen(key)) == 0
			&& env[i][ft_strlen(key)] == '=')
			value = ft_strdup(env[i]);
		i++;
	}
	if (value == NULL)
		return (NULL);
	value = remove_str_from_line(value, 0, ft_strlen(key) + 1);
	return (value);
}

char	*find_cmd_path(t_data *cmd, char **env)
{
	char	*path_value;
	char	**splited_path;
	char	*cmd_with_path;
	int		i;

	path_value = gain_env_value("PATH", env);
	splited_path = ft_split(path_value, ':');
	cmd_with_path = NULL;
	i = 0;
	while (splited_path[i])
	{
		splited_path[i] = append_str_to_alloced_str(splited_path[i], "/");
		cmd_with_path = ft_strjoin(splited_path[i], cmd->command);
		if (access(cmd_with_path, F_OK) == 0)
		{
			free(path_value);
			free_2d_arr(splited_path);
			return (cmd_with_path);
		}
		free(cmd_with_path);
		i++;
	}
	free(path_value);
	free_2d_arr(splited_path);
	return (NULL);
}

void	execute_non_builtin(t_data *cmd, char *cmd_with_path, char **env)
{
	char		**argv;
	struct stat	buf;
	int			i;

	argv = ft_calloc(2, sizeof(char *));
	argv[0] = ft_strdup(cmd->command);
	i = 0;
	while (cmd->option[i])
	{
		argv = ft_realloc(argv, (i + 2) * sizeof(char *),
			(i + 3) * sizeof(char *));
		argv[i + 1] = ft_strdup(cmd->option[i]);
		i++;
	}
	execve(cmd_with_path, argv, env);
	free_2d_arr(argv);
	free(cmd_with_path);
	stat(cmd->command, &buf);
	if (S_ISDIR(buf.st_mode))
		printf("%sminishell: Is a directory%s\n", RED, BLACK);
}

void	non_builtin(t_data *cmd, char **env)
{
	char	*cmd_with_path;
	
	cmd_with_path = find_cmd_path(cmd, env);
	if (cmd_with_path == NULL)
	{
		if (find_c_pos(cmd->command, '/', 0) != -1)
			printf("%sminishell: No such file or directory%s\n", RED, BLACK);
		else
			printf("%s%s: command not found%s\n", RED, cmd->command, BLACK);
		cmd->exit = 127;
		return ;
	}
	execute_non_builtin(cmd, cmd_with_path, env);
}
