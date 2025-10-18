/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_wrappers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/10/18 21:31:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/gc.h"
#include "../headers/libft.h"

/**
 * Wrapper for ft_strdup that uses garbage collector
 */
char	*gc_strdup(const char *s1)
{
	char	*dup;

	dup = ft_strdup(s1);
	if (dup)
		gc_add_ptr(dup);
	return (dup);
}

/**
 * Wrapper for ft_split that uses garbage collector
 */
char	**gc_split(char const *s, char c)
{
	char	**split;
	int		i;

	split = ft_split(s, c);
	if (!split)
		return (NULL);
	
	gc_add_ptr(split);
	i = 0;
	while (split[i])
	{
		gc_add_ptr(split[i]);
		i++;
	}
	
	return (split);
}

/**
 * Wrapper for ft_strtrim that uses garbage collector
 */
char	*gc_strtrim(char const *s1, char const *set)
{
	char	*trimmed;

	trimmed = ft_strtrim(s1, set);
	if (trimmed)
		gc_add_ptr(trimmed);
	return (trimmed);
}
