/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:30:14 by ibouram           #+#    #+#             */
/*   Updated: 2024/07/07 10:40:19 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ls -la < lsls >> slsl -l | cat -e

void print_final(t_final *final)
{
    t_final *tmp = final;
    int i;

    while (tmp)
    {
        printf("Command: %s\n", tmp->cmd);
        printf("Options: ");
        if (tmp->args)
        {
            for (i = 0; tmp->args[i]; i++)
            {
                printf("%s ", tmp->args[i]);
            }
        }
        printf("\nFiles: ");
        if (tmp->files)
        {
            for (i = 0; tmp->files[i].file; i++)
            {
                printf("%s (type: %d) ", tmp->files[i].file, tmp->files[i].type);
            }
        }
        printf("\n");
        tmp = tmp->next;
    }
}

int	count_len(t_token *node, int type)
{
	int	i;

	i = 0;
	while (node && node->type != PIPE)
	{
		if (node->type == type)
			i++;
		node = node->next;
	}
	return (i);
}

t_final	*init_final(t_token **nodee)
{
	t_final	*final;
	t_token	*node;

	node = *nodee;
	final = malloc(sizeof(t_final));
	if (!final)
		return (NULL);
	final->cmd = NULL;
	if (count_len(node, OPTION) > 0)
	{
		final->args = malloc(sizeof(char *) * (count_len(node, OPTION) + 1));
		if (!final->args)
			return (NULL);
		final->args[count_len(node, OPTION)] = NULL;
	}
	else
		final->args = NULL;
	int files_len = count_len(node, IN_FILE) + count_len(node, OUT_FILE) + count_len(node, AOUT_FILE) + count_len(node, DELIMITER);
	if (files_len > 0)
	{
		final->files = malloc(sizeof(t_file) * (files_len + 1));
		if (!final->files)
			return (NULL);
		final->files[files_len].file = NULL;
	}
	else
		final->files = NULL;
	return (final);
}


t_final	*struct_init(t_token **token)
{
	t_token *node;
	t_final *final;
	t_final *tmp;
	int		opt_index;
	int     files_index;

	node = *token;
	final = NULL;
	while (node)
	{
		if (node == *token || node->type == PIPE)
		{
			(1) && (opt_index = 0, files_index = 0);
			if (node->type == PIPE)
				node = node->next;
			tmp = init_final(&node);
			if (!tmp)
				return (NULL);
			while (node && node->type != PIPE)
			{
				if (node->type == CMD)
					tmp->cmd = ft_strdup(node->token);
				else if (node->type == OPTION)
				{
					tmp->args[opt_index++] = ft_strdup(node->token);
				}
				else if (node->type == IN_FILE)
				{
					tmp->files[files_index++].file = ft_strdup(node->token);
					tmp->files[files_index].type = IN_FILE;
				}
				else if (node->type == OUT_FILE)
				{
					tmp->files[files_index++].file = ft_strdup(node->token);
					tmp->files[files_index].type = OUT_FILE;
				}
				else if (node->type == AOUT_FILE)
				{
					tmp->files[files_index++].file = ft_strdup(node->token);
					tmp->files[files_index].type = AOUT_FILE;
				}
				else if (node->type == DELIMITER)
				{
					tmp->files[files_index++].file = ft_strdup(node->token);
					tmp->files[files_index].type = DELIMITER;
				}
				node = node->next;
			}
			tmp->next = NULL;
			ft_lstadd_back3_parse(&final, tmp);
		}
		else
			node = node->next;
	}
	tmp->files[files_index++].type = 42;
	/*
	to loop over the files array:
	while (files.type != 42)
	{
		....
	}
	 */
	// print_final(final);
	return (final);
}
