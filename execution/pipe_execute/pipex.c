/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:58:31 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/05 16:04:23 by zderfouf         ###   ########.fr       */
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

void	child(t_final *lst, t_env *env, int *fds, char **envp, int sec_fd)
{
	bool	flag;

	if (lst->in_file || lst->heredoc || lst->out_file || lst->aout_file)
	{
		if (lst->heredoc)
		{
			dup2(sec_fd, 0);
			heredoc_opener(lst->heredoc, env);
		}
		if (lst->in_file)
			infile_opener(lst->in_file);
		if (lst->out_file)
			outfile_opener(lst->out_file);
		if (lst->aout_file)
			aoutfile_opener(lst->aout_file);
	}
	if (lst->next && isatty(1)) // isatty(1) checks if the redirection is tty or a file cat Makefile | grep clean > (--/dev/stdout--) | wc
		pipe_cmd(lst, &fds[0], 1);
	builtins(lst, env, &flag);
	if (flag)
		exit(0);
	else
		execute_cmd(lst, envp);
}