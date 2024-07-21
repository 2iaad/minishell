/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:03:18 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/21 17:30:58 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 								EXPORT								*/

void	alpha_arrang(t_env *env)
{
	char *temp;
	t_env *tmp;

	tmp = env;
	while (tmp && tmp->next)
	{
		if (tmp->key[0] > tmp->next->key[0])
		{
			temp = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = temp;
			
			temp = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = temp;
			
			tmp = env;
		}
		else
			tmp = tmp->next;
	}
}

void	export_replace(t_env *env, char **str)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str[0], ft_strlen(str[0])))
		{
			free(tmp->value); // free old value
			tmp->value = ft_strdup(str[1]); // replace it with new allocated value(so i can free the linked list)
		}
		tmp = tmp->next;
	}	
}

void	export_join(t_env *env, char **str)
{
	bool	flag;
	t_env	*tmp;
	char	*tmpo;

	flag = false;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str[0], ft_strlen(str[0]) - 2))
		{
			flag = true;
			tmpo = tmp->value;
			tmp->value = ft_strjoin(tmpo, str[1]);
			free(tmpo);
		}
		tmp = tmp->next;
	}
	if (flag == false) // ila mal9ach smit lvariable ay addih
	{
		str[0][ft_strlen(str[0]) - 1] = '\0'; // atkoun str[0]="a+" donc blast + andir '\0' 3ad naddih
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
	}
}

void	export_var(t_env *env, char **str)
{
	bool	flag;
	t_env	*tmp;

	flag = false;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str[0], ft_strlen(str[0])))
		{
			flag = true; // flag tells if there is the variable or it should be added
			free(tmp->value);
			tmp->value = ft_strdup(str[1]);
		}
		tmp = tmp->next;
	}
	if (flag == false) // ila mal9ach smit lvariable ay addih
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(str[0]), ft_strdup(str[1])));
}

void	export_solo(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "_", 1) && ft_strncmp(tmp->key, "?", 1))
		{
			if (tmp->value && *tmp->value)
				printf("declare -x %s=\"%s\"\n",tmp->key, tmp->value); // \" to print the double quotations
			else if (tmp->value && !*tmp->value) 
				printf("declare -x %s=\"\"\n",tmp->key); // incase there was a "export VAR="
			else
				printf("declare -x %s\n", tmp->key); // hadi ila makanch chi key ando value deyalo
		}
		tmp = tmp->next;
	}
}

void	export_command(t_final *lst, t_env **env_list) // doesnt have to work if the key is a number or '=' , have to be ranged between 'a' and 'z'
{
	int		i;
	char	**str;

	i = 0;
	if (!lst->final_cmd[1])
		return (alpha_arrang(*env_list), export_solo(*env_list)); // if there is "export" arrang and print
	while (lst->final_cmd[++i])
	{
		str = custumized_ft_split(lst->final_cmd[i], '='); // str = {"a","salam", NULL}
		if (!str)
			return ;
		if (!export_valid_check(str[0], &env_list))
		{
			ft_free(str);
			continue;
		}
		if (str[0][ft_strlen(str[0]) - 1] == '+') // case where there is "+=" --> join
			export_join(*env_list, str);
		else if (str[1] && str[1][0] == '+') // case where there is "=+" --> replace // checking if str[1] in case i did "export salam"
			export_replace(*env_list, str);
		else
			export_var(*env_list,str);
		ft_free(str);
	}
}

/* handle export errors */
