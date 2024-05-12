/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:13:21 by zderfouf          #+#    #+#             */
/*   Updated: 2024/05/12 11:54:46 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
#define TOOLS_H

#include "minishell.h"

void    ft_free(char **str);
int     flag_check(char *s1);
char	*ft_strdup(char *s1);
int     ft_strlen(char *str);
void    ft_putstr(char *str, int fd);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
int     ft_strcmp(char *s1, char *s2, int len);
char	**custumized_ft_split(const char *str, char c);
char	*ft_strnstr(const char *haystack, const char *needle, int len);


#endif