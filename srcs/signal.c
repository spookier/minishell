/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:26:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/24 18:09:56 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	signal_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	/* ctrl-C */
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			//g_exit_status = 130;
		}
		else
			printf("\n");
	}
	/* ctrl-\ */
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
		{
			printf("minishell$ ");
			// printf("\b\b\b\b\b\b\b\b\b\b\b\b");
		}
	}
}

void	ft_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}