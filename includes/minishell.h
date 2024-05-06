/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:12:29 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/06 17:17:12 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "tools.h"
#include <stddef.h> // for size_t to be recognized
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_env
{
	char			*key;
    char			*value;
    struct s_env	*next;
}   t_env;

typedef struct s_list
{
	char	**cmd;
    char 	**env;
	t_env	*env_args;
}	t_list;

t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstadd_back(t_env **lst, t_env *newn);



/*          BUILTINS        */

void    echo(char   **cmd);
void    cd(char **cmd);
void    pwd(void);
void    env(t_list *cmd);

/*          EXECUTION       */

char	*look_for_paths(char **ev);

#endif