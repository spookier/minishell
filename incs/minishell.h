/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:50 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/30 01:58:42 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BLACK			"\x1b[0m"
# define RED			"\x1b[31m"
# define CYAN			"\x1b[36m"
# define YELLOW			"\x1b[33m"

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define SPACE			10
# define PIPE			11
# define END			14

# define NONE			20
# define IN			21
# define OUT			22
# define HEREDOC		23
# define APPEND			24

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
	int			operation_flag;
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
char		**alloc_env(char **env);
void		minishell_header(void);
int			minishell_main(t_data **cmd, char **env);
int			main(int argc, char **argv, char **env);

/* signal.c */
void		signal_handler(int signo);
void		signal_detect(void);

/* parse.c */
t_data		**alloc_cmd(t_data **cmd, int i);
t_data		**parse(t_data **cmd, char **env, char *rdline);

/* parse_token_error_1.c */
int			token_quote_err(char *line);
int			token_pipe_err(char *line, int i);
int			token_ampersand_err(char *line, int i);
int			token_err(char *line);

/* parse_token_error_2.c */
int			token_redir_in_err(char *line, int i);
int			token_redir_out_err(char *line, int i);
int			token_semicolon_err(void);
int			token_backslash_err(void);

/* parse_token_pos_error.c */
void		convert_line(char *line);
void		pos_err_msg(int flag);
int			check_pos_err(char *line, int *flag, int i);
char		*copy_line(char *line);
int			pos_err(char *line);

/* parse_utils.c */
int			find_c_pos(char *str, char c, int start);
void		token_err_msg(char *s);

/* lib_utils.c */
void		*ft_realloc(void *old_ptr, size_t old_len, size_t new_len);
void		free_2d_arr(char **arr);
void		free_cmd(t_data **cmd);

#endif
