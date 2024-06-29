/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:13:33 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/29 21:04:50 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_cmd(t_final *lst, int *fds, int flag)
{
	if (!lst->next)	
		return ;
	if (flag == 0)
		if(pipe(fds) == -1)
				error("pipe", 1337);
	if (flag == 1)
	{
		close(fds[0]);
		if (dup2(fds[1], 1) == -1)
			error("dup2", 1337);
		close(fds[1]);
	}
	if (flag == 2)
	{	
		close(fds[1]);	
		if (dup2(fds[0], 0) == -1)
				error("dup2", 1337);
		close(fds[0]);
	}
}

void	child(t_final *lst, t_env *env, int *fds, char **envp)
{
	bool	flag;

	if (lst->in_file || lst->heredoc || lst->out_file || lst->aout_file)
	{
		if (lst->heredoc)
			heredoc_opener(lst->heredoc, env);
		if (lst->in_file)
			infile_opener(lst->in_file);
		if (lst->out_file)
			outfile_opener(lst->out_file);
		if (lst->aout_file)
			aoutfile_opener(lst->aout_file);
	}
	else if (lst->next)
		pipe_cmd(lst, &fds[0], 1);
	builtins(lst, env, &flag);
	if (flag)
		exit(0);
	else
		execute_cmd(lst, envp);
}

void	multiple(t_final *lst, t_env *env, char **envp)
{
	int	pid;
	int exit_status;
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
			child(lst, env, fds, envp);
		else
		{
			pipe_cmd(lst, &fds[0], 2);
			lst = lst->next;
		}
	}
	if (dup2(sec_fd[0], 0) == -1 || dup2(sec_fd[1], 1) == -1)
		error("dup2", 1337);
	while (wait(&exit_status) != -1)
		;
	return ((void)close(sec_fd[0]), (void)close(sec_fd[1]));
}

void	single(t_final *lst, t_env *env, char **envp)
{
	int		pid;
	bool	flag;

	flag = false;
	builtins(lst, env, &flag);
	if (!flag)
	{
		pid = fork();
		if (!pid)
			child(lst, env, &pid, envp);
		else
		 	wait(NULL);
	}
}

void    execution(t_final *lst, t_env *env, char **envp)
{
	if (lst->next)
		multiple(lst, env, envp);
	else
	 	single(lst, env, envp);
}
