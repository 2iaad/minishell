/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caller.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:02:14 by zderfouf          #+#    #+#             */
/*   Updated: 2024/06/29 20:46:08 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	builtins(t_final *lst, t_env *env_list, bool *flag)
{
	if (!lst->final_cmd[0])
		return ;
    if (!ft_strncmp(lst->final_cmd[0], "echo", 4))
        echo(lst), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "cd", 2))
        cd(lst, &env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "pwd", 3))
        pwd(), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "export", 6))
        export_command(lst, &env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "unset", 5))
        unset(lst, env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "env", 3))
        env(lst, env_list), *flag = true;
    if (!ft_strncmp(lst->final_cmd[0], "exit", 4))
        exit_command(lst->final_cmd), *flag = true;
}