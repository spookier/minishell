/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:35:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/21 20:23:59 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_data	**alloc_cmd(t_data **cmd, int i)
{
	cmd = ft_realloc(cmd, sizeof(t_data *) * (i + 1),
			sizeof(t_data *) * (i + 2));
	if (!cmd)
		return (printf("%sError: malloc error%s\n", RED, BLACK), NULL);
	cmd[i] = (t_data *)ft_calloc(sizeof(t_data), 2);
	if (!cmd[i])
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		return (free_cmd(cmd), NULL);
	}
	return (cmd);
}

char	*make_new_line(char **env, char *rdline)
{
	char	*line;

	line = ft_strdup(rdline);
	remove_dollar(line);
	line = handle_env_var(env, line);
	remove_quote(line);
	return (line);
}

int	is_redir(char *str)
{
	if ((!strncmp("<", str, 1) && ft_strlen(str) == 1)
		|| (!strncmp(">", str, 1) && ft_strlen(str) == 1)
		|| (!strncmp("<<", str, 1) && ft_strlen(str) == 2)
		|| (!strncmp(">>", str, 1) && ft_strlen(str) == 2))
		return (1);
	return (0);
}

void	fill_option(t_data **cmd, char **split_cmd, int cmd_i)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd[cmd_i]->option[i] = NULL;
	while (split_cmd[++i])
	{
		if (is_redir(split_cmd[i]))
		{
			i++;
			continue ;
		}
		cmd[cmd_i]->option[j++] = ft_strdup(split_cmd[i]);
	}
}

void	check_redir_filename(char *split_cmd)
{
	printf("filename: %s\n", split_cmd);
	
}

void	fill_redir(t_data **cmd, char **split_cmd, int cmd_i)
{
	int	i;

	if (cmd[cmd_i]->redir->redir_flag == NONE)
	{
		cmd[cmd_i]->redir->file_name = ft_strdup("");
		return ;
	}

	i = -1;
	while (split_cmd[++i])
	{
		if (is_redir(split_cmd[i]))
			break ;
	}
	i++;
	check_redir_filename(split_cmd[i]);
}

void	check_redir(t_data **cmd, char *each_cmd, char **split_cmd, int cmd_i)
{
	int	i;

	i = 0;
	cmd[cmd_i]->redir->redir_flag = -1;
	while (each_cmd[i] && cmd[cmd_i]->redir->redir_flag == -1)
	{
		if (each_cmd[i] == '<')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '<')
				cmd[cmd_i]->redir->redir_flag = HEREDOC;
			else
				cmd[cmd_i]->redir->redir_flag = IN;
		}
		if (each_cmd[i] == '>')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '>')
				cmd[cmd_i]->redir->redir_flag = APPEND;
			else
				cmd[cmd_i]->redir->redir_flag = OUT;
		}
		i++;
	}
	if (cmd[cmd_i]->redir->redir_flag == -1)
		cmd[cmd_i]->redir->redir_flag = NONE;
	fill_redir(cmd, split_cmd, cmd_i);
}

t_data	**fill_data(t_data **cmd, char *each_cmd, int cmd_i)
{
	char	**split_each_cmd;
	int		option;
	int		redir_flag;

	split_each_cmd = ft_split(each_cmd, ' ');
	option = 0;
	while (split_each_cmd[option])
	{
		if (is_redir(split_each_cmd[option]))
			redir_flag++;
		option++;
	}
	if (!option)
	{
		free_2d_arr(split_each_cmd);
		return (free_cmd(cmd), NULL);
	}
	cmd[cmd_i]->command = ft_strdup(split_each_cmd[0]);
	cmd[cmd_i]->option = ft_calloc(sizeof(char *), option);
	cmd[cmd_i]->redir = ft_calloc(sizeof(t_redir *), 2);
	if (!cmd[cmd_i]->option || !cmd[cmd_i]->redir)
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		free_2d_arr(split_each_cmd);
		return (free_cmd(cmd), NULL);
	}
	fill_option(cmd, split_each_cmd, cmd_i);
	check_redir(cmd, each_cmd, split_each_cmd, cmd_i);
	return (free_2d_arr(split_each_cmd), cmd);
}

t_data	**parse(t_data **cmd, char **env, char *rdline)
{
	char	*line;
	char	**split_pipe;
	int		i;

	/* command line error check: quote, pipe, empersand, redirect, semicolon, backslash */
	//todo: handle error code
	if (token_quote_err(rdline) || token_err(rdline) || pos_err(rdline))
		return (free_cmd(cmd), NULL);
	/* make new command line: handle env variable, remove dollar sign */
	line = make_new_line(env, rdline);
	printf("%sline: %s%s\n", CYAN, line, BLACK);//
	/* split the command by pipe */
	split_pipe = ft_split(line, '|');
	/* free the original command line */
	free(line);
	i = -1;
	/* put command info to the cmd structure */
	while (split_pipe[++i])
	{
		/* alloc cmd structure */
		cmd = alloc_cmd(cmd, i);
		/* error check: malloc */
		if (!cmd)
			return (free_2d_arr(split_pipe), NULL);
		/* fill the command info */
		cmd = fill_data(cmd, split_pipe[i], i);
		/* check if any error happened and free split_pipe if there was error
			: if any error has happened during filling the info,
			cmd was freed and NULL was returned */
		if (!cmd)
			return (free_2d_arr(split_pipe), NULL);
	}
	/* free split_pipe after filling cmd struct */
	free_2d_arr(split_pipe);




	i = -1;//
	printf("%s", YELLOW);
	while (cmd[++i])//
	{
		printf("cmd[%d] command: %s\n", i, cmd[i]->command);//
		int j = -1;//
		while (cmd[i]->option[++j])//
			printf("       option[%d]: %s\n", j, cmd[i]->option[j]);//
		if (cmd[i]->redir->redir_flag == IN)
			printf("       redir: IN\n");
		else if (cmd[i]->redir->redir_flag == OUT)
			printf("       redir: OUT\n");
		else if (cmd[i]->redir->redir_flag == HEREDOC)
			printf("       redir: HEREDOC\n");
		else if (cmd[i]->redir->redir_flag == APPEND)
			printf("       redir: APPEND\n");
		else
			printf("       redir: NONE\n");
	}
	printf("%s", BLACK);
	
	return (cmd);
}
