/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:50 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/25 05:22:01 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MIHISHELL_H

# define BLACK			"\x1b[0m"
# define RED			"\x1b[31m"
# define CYAN			"\x1b[36m"
# define YELLOW			"\x1b[33m"

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define NONE			10
# define IN			11
# define OUT			12
# define HEREDOC		13
# define APPEND			14

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <limits.h>
# include "../libft/incs/libft.h"

typedef struct s_redir
{
	int		operation_flag;
	char		*file_name;
}	t_redir;

typedef struct s_data
{
	char		*command;
	char		**option;
	t_redir		**redir;
	int			pid;
	int			exit;
}	t_data;

extern int	g_exit_code;

/* main.c */
void	minishell_header(void);
char	**alloc_env(char **env);
int	minishell_main(char **env);
int	main(int argc, char **argv, char **env);

/* signal.c */
void	signal_handler(int signo);
void	signal_detect(void);

/* parse.c */
int	check_valid_input(char *str, char **env);
t_data	**alloc_cmd(t_data **cmd, char **env, int i);
t_data	**parse(t_data **cmd, char **env, char *rdline);

/* parse_error.c */
int	token_quote_err(char *line);
int	pipe_err(char *line, int i);
int	redir_in_err(char *line, int i);
int	redir_out_err(char *line, int i);
int	token_err(char *line);

/* parse_utils.c */
int	find_c_pos(char *str, char c, int start);
void	token_err_msg(char c);

/* lib_utils.c */
void	*ft_realloc(void *old_ptr, size_t old_len, size_t new_len);
void	free_2d_arr(char **arr);
void	free_cmd(t_data **cmd);

#endif
