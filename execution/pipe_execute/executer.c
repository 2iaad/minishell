/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/07 18:08:28 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_cmd(t_final *lst, int *fds, int flag)
{
	if (flag == 0)
		if (lst->next)
			if(pipe(fds) == -1)
					error("pipe", 1337);
	if (flag == 1)
		if (lst->next)
			{
				if (dup2(fds[1], 1) == -1)
					error("dup2", 1337);
				close(fds[0]);
				close(fds[1]);
			}
	if (flag == 2)
		if (lst->next)
		{
			if (dup2(fds[0], 0) == -1)
					error("dup2", 1337);
			close(fds[0]);
			close(fds[1]);	
		}
}

void	child(t_final *lst, int *fds, char **envp)
{
	if (lst->in_file || lst->out_file || lst->aout_file || lst->heredoc)
	{
		heredoc_opener(lst->heredoc);
		infile_opener(lst->in_file);
		outfile_opener(lst->out_file);
		aoutfile_opener(lst->aout_file);
	}
	else
		pipe_cmd(lst, &fds[0], 1);
	execute_cmd(lst, envp);
}

void    execution(t_final *lst, t_env *env, char **envp)
{
	int	pid;
	int	fds[2];
	int	sec_fd[2];

	(1 == 1) && (sec_fd[0] = dup(0)) && (sec_fd[1] = dup(1));
	if (sec_fd[0] == -1 || sec_fd[1] == -1)
		error("dup", 1337);
	while (lst)
	{
		pipe_cmd(lst, &fds[0], 0);
		pid = fork();
		if (pid == -1)
			error("fork", 1337);
		if (!pid)
			child(lst, fds, envp);
		else
		{
			pipe_cmd(lst, &fds[0], 2);
			while (wait(NULL) == -1)
				;
			lst = lst->next;
		}
	}
	if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
		error("perror", 1337);
}
