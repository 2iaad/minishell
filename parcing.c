/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:10:41 by ibouram           #+#    #+#             */
/*   Updated: 2024/05/04 18:00:22 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
int	main()
{
	char *s = "cat-e<numbers.txt>|grep>>hi";
	char **line;

	line = ft_split(s, " '\"|<>&");
	// if (line != NULL)
	// {
	// 	int i = 0;
	// 	while (line[i])
	// 	{
	// 		printf("%s\n", line[i]);
	// 		i++;
	// 	}
	// }
}