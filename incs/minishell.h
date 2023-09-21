/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:50 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/21 21:51:40 by yhwang           ###   ########.fr       */
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

# define SPACE			1
# define PIPE			2
# define END			3

# define _PIPE			10
# define _IN			11
# define _OUT			12
# define _SPACE			13

# define NONE			1
# define IN			2
# define OUT			3
# define HEREDOC		4
# define APPEND			5

# define KEY			0
# define VALUE			1
# define TEMP			2

# define CHILD			0
# define PARENTS		1

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
# include "../libft/incs/ft_printf.h"

typedef struct s_redir
{
	int			redir_flag;
	char		*file_name;
}	t_redir;

typedef struct s_data
{
	char		*command;
	char		**option;
	t_redir		*redir;
	int			exit;
	int			pid;
}	t_data;

extern int	g_exit_code;

/* 🐥 main 🐥 */
/* main.c */
char		**alloc_env(char **env);
void		signal_handler(int signo);
void		signal_detect(void);
int			minishell_main(t_data **cmd, char **env);
int			main(int argc, char **argv, char **env);

/* 🐥 parse 🐥 */
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

/* parse_pos_error.c */
void		convert_line(char *line);
void		pos_err_msg(int flag);
int			check_pos_err(char *line, int *flag, int i);
char		*copy_line(char *line);
int			pos_err(char *line);

/* parse_make_new_line.c */
void		remove_dollar(char *line);
void		remove_quote(char *line);
char		*put_space(char *line, int i, int redir_len, char redir);
char		*redir_put_space(char *line);
char		*make_new_line(char **env, char *rdline);

/* parse_handle_env_variable.c */
char		*change_key_to_value(char *line,
				char *key, int *pos_key_start, char *value);
char		*env_check_value(char **env, char *line, int *start, int end);
char		*env_var_convert_line(char **env, char *line, int *i);
void		handle_env_var_norminette(int *quote);
char		*handle_env_var(char **env, char *line);

/* parse_fill_cmd_struct.c */
int			is_redir(char *str);
void		fill_option(t_data **cmd, char **split_cmd, int cmd_i);
void		fill_redir(t_data **cmd, char **split_cmd, int cmd_i);
void		check_redir(t_data **cmd,
				char *each_cmd, char **split_cmd, int cmd_i);
t_data		**fill_cmd_struct(t_data **cmd, char *each_cmd, int cmd_i);

/* parse_utils.c */
void		minishell_header(void);
void		token_err_msg(char *s);
int			find_c_pos(char *str, char c, int start);
char		*remove_str_from_line(char *line, int str_start_pos, int str_len);

/* parse_lib_utils.c */
void		*ft_realloc(void *old_ptr, size_t old_len, size_t new_len);
void		free_2d_arr(char **arr);
void		free_cmd(t_data **cmd);

/* 🐥 execute 🐥 */
/* execute_main.c */
void		execute_cmd(t_data *cmd, char ***env);
void		wait_pid(t_data **cmd);
void		exec_main(t_data **cmd, char ***env);

/* execute_heredoc.c */
void		write_heredoc(int fd_heredoc, char *delim);
void		check_heredoc(t_data **cmd);

/* execute_pipe_fd.c */
void		alloc_pipe(t_data **cmd, int (**_pipe)[2]);
void		close_pipe(t_data **cmd, int (**_pipe)[2]);
void		set_fd_close_pipe(t_data **cmd, int (**_pipe)[2], int i);
void		set_fd_stdio(int *fd);
void		close_fd_stdio(int *fd);

/* execute_redir.c */
int			redir_open_file(int *in_fd, int *out_fd, t_data *cmd);
int			redir_set_fd(t_data *cmd);

/* execute_builtin_echo.c */
void		builtin_echo(t_data *cmd);

/* execute_builtin_env.c */
void		builtin_env(char **env);

/* execute_builtin_unset.c */
void		builtin_unset(t_data *cmd, char **env);

/* execute_builtin_export.c */
void		builtin_export(t_data *cmd, char ***env);

/* execute_builtin_cd.c */
void		add_element_to_env(char ***env, char *element_to_add);
void		builtin_cd(t_data *cmd, char ***env);

/* execute_builtin_pwd.c */
void		builtin_pwd(void);

/* execute_builtin_exit.c */
long long	ft_atolonglong(char *str);
int			is_num_str(char *str);
void		builtin_exit(t_data *cmd);

/* execute_non_builtin.c */
char		*gain_env_value(char *key, char **env);
char		*find_cmd_path(t_data *cmd, char **env);
void		non_builtin(t_data *cmd, char **env);

/* execute_utils.c */
char		**remove_element_from_env(char **env, char *to_remove);
int			is_builtin_cmd(char *command);
char		*append_str_to_alloced_str(char *str1, char *str2);
char		*append_num_to_alloced_str(char *str1, int i);
void		stderr_msg(char *str);

#endif
