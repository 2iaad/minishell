/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/04 15:57:33 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	signal_checker()
{
	if (g_signal == 2)
	{
		exit_status(1, 1);
		g_signal = 0;
		return (true);
	}
	return (false);
}

void	multiple(t_final *lst, t_env **env)
{
	pid_t	pid;
	int		fds[2][2];

	init_secfds(&fds[1][0], 0);
	while (lst)
	{
		pipe_cmd(lst, &fds[0][0], 0);
		heredoc_opener(&lst->files, *env, fds[1][0]);
		if (signal_checker())
			break ;
		pid = fork();
		if (pid == -1)
			error("fork", 1337);
		if (!pid)
			child(lst, env, fds[0]);
		else
		{
			close(0);
			pipe_cmd(lst, &fds[0][0], 2);
			lst = lst->next;
		}
	}
	multiple_helper(env);
	init_secfds(&fds[1][0], 1);
}

void	single(t_final *lst, t_env **env)
{
	pid_t	pid;
	int		sec_fd[2];

	init_secfds(sec_fd, 0);
	heredoc_opener(&lst->files, *env, sec_fd[0]);
	if (signal_checker())
		return ;
	if (!s_file_opener(lst->files))
		return ;
	if (!builtins(lst, env))
	{
		pid = fork();
		if (!pid)
			execute_cmd(lst, *env);
		else
			multiple_helper(env);
	}
	init_secfds(sec_fd, 1);
}

void	execution(t_final *lst, t_env **env, struct termios *p)
{
	parce_files(&lst);
	if (lst->next)
		multiple(lst, env);
	else
	{
	 	single(lst, env);
		tcsetattr(0, 0, p);
	}
}